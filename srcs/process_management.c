/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_management.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: naomisterk <naomisterk@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 17:54:53 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/03/28 12:45:11 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <sys/wait.h>

void	handle_the_children(t_pipex *pipex, char **argv, char **envp)
{
	fork_process(pipex);
	if (pipex->pid[0] == 0)
		first_child(pipex, argv[1], envp);
	pipex->current_child++;
	if (pipex->here_doc)
		waitpid(pipex->pid[0], NULL, 0);
	while (pipex->current_child < (pipex->nr_children - 1))
	{
		fork_process(pipex);
		if (pipex->pid[pipex->current_child] == 0)
			middle_children(pipex, envp);
		pipex->current_child++;
	}
	fork_process(pipex);
	if (pipex->pid[pipex->current_child] == 0)
	{
		if (!pipex->here_doc)
			last_child(pipex, argv[pipex->nr_children + 2], envp);
		else
			last_child(pipex, argv[pipex->nr_children + 3], envp);
	}
}

void	fork_process(t_pipex *pipex)
{
	pipex->pid[pipex->current_child] = fork();
	if (pipex->pid[pipex->current_child] < 0)
		exit_pipex(pipex, 1, "Failed to fork process");
}

void	wait_for_children(t_pipex *pipex)
{
	int	i;
	int	status;

	if (pipex->here_doc)
		i = 1;
	else
		i = 0;
	while (i < pipex->nr_children)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			pipex->status = WEXITSTATUS(status);
		i++;
	}
}
