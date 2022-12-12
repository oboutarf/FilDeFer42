/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:56:30 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 16:56:56 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_scale_big_maps(t_data *grid, float *scaling)
{
	if (grid->x_max > 101 && grid->x_max <= 201
		&& grid->y_max > 100 && grid->y_max <= 200)
	{
		scaling[0] = 3;
		scaling[1] = 3;
	}
	if (grid->x_max == 501 && grid->y_max == 500)
	{
		scaling[0] = 2;
		scaling[1] = 1;
	}
}

void	parse_scale(t_data *grid, float *scaling)
{
	if (grid->x_max <= 21 && grid->y_max <= 20)
	{
		scaling[0] = 40;
		scaling[1] = 6;
	}
	if (grid->x_max > 21 && grid->x_max <= 51
		&& grid->y_max > 20 && grid->y_max <= 50)
	{
		scaling[0] = 20;
		scaling[1] = 10;
	}
	if (grid->x_max > 51 && grid->x_max <= 101
		&& grid->y_max > 50 && grid->y_max <= 100)
	{
		scaling[0] = 10;
		scaling[1] = 5;
	}
	parse_scale_big_maps(grid, scaling);
}

t_pxl	*init_t_pxl(t_data *grid)
{
	float	scaling[2];
	t_pxl	*draw;

	draw = malloc(sizeof(t_pxl));
	// parse_scale(grid, scaling);
	scaling[0] = 10;
	scaling[1] = 3;
	draw->space = 10;
	draw->angle = 0.8;
	draw->z_scale = scaling[1];
	draw->scale = scaling[0];
	(void)grid;
	return (draw);
}

void	malloc_line(t_vct **line, int number_elems)
{
	t_vct	*element;

	while (number_elems > 0)
	{
		element = malloc(sizeof(t_vct));
		if (!element)
			return ;
		element->x = 0;
		element->y = 0;
		element->is_last = 0;
		element->next = *line;
		*line = element;
		number_elems--;
	}
}

void	make_inits(t_vct *line_ord, int *iter, t_data *grid, t_pxl *draw)
{
	iter[1] = -1;
	draw->line_abs_len = grid->x_max;
	(void)line_ord;
}
