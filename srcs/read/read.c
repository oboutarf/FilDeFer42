/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:07:18 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/04 05:25:58 by oboutarf         ###   ########.fr       */
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


	// printf("%s\n", grid_output);
	// printf("\n\ny is: %d\n\n", y);
	// printf("%s\n",*ft_split(grid_output, ' '));
	// printf("\n\ny_max is : %d\n\n", grid->y_max);
	// printf("\n\n%d\n\n", (grid->x_max * grid->y_max));
	// printf("\n\n%d | %d\n\n", grid->x_max, grid->y_max);
	// printf("\n\nLign is ----->    %s   \n\n", lines[y]);
	// printf( "\n\nx_max is: %d;\ny_max is: %d;\n\n", grid->x_max, grid->y_max);
	// printf("\n\ngrid_x_max is: %d || grid_y_max is: %d || pointer on grid_data is: %p\n\n", grid->x_max, grid->y_max, grid->grid_data);
	// printf("\n\n  --  lines is: %s --  \n\n", lines[i + 7]);
	// printf("\n\n%d\n\n", grid->x_max);
	// printf("\n\n%d\n\n", grid->grid_data[2][2]);
	// printf("\n\n--- grid->x_max is: %d || grid->y_max is: %d ---\n\n", grid->x_max, grid->y_max);
	// printf("grid_x_max is: %d\n", grid->x_max);
	// printf("\n\n%d\n\n", x);
	// printf("\033[0;31m");
	// printf("\n\n%d || %d\n\n", *grid[y], y);
	// printf("\033[0m");
	// printf("\n\n%s || %d\n\n", line, y);
	// printf("\n\n%s || %d\n\n", line, y);
	/* 	while (i < 100)
			printf("\n%s\n", lines[i]);
			i++;
		}
		return (grid); 
	*/