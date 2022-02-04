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
		perror(NULL);
	dup2(pipex->fd[1], STDOUT_FILENO);
	dup2(pipex->infile, STDIN_FILENO);
	close_pipe(pipex);
	if (execve(pipex->cmd[0].pathname, pipex->cmd[0].cmdv, envp) == -1)
		perror("Execve process 1 failed");
}

void	last_child(t_pipex *pipex, char *file, char **envp)
{
	pipex->outfile = open(file, O_WRONLY | O_CREAT, 0777);
	if (pipex->outfile == -1)
		perror("Failed to open outfile");
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close_pipe(pipex);
	if (execve(pipex->cmd[1].pathname, pipex->cmd[1].cmdv, envp) == -1)
		perror("execve process 2 failed");
}
