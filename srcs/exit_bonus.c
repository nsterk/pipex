/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_bonus.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 19:47:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/02/19 20:46:43 by naomisterk    ########   odam.nl         */
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

void	free_strings(char **strings, int len)
{
	while (len)
	{
		len--;
		free(strings[len]);
	}
	free(strings);
}

void	free_ints(int **ints, int len)
{
	while(len)
	{
		len--;
		free(ints[len]);
	}
	free(ints);
}

void	free_cmd(t_cmd *cmd)
{
	free_strings(cmd->cmdv, nr_strings(cmd->cmdv));
	free(cmd->pathname);
}

void	exit_pipex(t_pipex *pipex, int status, char *message)
{
	// if (status > 0)
	// {
		
	// }
	
	if (status == -3) // free pipex->cmnd **
	{
		perror(message);
		free(pipex->cmd);
	}
	else if (status == -4)
		perror("Malloc error separating arguments and flags"); // free pipex->cmnd->cmdv  **get_commands
	if (status)
		perror(message);
	exit(0);
}
