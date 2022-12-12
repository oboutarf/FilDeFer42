/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:59:04 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 11:36:34 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_data	*assign_coordonnates_max(char *buf)
{
	t_data	*grid;

	grid = malloc(sizeof(t_data));
	grid = get_number_of_lines(buf, grid);
	return (grid);
}

int	data_width(char *line)
{
	int		count;
	int		cnt;

	cnt = 0;
	count = 0;
	while (line[cnt] != '\n')
	{
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

t_data	*get_number_of_lines(char *buf, t_data *grid)
{
	int		count;
	int		x;
	int		y;

	y = 0;
	count = 0;
	x = data_width(buf);
	while (buf[count++])
		if (buf[count] == '\n')
			y++;
	grid->x_max = x;
	grid->y_max = y;
	return (grid);
}
