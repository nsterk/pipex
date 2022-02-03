/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: naomisterk <naomisterk@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 19:00:00 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/02/03 21:50:34 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <fcntl.h>

void	first_child(t_pipex *pipex, char *file, char **envp)
{
	pipex->infile = open(file, O_RDONLY, 0777);
	if (pipex->infile == -1)
		perror("Failed to open infile");
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(pipex->fullcmd1, pipex->cmd1, envp) == -1)
		perror("execve process 1 failed");
}

void	last_child(t_pipex *pipex, char *file, char **envp)
{
	pipex->outfile = open(file, O_WRONLY | O_CREAT, 0777);
	if (pipex->outfile == -1)
		perror("Failed to open outfile");
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(pipex->fullcmd2, pipex->cmd2, envp) == -1)
		perror("execve process 2 failed");
}
