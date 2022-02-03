#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <pipex.h>

static char *get_paths(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static void print_array(char **str)
{

	printf("%s\n", str[0]);
	while (*str)
	{
		printf("%s\n", *str);
		str++;
	}
	printf("%s\n", *str);
	return ;
}


	// printf("argv[0]: %s		argc: %i\n", argv[0], argc);

int	main(int argc, char **argv, char **envp)
{
	// char	*cmd1[] = {"/bin/ls", NULL};
	// char	*cmd2[] = {"/usr/bin/grep", "pip", NULL};
	char	**paths;
	char	*env_paths;
	// char	*env;
	char	**cmd1;
	char	**cmd2;
	char	*pathslash;
	char	*fullcmd;
	int		found;
	// char	*cmd1[] = {"ls", NULL};
	// char	*cmd2[] = {"grep", "pip", NULL};
	// int	fd[2];
	int	pid1;
	int	i;
	// int	file;
	//	int	file2;
	printf("%s%i\n", argv[0], argc);
	env_paths = get_paths(envp);
	paths = ft_split(env_paths, ':');
	cmd1 = ft_split(argv[1], ' ');
	cmd2 = ft_split(argv[2], ' ');
	print_array(cmd1);
	// if (pipe(fd) == -1)
	// 	return (1);
	i = 0;
	found = 0;
	while (!found)
	{
		pathslash = ft_strjoin(paths[i], "/");
		fullcmd = ft_strjoin(pathslash, cmd1[0]);
		free(pathslash);
		// printf("%s\n", fullcmd);
		if(access(fullcmd, F_OK))
			i++;
		else
			found = 1;
	}
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0){	// process 1: ls
		// dup2(fd[1], STDOUT_FILENO);
		// close(fd[0]);
		// close(fd[1]);
		if (execve(argv[1], cmd1, paths) == -1)
			perror("execve process 1 failed");
			
	}
	// int	pid2 = fork();
	// if (pid2 < 0)
	// 	return (3);
	// if (pid2 == 0){// process 2: grep
	// 	file = open("pippy.txt", O_WRONLY | O_CREAT, 0777);
	// 	if (file == -1)
	// 	{	
	// 		printf("failed to open or create file");
	// 		exit(0);
	// 	}
	// 	dup2(fd[0], STDIN_FILENO);
	// 	dup2(file, STDOUT_FILENO);
	// 	close(file);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	printf("this should show up in pippy.txt");
	// 	if (execv(cmd2[0], cmd2) == -1)
	// 		perror("execv process 2 failed");
	// }
	// close(fd[0]);
	// close(fd[1]);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	return (0);
}