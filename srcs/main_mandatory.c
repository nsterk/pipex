/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_mandatory.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 13:00:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/25 20:12:10 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <time.h>
#include <pipex.h>

static void	init_pipex(t_pipex *pipex, int argc)
{
	int	pipe;

	pipe = 0;
	pipex->paths = NULL;
	pipex->status = 0;
	pipex->nr_children = argc - 3;
	pipex->current_child = 0;
	pipex->cmd = malloc(sizeof(t_cmd) * pipex->nr_children);
	pipex->pid = malloc(sizeof(int) * pipex->nr_children);
	pipex->fd = malloc(sizeof(pipex->fd) * (pipex->nr_children - 1));
	if (!pipex->cmd || !pipex->pid || !pipex->fd)
		exit_pipex(pipex, 1, "Malloc failure");
	while (pipe < pipex->nr_children - 1)
	{
		pipex->fd[pipe] = malloc(sizeof(int) * 2);
		if (!pipex->fd[pipe])
			exit_pipex(pipex, 1, "Malloc failure");
		pipe++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		perror("Provide exactly four arguments");
		return (0);
	}
	init_pipex(&pipex, argc);
	get_commands(&pipex, argv, envp);
	open_pipes(&pipex);
	handle_the_children(&pipex, argv, envp);
	close_pipes(&pipex);
	wait_for_children(&pipex);
	exit_pipex(&pipex, pipex.status, NULL);
	return (pipex.status);
}
