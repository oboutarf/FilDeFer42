/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:07:18 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/02 22:32:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/fdf.h"

int	ft_atoi(const char *nptr)
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
	return (num * mns);
}

int	data_width(char *line)
{
	int		count;
	int		cnt;
	
	cnt = 0;
	count = 0;
	while (line[cnt])
	{
		if (line[cnt] == ' ')
			count++;
		cnt++;
	}
	return (count);
}

int	**alloc_grid(char *input_file, int fd)
{
	int		**new;
	char	*line;
	int		x;
	int		y;

	fd = open(input_file, O_RDONLY);
	line = get_next_line(fd);
	x = data_width(line);
	free(line);
	while (line = get_next_line(fd))
		y++;
	new = malloc((sizeof(int *) * y) + 1);
	while (y > 0)
	{
		new[y] = malloc((sizeof(int) * x) + 1);
		y--;
	}
	close (fd);
	return (new);
}

int	*write_data(char **line)
{
	int		*grid_x;
	int		i = 0;
	int		j = 0;

	while (line[i])
	{
		grid_x[j] = ft_atoi(line[i]);
		i++;
		j++;
	}
	return (grid_x);
}

int	**grid_data(char *input_file, int fd)
{
	char	**write_line;
	int		**grid;
	char	*line;
	int		y = 0;

	fd = open(input_file, O_RDONLY);
	while (line = get_next_line(fd))
	{
		printf("\n\nWENT THERE!\n\n");
		write_line = ft_split(line, ' ');
		printf("%s", write_line[y]);
		grid[y] = write_data(write_line);
		y++;
	}
}

int	**parse_grid(char *input_file, int fd)
{
    int	**grid;

    fd = open(input_file, O_RDONLY);
    grid = alloc_grid(input_file, fd);
	grid = grid_data(input_file, fd);
    close(fd);
}