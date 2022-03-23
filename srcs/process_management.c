/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_management.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: naomisterk <naomisterk@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 17:54:53 by naomisterk    #+#    #+#                 */
/*   Updated: 2022/03/23 14:45:06 by nsterk        ########   odam.nl         */
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
	while (pipex->current_child < (pipex->nr_children - 1))
	{
		fork_process(pipex);
		if (pipex->pid[pipex->current_child] == 0)
			middle_children(pipex, envp);
		pipex->current_child++;
	}
	fork_process(pipex);
	if (pipex->pid[pipex->current_child] == 0)
		last_child(pipex, argv[pipex->nr_children + 2], envp);
	// free_cmd(&pipex->cmd[pipex->current_child]);
	// free(pipex->cmd);
}

void	fork_process(t_pipex *pipex)
{
	// if (pipex->current_child > 0)
	// 	free_cmd(&pipex->cmd[pipex->current_child - 1]);
	pipex->pid[pipex->current_child] = fork();
	if (pipex->pid[pipex->current_child] < 0)
		exit_pipex(pipex, 1, "Failed to fork process");
}

void	wait_for_children(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->nr_children)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			pipex->status = WEXITSTATUS(status);
		i++;
	}
	// while (i < pipex->nr_children)
	// {
	// 	waitpid(pipex->pid[i], &(pipex->status), 0);
	// 	if (WIFEXITED(pipex->status))
	// 		pipex->status = WEXITSTATUS(pipex->status);
	// 	printf("%i:		%i\n", i, WEXITSTATUS(pipex->status));
	// 	i++;
	// }
}
