#include <sys/wait.h>
#include <time.h>
#include <pipex.h>

static void	init_pipex(t_pipex *pipex, int argc)
{
	pipex->paths = NULL;
	pipex->cmd = malloc(sizeof(t_cmd) * (argc - 3));
	if (!pipex->cmd)
		exit_pipex(pipex, -1);
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

	if (argc != 5)
		exit_pipex(&pipex, -2, "Incorrect nr of arguments");
	init_pipex(&pipex, argc);
	pipex.paths = ft_split(get_paths(envp), ':');
	if (!pipex.paths)
		exit_pipex(&pipex, -3, "Malloc failure");
	get_commands(&pipex, argv, argc - 1);
	if (pipe(pipex.fd) == -1)
		perror("Failed to create pipe");
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (2);
	if (pipex.pid1 == 0)
		first_child(&pipex, argv[1], envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		return (3);
	if (pipex.pid2 == 0)
		last_child(&pipex, argv[argc - 1], envp);
	close_pipe(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}