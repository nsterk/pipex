/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: naomisterk <naomisterk@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/20 10:42:06 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/03/21 18:38:36 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
	while (len)
	{
		len--;
		free(ints[len]);
	}
	free(ints);
}

void	free_cmd(t_cmd *cmd)
{
	free_strings(cmd->cmdv, nr_strings(cmd->cmdv));
	if (cmd->pathname)
		free(cmd->pathname);
}
