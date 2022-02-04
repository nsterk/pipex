/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:58:01 by nsterk        #+#    #+#                 */
/*   Updated: 2022/02/04 17:45:38 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_cmd
{
	char	**cmdv;
	char	*pathname;
}				t_cmd;

typedef struct s_pipex
{
	char	**paths;
	t_cmd	*cmd;
	char	**cmd1;
	char	**cmd2;
	char	*fullcmd1;
	char	*fullcmd2;
	int		pid1;
	int		pid2;
	int		infile;
	int		outfile;
	int		fd[2];
}				t_pipex;

int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	**ft_split(char const *s, char c);
int		ft_strlcpy(char *dest, const char *src, int size);
int		get_command(char *arg, char ***cmd);
int		get_fullcmd(char **paths, char **cmd, char **fullcmd);
int		draft(t_pipex *pipex, char **argv, int out_arg);
int		get_draft(char **paths, t_cmd *cmd);

// Child processes
void	last_child(t_pipex *pipex, char *file, char **envp);
void	first_child(t_pipex *pipex, char *file, char **envp);

// Pipes
void	close_pipe(t_pipex *pipex);

#endif
