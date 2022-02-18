/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:47:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/02/18 16:32:44 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

void	exit_pipex(t_pipex *pipex, int status, char *message)
{
	if (status == -3) // free pipex->cmnd **
	{
		perror(message);
		free(pipex->cmd);
	}
	else if (status == -4)
		perror("Malloc error separating arguments and flags"); // free pipex->cmnd->cmdv  **get_commands
	perror(message);
	exit(0);
}
