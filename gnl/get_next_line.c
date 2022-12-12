/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:12:05 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/01 19:03:15 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int			all_length;
	char		*dest;
	size_t		l_s1;
	int			i;
	size_t		j;

	i = 0;
	j = 0;
	l_s1 = ft_strlen(s1);
	if (!s1 && !s2)
		return (NULL);
	all_length = (l_s1 + ft_strlen(s2));
	if (all_length == 0)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (all_length + 1));
	if (!dest)
		return (NULL);
	while (j < l_s1)
		dest[i++] = s1[j++];
	j = 0;
	while (i < all_length)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (free(s1), dest);
}

char	*ft_getbn(char *lgn, int s_bin)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(sizeof(char) * (s_bin + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s_bin + 1 > 0)
	{
		dest[i] = lgn[i];
		if (dest[i] == '\n')
			break ;
		s_bin--;
		i++;
	}
	dest[i + 1] = 0;
	return (free(lgn), dest);
}

void	ft_mylstbuf(char *buf, char *lgn, int s_bin)
{
	int		i;

	i = 0;
	while (lgn[s_bin])
	{
		buf[i++] = lgn[s_bin];
		s_bin++;
	}
	buf[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	int				s_bin;
	char			*lgn;
	int				vrf;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	vrf = 1;
	lgn = NULL;
	lgn = ft_strjoin(lgn, buf);
	while (!ft_strbn(lgn))
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		vrf = read(fd, buf, BUFFER_SIZE);
		if (buf[0] == 0 && vrf <= 0)
			return (NULL);
		lgn = ft_strjoin(lgn, buf);
	}
	s_bin = ft_strbn(lgn);
	ft_mylstbuf(buf, lgn, s_bin);
	lgn = ft_getbn(lgn, s_bin);
	return (lgn);
}
