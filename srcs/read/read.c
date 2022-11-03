/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:07:18 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/03 21:36:58 by oboutarf         ###   ########.fr       */
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
		if (line[cnt] == ' ')
			count++;
		cnt++;
	}
	return (count - 1);
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
	while (buf[count++] && buf[count + 1])
		if (buf[count] == '\n')
			y++;
	grid->x_max = x;
	grid->y_max = y;
	return (grid);
}


int	line_len()
{
	
}


char 	*get_line(char *src)
{
	// char	**cut_coordonnates;
	char 	*newcut_backslach_n;
	int		i = 0;
	r_data	*grid;

	// int		x = 0;
	newcut_backslach_n = malloc(sizeof(char)*);
	while (src[i] != '\n')
	{
		newcut_backslach_n[i] = src[i];
		i++;
	}
}

r_data	*push_coordonnates(r_data *grid, char *grid_output)
{
	char	*line;
	int		x;
	int		i;

	line = get_line(grid_output);
}







r_data	*assign_coordonnates_max(char *buf)
{
	r_data 		*grid;
	int			number_lines;


	grid = malloc(sizeof(r_data));
	grid = get_number_of_lines(buf, grid);
	// printf( "\n\nx_max is: %d;\ny_max is: %d;\n\n", grid->x_max, grid->y_max);
	return (grid);
}

r_data	*malloc_grid(r_data *grid, int y)
{
	grid->grid_data = malloc(sizeof(int *) * (grid->y_max + 1));
	while (y < grid->y_max)
	{
		grid->grid_data[y] = malloc(sizeof(int) * (grid->x_max + 1));
		y++;
	}
}

r_data *parse_grid(char *input_file, int fd)
{
	char 		buf[BUFFER_SIZE];
    r_data		*grid;
	int			number_lines;
	int			y = 0;

    fd = open(input_file, O_RDONLY);
	ft_bzero(buf, BUFFER_SIZE);
	read(fd, buf, BUFFER_SIZE);
	grid = assign_coordonnates_max(buf);
	grid = malloc_grid(grid, y);
	grid = push_coordonnates(grid, buf);
    close(fd);
}


















































		// printf("\033[0;31m");
		// printf("\n\n%d || %d\n\n", *grid[y], y);
		// printf("\033[0m");
		// printf("\n\n%s || %d\n\n", line, y);
		// printf("\n\n%s || %d\n\n", line, y);

		/* int	*write_data(char **line)
		{
			int		*grid_x;
			int		i = 0;
			int		j = 0;

			grid_x = malloc(sizeof(int) * (ft_strlen(line[i])+ 10));
			while (line[i])
			{
				grid_x[j] = ft_atoi(line[i]);
				i++;
				j++;
			}
			return (grid_x);
		} */