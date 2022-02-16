#include <sys/wait.h>
#include <time.h>
#include <pipex.h>

static void	init_pipex(t_pipex *pipex, int argc)
{
	int	pipe;

	pipe = 0;
	pipex->paths = NULL;
	pipex->nr_children = argc - 3;
	pipex->current_child = 1;
	pipex->cmd = malloc(sizeof(t_cmd) * pipex->nr_children);
	if (!pipex->cmd)
		exit_pipex(pipex, -1, "Malloc failure in init");
	pipex->pid = malloc(sizeof(int) * pipex->nr_children);
	if (!pipex->pid)
		exit_pipex(pipex, -1, "Malloc failure in init");
	pipex->fd = malloc(sizeof(pipex->fd) * pipex->nr_children);
	while (pipe < pipex->nr_children)
	{
		pipex->fd[pipe] = malloc(sizeof(int) * 2);
		if (!pipex->fd[pipe])
			exit_pipex(pipex, -1, "Malloc failure in init");
		pipe++;
	}
	//pipex->fd[pipe] = NULL;
	// printf("argc: %i\n", argc);
}

static char	*get_paths(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pipey;

	pipey = 0;
	if (argc < 5)
		exit_pipex(&pipex, -2, "Too few arguments supplied");
	init_pipex(&pipex, argc);
	pipex.paths = ft_split(get_paths(envp), ':');
	if (!pipex.paths)
		exit_pipex(&pipex, -3, "Malloc failure getting env paths");
	get_commands(&pipex, argv, argc - 1);
	while (pipey < pipex.nr_children - 1)
	{
		if (pipe(pipex.fd[pipey]) == -1)
			exit_pipex(&pipex, 1, "Failed to create pipe");
		pipey++;
	}
	handle_the_children(&pipex, argv, envp);
	close_pipes(&pipex);
	// pipey = 0;
	// while (pipey <= pipex.nr_children - 2)
	// {
	// 	close_pipe(pipex.fd[pipey]);
	// 	pipey++;
	// }
	wait_for_children(&pipex);
	return (0);
}
