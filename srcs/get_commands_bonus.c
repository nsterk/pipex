/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:39:13 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/02/18 17:09:00 by naomisterk    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static int	try_pathname(char *path, t_cmd *cmd)
{
	char	*pathslash;

	pathslash = ft_strjoin(path, "/");
	if (!pathslash)
		return (-1);
	cmd->pathname = ft_strjoin(pathslash, cmd->cmdv[0]);
	free(pathslash);
	if (!cmd->pathname)
		return (-1);
	if (access(cmd->pathname, F_OK))
	{
		free(cmd->pathname);
		return (1);
	}
	else
		return (0);
}

static int	get_pathname(char **paths, t_cmd *cmd)
{
	int		i;
	int		not_found;
	// char	*pathslash;

	i = 0;
	not_found = 1;
	while (not_found > 0 && paths[i])
	{
		not_found = try_pathname(paths[i], cmd);
		i++;
		// pathslash = ft_strjoin(paths[i], "/");
		// if (!pathslash)
		// 	return (1);
		// cmd->pathname = ft_strjoin(pathslash, cmd->cmdv[0]);
		// free(pathslash);
		// if (!cmd->pathname)
		// 	return (1);
		// if (access(cmd->pathname, F_OK))
		// {
		// 	free(cmd->pathname);
		// 	i++;
		// }
		// else
		// 	not_found = 0;
	}
	return (not_found);
}

int	get_commands(t_pipex *pipex, char **argv, int out_arg)
{
	int	i;
	int	found;

	i = 2;
	while (i < out_arg)
	{
		if (!argv || !argv[i])
			exit_pipex(pipex, -1, "unable to grab arguments");
		pipex->cmd[i - 2].cmdv = ft_split(argv[i], ' ');
		if (!pipex->cmd[i - 2].cmdv)
			exit_pipex(pipex, -4, "Malloc failure");
		found = get_pathname(pipex->paths, &pipex->cmd[i - 2]);
		if (found < 0)
			exit_pipex(pipex, 1, "command not found");
		else if (found > 0)
			exit_pipex(pipex, -4, "Malloc failure");
		i++;
	}
	return (0);
}
