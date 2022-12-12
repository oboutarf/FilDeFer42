/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:58:01 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/11 23:41:46 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)s;
	while (i < n)
	{
		s1[i] = c;
		i++;
	}
	return (s1);
}

void	free_l(t_vct **line, int size)
{
	t_vct	*fr_l;

	if (!(*line))
		return ;
	while (size > 0)
	{
		fr_l = (*line)->next;
		free((*line));
		(*line) = fr_l;
		size--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (size && (65535 / size) < nmemb)
		return (NULL);
	alloc = malloc((size * nmemb));
	if (!alloc)
		return (NULL);
	ft_memset(alloc, '\0', size * nmemb);
	return (alloc);
}


t_data	*malloc_grid(t_data *grid, int y)
{
	grid->grid_data = malloc(sizeof(int *) * (grid->y_max));
	while (y < grid->y_max)
	{
		grid->grid_data[y] = ft_calloc(sizeof(int), (grid->x_max));
		y++;
	}
	return (grid);
}
