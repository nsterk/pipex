/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 01:32:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/27 21:15:23 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <get_next_line.h>
#include "../inc/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

//&& ft_strncmp(line, delimiter, 100)
// static int	ft_strncmp(const char *s1, const char *s2, int len)
// {
// 	int	i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	while (i < len && (s1[i] != '\0' || s2[i] != '\0'))
// 	{
// 		if (s1[i] == s2[i])
// 			i++;
// 		else
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 	}
// 	return (0);
// }

int	read_from_cmdl(char *delimiter)
{
	int		fd1;
	int		fd2;
	char	*line;
	// char	*delimiter;

	fd1 = open("tmp_here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd1 == -1)
	{
		printf("\e[0;31merror: failed to open file\e[0m\n");
		return (-1);
	}
	// delimiter = ft_strgjoin(argv[1], )
	if (get_next_line(STDIN_FILENO, &line) < 0 || !ft_strncmp(line, delimiter, 100))
		return (-1);
	write(fd1, line, ft_strglen(line));
	write(fd1, "\n", 1);
	free(line);
	while (get_next_line(STDIN_FILENO, &line) > 0 && ft_strncmp(line, delimiter, 100))
	{
		write(fd1, line, ft_strglen(line));
		write(fd1, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	fd2 = open("tmp_here_doc", O_RDONLY, 0777);
	close(fd1);
	return (fd2);
}

// void	first_child(t_pipex *pipex, char *file, char **envp)
// {
// 	pipex->infile = read_from_cmdl(pipex->delimiter);
// 	if (pipex->infile < 0)
// 		exit_pipex(pipex, 1, "Failed to open infile");
// 	dup2(pipex->infile, STDIN_FILENO);
// 	dup2(pipex->fd[0][1], STDOUT_FILENO);
// 	close_pipe(pipex->fd[0]);
// 	close(pipex->infile);
// 	if (execve(pipex->cmd[0].pathname, pipex->cmd[0].cmdv, envp) == -1)
// 		exit_pipex(pipex, 127, "Failed to open infile");
// }

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;
// 	// char	*delimiter;

// 	fd = open("tmp_here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	if (!argc || fd == -1)
// 	{
// 		printf("\e[0;31merror: failed to open file\e[0m\n");
// 		return (0);
// 	}
// 	// delimiter = ft_strgjoin(argv[1], )
// 	if (get_next_line(STDIN_FILENO, &line) < 0 || !ft_strncmp(line, argv[1], 100))
// 		return (0);
// 	write(fd, line, ft_strglen(line));
// 	free(line);
// 	while (get_next_line(STDIN_FILENO, &line) > 0 && ft_strncmp(line, argv[1], 100))
// 	{
// 		write(fd, "\n", 1);
// 		write(fd, line, ft_strglen(line));
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// 	// unlink("temp_here_doc");
// }