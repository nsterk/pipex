/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:47:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/04 18:04:28 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static void	choose_free_cmd(t_pipex *pipex, int status)
{
	if (status == -1)
	{
		while (pipex->current_child)
		{
			pipex->current_child--;
			free_cmd(&pipex->cmd[pipex->current_child]);
		}
	}
	if (status > 0)
	{
		while (pipex->current_child <= pipex->nr_children - 1)
		{
			free_cmd(&pipex->cmd[pipex->current_child]);
			pipex->current_child++;
		}
	}
}

void	exit_pipex(t_pipex *pipex, int status, char *message)
{
	choose_free_cmd(pipex, status);
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->paths)
		free_strings(pipex->paths, nr_strings(pipex->paths));
	if (pipex->fd)
		free_ints(pipex->fd, pipex->nr_children - 1);
	if (status)
		perror(message);
	exit(0);
}