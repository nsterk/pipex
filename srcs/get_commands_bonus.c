/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:39:13 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/02/10 13:50:52 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	get_pathname(char **paths, t_cmd *cmd)
{
	int		i;
	int		found;
	char	*pathslash;

	i = 0;
	found = 0;
	while (!found && paths[i])
	{
		pathslash = ft_strjoin(paths[i], "/");
		cmd->pathname = ft_strjoin(pathslash, cmd->cmdv[0]);
		free(pathslash);
		if (!cmd->pathname)
			return (1);
		if (access(cmd->pathname, F_OK))
		{
			free(cmd->pathname);
			i++;
		}
		else
			found = 1;
	}
	if (!found)
		perror("invalid command");
	return (0);
}

int	get_commands(t_pipex *pipex, char **argv, int out_arg)
{
	int	i;

	i = 2;
	while (i < out_arg)
	{
		if (!argv || !argv[i])
			perror("unable to grab arguments");
		pipex->cmd[i - 2].cmdv = ft_split(argv[i], ' ');
		if (!pipex->cmd[i - 2].cmdv)
			exit_pipex(pipex, -4);
		get_pathname(pipex->paths, &pipex->cmd[i - 2]);
		i++;
	}
	return (0);
}
