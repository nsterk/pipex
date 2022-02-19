/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:39:13 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/02/19 11:09:37 by naomisterk    ########   odam.nl         */
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

	i = 0;
	not_found = 1;
	while (not_found > 0 && paths[i])
	{
		not_found = try_pathname(paths[i], cmd);
		i++;
	}
	return (not_found);
}

void	get_paths(t_pipex *pipex, char **envp, char c)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pipex->paths = ft_split(*envp + 5, c);
	if (!pipex->paths)
		exit_pipex(pipex, -3, "Malloc failure getting env paths");
	// return (ft_split(*envp + 5, c));
	// return (*envp + 5);
}

int	get_commands(t_pipex *pipex, char **argv, int out_arg, char **envp)
{
	int	i;
	int	found;

	i = 0;
	get_paths(pipex, envp, ':');
	while (i < (out_arg - 2))
	{
		if (!argv || !argv[i + 2])
			exit_pipex(pipex, -1, "unable to grab arguments");
		pipex->cmd[i].cmdv = ft_split(argv[i + 2], ' ');
		if (!pipex->cmd[i].cmdv)
			exit_pipex(pipex, -4, "Malloc failure");
		found = get_pathname(pipex->paths, &pipex->cmd[i]);
		if (found > 0)
			exit_pipex(pipex, 1, "command not found");
		else if (found < 0)
			exit_pipex(pipex, -4, "Malloc failure");
		i++;
	}
	free_strings(pipex->paths, nr_strings(pipex->paths));
	return (0);
}
