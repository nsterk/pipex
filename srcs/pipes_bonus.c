/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 14:35:57 by nsterk        #+#    #+#                 */
/*   Updated: 2022/02/11 17:25:34 by naomisterk    ########   odam.nl         */
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
