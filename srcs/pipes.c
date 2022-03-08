/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 14:35:57 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/08 09:34:09 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	close_pipe(int *fd)
{
	if (!fd)
		return ;
	close(fd[0]);
	close(fd[1]);
}

void	open_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nr_children - 1)
	{
		if (pipe(pipex->fd[i]) == -1)
			exit_pipex(pipex, 1, "Failure opening pipe");
		i++;
	}
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
