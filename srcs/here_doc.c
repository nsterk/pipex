/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   here_doc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/26 01:32:04 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/27 22:23:19 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <get_next_line.h>
#include <fcntl.h>
#include <stdio.h>

int	read_from_cmdl(char *delimiter)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("tmp_here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd1 == -1)
	{
		printf("\e[0;31merror: failed to open file\e[0m\n");
		return (-1);
	}
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
