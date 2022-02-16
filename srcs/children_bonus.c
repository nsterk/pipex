/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 19:00:00 by nsterk		   #+#    #+#                 */
/*   Updated: 2022/02/04 15:11:34 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <fcntl.h>

void	first_child(t_pipex *pipex, char *file, char **envp)
{
	pipex->infile = open(file, O_RDONLY, 0777);
	if (pipex->infile == -1)
		perror("couldnt open infile");
	dup2(pipex->fd[0][1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	close_pipe(pipex->fd[0]);
	close(pipex->infile);
	if (execve(pipex->cmd[0].pathname, pipex->cmd[0].cmdv, envp) == -1)
		perror("Execve process 1 failed");
}

void	middle_children(t_pipex *pipex, char **envp)
{
	dup2(pipex->fd[pipex->current_child - 1][0], STDIN_FILENO);
	dup2(pipex->fd[pipex->current_child][1], STDOUT_FILENO);
	close_pipes(pipex);
	if (execve(pipex->cmd[pipex->current_child].pathname, \
		pipex->cmd[pipex->current_child].cmdv, envp) == -1)
		perror("execve in one of middle children");
}

// void	last_child_test(t_pipex *pipex, char *file, char **envp)
// {
// 	pipex->outfile = open(file, O_WRONLY | O_CREAT, 0777);
// 	if (pipex->outfile == -1)
// 		perror("Failed to open outfile");
// 	dup2(pipex->fd[pipex->nr_children - 1][0], STDIN_FILENO);
// 	dup2(pipex->outfile, STDOUT_FILENO);
// 	close(pipex->outfile);
// 	close_pipe(pipex->fd[pipex->nr_children - 1]);
// 	if (execve(pipex->cmd[1].pathname, pipex->cmd[1].cmdv, envp) == -1)
// 		perror("execve process 2 failed");
// }

void	last_child_test(t_pipex *pipex, char *file, char **envp)
{
	pipex->outfile = open(file, O_WRONLY | O_CREAT, 0777);
	if (pipex->outfile == -1)
		perror("Failed to open outfile");
	if (pipex->nr_children > 2)
		dup2(pipex->fd[pipex->nr_children - 2][0], STDIN_FILENO);
	else
		dup2(pipex->fd[0][0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close_pipes(pipex);
	if (execve(pipex->cmd[pipex->current_child].pathname, pipex->cmd[pipex->current_child].cmdv, envp) == -1)
		perror("execve process 2 failed");
}

int	handle_the_children(t_pipex *pipex, char **argv, char **envp)
{
	int	i;

	i = 1;
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
		return (2);
	if (pipex->pid[0] == 0)
		first_child(pipex, argv[1], envp);
	while (i < (pipex->nr_children - 1))
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			return (3);
		if (pipex->pid[i] == 0)
			middle_children(pipex, envp);
		pipex->current_child++;
		i++;
	}
	pipex->pid[pipex->nr_children - 1] = fork();
	if (pipex->pid[pipex->nr_children - 1] < 0)
		return (3);
	if (pipex->pid[pipex->nr_children - 1] == 0)
		last_child_test(pipex, argv[pipex->nr_children + 2], envp);
	return (0);
}

void	wait_for_children(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nr_children)
	{
		waitpid(pipex->pid[i], NULL, 0);
		i++;
	}
}
