/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 14:35:57 by nsterk        #+#    #+#                 */
/*   Updated: 2022/02/14 17:02:09 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
/*
hier nog over nadenken want is er niet misschien een punt in het programma
waar ik maar 1 pipe wil sluiten?
*/
void	close_pipe(int *fd)
{
	if (!fd)
		return ;
	close(fd[0]);
	close(fd[1]);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nr_children - 1)
	{
		close(pipex->fd[i][0]);
		close(pipex->fd[i][1]);
		i++;
	}
}
