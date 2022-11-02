/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:15:27 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/02 19:03:01 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/fdf.h"

static char	**mallocrash(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	*ft_mystrlcpy(char *dest, char *src, int size, int i)
{
	int		j;

	j = 0;
	while (size--)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

static int	tablength(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			i++;
			if (s[i] == '\0')
				return (count);
		}
		while (s[i] != c && s[i])
			i++;
		count++;
	}
	return (count);
}

static int	myanti_c(char const *s, int i, char c)
{
	int		base;

	base = i;
	while (s[i] != c && s[i])
		i++;
	i -= base;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		a;

	i = 0;
	a = 0;
	tab = (char **)malloc(sizeof(char *) * (tablength(s, c) + 1));
	if (!tab)
		return (NULL);
	while (a < tablength(s, c))
	{
		while (s[i] == c)
			i++;
		tab[a] = malloc(sizeof(char) * myanti_c(s, i, c) + 1);
		if (!tab[a])
			return (mallocrash(tab));
		ft_mystrlcpy(tab[a], (char *)s, myanti_c(s, i, c), i);
		while (s[i] != c && s[i])
			i++;
		a++;
	}
	tab[a] = NULL;
	return (tab);
}

