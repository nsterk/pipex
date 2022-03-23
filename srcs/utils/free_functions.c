/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: naomisterk <naomisterk@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/20 10:42:06 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/03/23 12:40:06 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_strings(char **strings, int len)
{
	while (len > 0)
	{
		len--;
		if (strings[len])
			free(strings[len]);
	}
	if (strings)
		free(strings);
}

void	free_ints(int **ints, int len)
{
	while (len > 0)
	{
		len--;
		if (ints[len])
			free(ints[len]);
	}
	if (ints)
		free(ints);
}

void	free_cmd(t_cmd *cmd)
{
	free_strings(cmd->cmdv, nr_strings(cmd->cmdv));
	if (cmd->pathname)
		free(cmd->pathname);
}
