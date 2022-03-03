/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:47:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/03 12:28:06 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

/*

Als status -2 is betekent dat dat er een failure was in get_paths and in that case
Im ust free: 

free(pipex->fid)
free_ints(pipex->fd, pipex->nr_children - 1)
free(pipex->fd)
free(pipex->cmd)
*/

void	exit_pipex(t_pipex *pipex, int status, char *message)
{
	if (status == -1)
	{
		while(pipex->current_child)
		{
			free_cmd(&pipex->cmd[pipex->current_child]);
			pipex->current_child--;
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
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->paths)
		free_strings(pipex->paths, nr_strings(pipex->paths));
	if (status)
		perror(message);
	exit(0);
}
