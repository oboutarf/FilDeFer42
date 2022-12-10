/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:07:18 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/22 19:34:01 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/fdf.h"

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
	return (count + 1);
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
	int		i = 0;

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
	grid->grid_data = malloc(sizeof(int *) * (grid->y_max));
	while (y < grid->y_max)
	{
		grid->grid_data[y] = ft_calloc(sizeof(int), (grid->x_max));
		y++;
	}
	return (grid);
}

r_data *parse_grid(int fd)
{
	char 		*buf;
    r_data		*grid;
	char		*lgn;
	int			y;

	y = 0;
	lgn = NULL;
	buf = ft_calloc(sizeof(char), BUFFER_SIZE);
	while (1)
	{
		lgn = ft_strjoin(lgn, buf);
		buf = get_next_line(fd);
		if (buf == NULL)
			break ;
	}
	// printf("%s", lgn);
	grid = assign_coordonnates_max(lgn);
	grid = malloc_grid(grid, y);
	grid = push_coordonnates(grid, lgn);
    close(fd);
	return (grid);
}
