/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 16:39:13 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/03/23 21:11:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	try_pathname(char *path, t_cmd *cmd)
{
	char	*pathslash;

	pathslash = ft_strjoin(path, "/");
	if (!pathslash)
		return (1);
	cmd->pathname = ft_strjoin(pathslash, cmd->cmdv[0]);
	free(pathslash);
	if (!cmd->pathname)
		return (1);
	if (access(cmd->pathname, F_OK))
	{
		free(cmd->pathname);
		cmd->pathname = NULL;
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
	cmd->pathname = NULL;
	if (!access(cmd->cmdv[0], F_OK))
	{
		cmd->pathname = ft_strdup(cmd->cmdv[0]);
		return (0);
	}
	else if (!paths)
		return (1);
	while (not_found > 0 && paths[i])
	{
		not_found = try_pathname(paths[i], cmd);
		i++;
	}
	return (not_found);
}

static void	get_paths(t_pipex *pipex, char **envp, char c)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		return ;
	pipex->paths = ft_split(*envp + 5, c);
	if (!pipex->paths)
		exit_pipex(pipex, 1, "Malloc failure getting env paths");
}

static int	prep_commands(char *str, t_cmd *cmd)
{
	int		cmd_len;
	char	*tmp;

	cmd->cmdv = ft_split(str, ' ');
	if (!cmd->cmdv)
		return (1);
	cmd_len = ft_strlen(cmd->cmdv[0]);
	if (cmd_len < 3)
		return (0);
	if (!ft_strncmp(cmd->cmdv[0][cmd_len - 3], "sed", 3))
	{
		while cmd->cmdv
	}
	return (0);
}

int	get_commands(t_pipex *pipex, char **argv, char **envp)
{
	int	found;

	get_paths(pipex, envp, ':');
	while (pipex->current_child < pipex->nr_children)
	{
		if (!argv || !argv[pipex->current_child + 2])
			exit_pipex(pipex, 1, "unable to grab arguments");
		if (prep_commands(argv[pipex->current_child + 2], \
		&pipex->cmd[pipex->current_child]))
			exit_pipex(pipex, 1, "Malloc failure");
		found = get_pathname(pipex->paths, &pipex->cmd[pipex->current_child]);
		if (found > 0)
			pipex->cmd[pipex->current_child].pathname = NULL;
		else if (found < 0)
			exit_pipex(pipex, 1, "Malloc failure");
		pipex->current_child++;
	}
	pipex->current_child = 0;
	return (0);
}
