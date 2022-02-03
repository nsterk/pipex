#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <pipex.h>

static char	*get_paths(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static void	init_pipex(t_pipex *pipex)
{
	pipex->paths = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
	pipex->fullcmd1 = NULL;
	pipex->fullcmd2 = NULL;
}

// static void print_array(char **str)
// {
// 	while (*str)
// 	{
// 		printf("%s\n", *str);
// 		str++;
// 	}
// 	printf("%s\n", *str);
// 	return ;
// }


int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	// int	fd[2];
	int	i;
	// int	file;
	//	int	file2;
	if (argc == 2)
		i = 0;
	init_pipex(&pipex);
	pipex.paths = ft_split(get_paths(envp), ':');
	if (get_command(argv[1], &pipex.cmd1))
		perror("failed to get cmd1");
	if (get_command(argv[2], &pipex.cmd2))
		perror("failed to get cmd2");
	// if (pipe(fd) == -1)
	// 	return (1);
	i = 0;
	get_fullcmd(pipex.paths, pipex.cmd1, &pipex.fullcmd1);
	get_fullcmd(pipex.paths, pipex.cmd2, &pipex.fullcmd2);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (2);
	if (pipex.pid1 == 0)
	{	// process 1: ls
		// dup2(fd[1], STDOUT_FILENO);
		// close(fd[0]);
		// close(fd[1]);
		if (execve(pipex.fullcmd1, pipex.cmd1, envp) == -1)
			perror("execve process 1 failed");		
	}
	// int	pid2 = fork();
	// if (pid2 < 0)
	// 	return (3);
	// if (pid2 == 0){// process 2: grep
	// 	// file = open("pippy.txt", O_WRONLY | O_CREAT, 0777);
	// 	// if (file == -1)
	// 	// {	
	// 	// 	printf("failed to open or create file");
	// 	// 	exit(0);
	// 	// }
	// 	// dup2(fd[0], STDIN_FILENO);
	// 	// dup2(file, STDOUT_FILENO);
	// 	// close(file);
	// 	// close(fd[0]);
	// 	// close(fd[1]);
	// 	printf("this should show up in pippy.txt");
	// 	if (execve(pipex.fullcmd2, pipex.cmd2, envp) == -1)
	// 		perror("execv process 2 failed");
	// }
	// close(fd[0]);
	// close(fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	// waitpid(pipex.pid2, NULL, 0);
	return (0);
}