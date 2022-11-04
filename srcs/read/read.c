/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:07:18 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/04 06:22:35 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/fdf.h"

int	data_width(char *line)
{
	int		count;
	int		cnt;
	
	cnt = 0;
	count = 0;
	while (line[cnt] != '\n')
	{
		//  && line[cnt + 1] != '\n'     -> Depends on case, if whitespace present before '\n'
		if (line[cnt] == ' ')
		{
			count++;
			while (line[cnt] == ' ')
				cnt++;
		}
		else
			cnt++;
	}
	return (count);
}

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

r_data *get_number_of_lines(char *buf, r_data *grid)
{
	int	count = 0;
	int	x = 0;
	int	y = 0;

	x = data_width(buf);
	while (buf[count++])
		if (buf[count] == '\n')
			y++;
	grid->x_max = x;
	grid->y_max = y;
	return (grid);
}

r_data	*push_coordonnates(r_data *grid, char *grid_output)
{
	char 	**lines;
	int		x = 0;
	int		y = 0;
	int		stop = 0;
	int		i = 0;

	lines = ft_split(grid_output, ' ');
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			grid->grid_data[y][x] = ft_atoi(lines[i]);
			x++;
			i++;
		}
		y++;
	}
	return (grid);
}

r_data	*assign_coordonnates_max(char *buf)
{
	r_data 		*grid;

	grid = malloc(sizeof(r_data));
	grid = get_number_of_lines(buf, grid);
	return (grid);
}

r_data	*malloc_grid(r_data *grid, int y)
{
	while (y < grid->y_max)
	{
		if (y == 0)
			grid->grid_data = malloc(sizeof(int *) * (grid->y_max));
		grid->grid_data[y] = malloc(sizeof(int) * (grid->x_max));
		y++;
	}
	return (grid);
}

r_data *parse_grid(char *input_file, int fd)
{
	char 		buf[BUFFER_SIZE];
    r_data		*grid;
	int			number_lines;
	int			y = 0;
	int			y1 = 0;
	int			x = 0;	

    fd = open(input_file, O_RDONLY);
	ft_bzero(buf, BUFFER_SIZE);
	read(fd, buf, BUFFER_SIZE);
	grid = assign_coordonnates_max(buf);
	grid = malloc_grid(grid, y);
	grid = push_coordonnates(grid, buf);
	return (grid);
    close(fd);
}
