#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <pipex.h>

static void	init_pipex(t_pipex *pipex, int argc)
{
	pipex->paths = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->fullcmd1 = NULL;
	pipex->fullcmd2 = NULL;
	pipex->cmd = malloc(sizeof(t_cmd) * (argc - 3));
	if (!pipex->cmd)
		perror("malloc error");
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
	init_pipex(&pipex, argc);
	pipex.paths = ft_split(get_paths(envp), ':');
	if (get_command(argv[2], &pipex.cmd1))
		perror("failed to get cmd1");
	if (get_command(argv[3], &pipex.cmd2))
		perror("failed to get cmd2");
	if (pipe(pipex.fd) == -1)
		return (1);
	get_fullcmd(pipex.paths, pipex.cmd1, &pipex.fullcmd1);
	get_fullcmd(pipex.paths, pipex.cmd2, &pipex.fullcmd2);
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