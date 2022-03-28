/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 20:59:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/28 12:36:37 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"
#include <pipex.h>

// size_t		ft_strglen(const char *s)
// {
// 	size_t i;

// 	i = 0;
// 	if (s)
// 	{
// 		while (s[i] != '\0')
// 			i++;
// 	}
// 	return (i);
// }

void	ft_strglcpy(char *dst, const char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strndup(char *src, int n)
{
	char	*str;

	str = malloc(sizeof(*str) * (n + 1));
	if (!str)
		return (NULL);
	ft_strglcpy(str, src, n + 1);
	return (str);
}

char	*ft_strgjoin(char *s1, char *s2, int len_s2)
{
	int		len_s1;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strndup(s2, len_s2));
	len_s1 = ft_strlen(s1);
	str = malloc(sizeof(*str) * (len_s1 + len_s2 + 1));
	if (!str)
		str = NULL;
	else
	{
		ft_strglcpy(str, s1, len_s1 + 1);
		ft_strglcpy(str + len_s1, s2, len_s2 + 1);
	}
	free((char *)s1);
	return (str);
}
