/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 21:24:38 by nsterk        #+#    #+#                 */
/*   Updated: 2022/03/21 18:53:13 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *src)
{
	char	*rstr;
	size_t	len;

	len = ft_strlen((char *)src);
	rstr = (char *)malloc(sizeof(*rstr) * (len + 1));
	if (!rstr)
		return (NULL);
	ft_strlcpy(rstr, src, len + 1);
	return (rstr);
}
