/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:39:13 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/02/04 17:18:33 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	get_command(char *arg, char ***cmd)
{
	if (!arg || !(*arg))
		return (1);
	*cmd = ft_split(arg, ' ');
	if (!(*cmd))
		return (2);
	return (0);
}

int	get_fullcmd(char **paths, char **cmd, char **fullcmd)
{
	int		i;
	int		found;
	char	*pathslash;

	i = 0;
	found = 0;
	while (!found && paths[i])
	{
		pathslash = ft_strjoin(paths[i], "/");
		*fullcmd = ft_strjoin(pathslash, cmd[0]);
		if (!(*fullcmd))
			return (1);
		free(pathslash);
		if (access(*fullcmd, F_OK))
		{
			free(*fullcmd);
			i++;
		}
		else
			found = 1;
	}
	if (!found)
		perror("invalid command");
	return (0);
}

int	draft(t_pipex *pipex, char **argv, int out_arg)
{
	int	i;

	i = 2;
	while (i < out_arg)
	{
		if (!argv || !argv[i])
			perror("unable to grab arguments");
		pipex->cmd[i - 2].cmdv = ft_split(argv[i], ' ');
		if (!pipex->cmd[i - 2].cmdv)
			perror("malloc error splitting args");
		i++;
	}
	return (0);
}

