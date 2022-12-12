/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:07:18 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/11 23:48:17 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(char *nptr)
{
	int		mns;
	int		num;
	int		i;

	i = 0;
	num = 0;
	mns = 1;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-')
		mns = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	num *= mns;
	return (num);
}

void	free_tab(char **_free_t_)
{
	int		j;

	j = 0;
	while (_free_t_[j])
	{
		free(_free_t_[j]);
		j++;
	}
	free(_free_t_);
}

t_data	*push_coordonnates(t_data *grid, char *grid_output)
{
	char	**lines;
	int		x;
	int		y;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	lines = ft_split(grid_output, ' ');
	while (y < grid->y_max)
	{
		x = 0;
		while (x + 1 < grid->x_max)
		{
			grid->grid_data[y][x] = ft_atoi(lines[i]);
			x++;
			i++;
		}
		y++;
	}
	free_tab(lines);
	lines = NULL;
	return (grid);
}

t_data	*parse_grid(int fd)
{
	t_data			*grid;
	char			*buf;
	char			*lgn;
	int				y;

	y = 0;
	lgn = NULL;
	buf = NULL;
	while (1)
	{
		lgn = ft_strjoin(lgn, buf);
		free(buf);
		buf = get_next_line(fd);
		if (buf == NULL)
			break ;
	}
	if (lgn == NULL)
		return (NULL);
	grid = assign_coordonnates_max(lgn);
	grid = malloc_grid(grid, y);
	grid = push_coordonnates(grid, lgn);
	free(lgn);
	close(fd);
	return (grid);
}
