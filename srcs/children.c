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
	if (pipex->here_doc)
		pipex->infile = read_from_cmdl(pipex->delimiter);
	else
		pipex->infile = open(file, O_RDONLY, 0777);
	if (pipex->infile == -1)
		exit_pipex(pipex, 1, "Failed to open infile");
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->fd[0][1], STDOUT_FILENO);
	close_pipes(pipex);
	close(pipex->infile);
	if (execve(pipex->cmd[0].pathname, pipex->cmd[0].cmdv, envp) == -1)
		exit_pipex(pipex, 127, "Failed to execute first command");
}

void	middle_children(t_pipex *pipex, char **envp)
{
	dup2(pipex->fd[pipex->current_child - 1][0], STDIN_FILENO);
	dup2(pipex->fd[pipex->current_child][1], STDOUT_FILENO);
	close_pipes(pipex);
	if (execve(pipex->cmd[pipex->current_child].pathname, \
		pipex->cmd[pipex->current_child].cmdv, envp) == -1)
		exit_pipex(pipex, 127, "Failed to execute one of middle commands");
}

void	last_child(t_pipex *pipex, char *file, char **envp)
{
	pipex->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile == -1)
		exit_pipex(pipex, 1, "Failed to open outfile");
	if (pipex->nr_children > 2)
		dup2(pipex->fd[pipex->nr_children - 2][0], STDIN_FILENO);
	else
		dup2(pipex->fd[0][0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	close(pipex->outfile);
	close_pipes(pipex);
	if (execve(pipex->cmd[pipex->current_child].pathname, \
		pipex->cmd[pipex->current_child].cmdv, envp) == -1)
		exit_pipex(pipex, 127, "Failed to execute last command");
}
