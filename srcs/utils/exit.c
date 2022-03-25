/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:47:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/25 13:33:44 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// static void	choose_free_cmd(t_pipex *pipex, int status)
// {
// 	if (status == 1)
// 	{
// 		while (pipex->current_child)
// 		{
// 			pipex->current_child--;
// 			free_cmd(&pipex->cmd[pipex->current_child]);
// 		}
// 	}
// 	if (status > 1)
// 	{
// 		while (pipex->current_child <= pipex->nr_children - 1)
// 		{
// 			free_cmd(&pipex->cmd[pipex->current_child]);
// 			pipex->current_child++;
// 		}
// 	}
// }

void	exit_pipex(t_pipex *pipex, int status, char *message)
{
	int	i;

	i = 0;
	while (i < pipex->nr_children)
	{
		free_cmd(&pipex->cmd[i]);
		i++;
	}
	if (pipex->pid)
		free(pipex->pid);
	if (pipex->paths)
		free_strings(pipex->paths, nr_strings(pipex->paths));
	if (pipex->fd)
		free_ints(pipex->fd, pipex->nr_children - 1);
	if (status)
		perror(message);
	exit(status);
}
