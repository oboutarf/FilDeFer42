/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 05:12:24 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 11:36:05 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_grid_data(t_data *grid)
{
	int		y;
	int		x;

	x = 0;
	y = 0;
	while (y <= grid->y_max)
	{
		x = 0;
		if (y + 1 == grid->y_max)
			break ;
		while (x < grid->x_max && y <= grid->y_max)
		{
			if (x + 1 == grid->x_max)
				break ;
			printf("[%d][%d] = %d\n", y, x, grid->grid_data[y][x]);
			x++;
		}
		printf("\n\n");
		y++;
	}
}

void	print_line(t_vct *line)
{
	while (line->next)
	{
		printf("LINES == %f  ---  %f    -%f\n", line->x, line->y, line->is_last);
		if (!line)
			return ;
		line = line->next;
	}
}
