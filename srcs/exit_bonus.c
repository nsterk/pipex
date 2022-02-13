/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:47:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/02/10 15:07:21 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	exit_pipex(t_pipex *pipex, int status)
{
	if (status == -2)
		perror("Incorrect nr of arguments"); //no free necessary
	else if (status == -1) // no free necessary
		perror("Malloc failure in init");
	else if (status == -3) // free pipex->cmnd **
	{
		perror("Malloc error getting paths");
		free(pipex->cmd);
	}
	else if (status == -4)
		perror("Malloc error separating arguments and flags"); // free pipex->cmnd->cmdv  **get_commands
	exit(0);
}
