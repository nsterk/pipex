#include <sys/wait.h>
#include <time.h>
#include <pipex_bonus.h>

static void	init_pipex(t_pipex *pipex, int argc)
{
	int	pipe;

	pipe = 0;
	pipex->paths = NULL;
	pipex->nr_children = argc - 3;
	pipex->current_child = 1;
	pipex->cmd = malloc(sizeof(t_cmd) * pipex->nr_children);
	pipex->pid = malloc(sizeof(int) * pipex->nr_children);
	pipex->fd = malloc(sizeof(pipex->fd) * pipex->nr_children);
	if (!pipex->cmd || !pipex->pid || !pipex->fd)
		exit_pipex(pipex, -1, "Malloc failure in init");
	while (pipe < pipex->nr_children)
	{
		pipex->fd[pipe] = malloc(sizeof(int) * 2);
		if (!pipex->fd[pipe])
			exit_pipex(pipex, -1, "Malloc failure in init");
		pipe++;
	}
}

static void	get_paths(t_pipex *pipex, char **envp, char c)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->paths = ft_split(*envp + 5, c);
	if (!pipex->paths)
		exit_pipex(pipex, -3, "Malloc failure getting env paths");
	// return (ft_split(*envp + 5, c));
	// return (*envp + 5);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		exit_pipex(&pipex, -2, "Too few arguments supplied");
	init_pipex(&pipex, argc);
	get_paths(&pipex, envp, ':');
	// pipex.paths = ft_split(get_paths(envp), ':');
	// if (!pipex.paths)
	// 	exit_pipex(&pipex, -3, "Malloc failure getting env paths");
	get_commands(&pipex, argv, argc - 1);
	open_pipes(&pipex);
	handle_the_children(&pipex, argv, envp);
	close_pipes(&pipex);
	wait_for_children(&pipex);
	return (0);
}
