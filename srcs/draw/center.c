/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:05:54 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 00:50:54 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	display_px(t_prog vars, int x, int y, int color)
{
	char	*dst;

	y *= vars.line_length;
	x *= (vars.bits_per_pixel / 8);
	dst = vars.addr + (y + x);
	*(unsigned int *)dst = color;
}

t_vct	*segments_absord_calculating(t_pxl *draw, int grid_x,
	int grid_y, t_vct *line)
{
	draw->x[0] = grid_x;
	draw->y[0] = grid_y;
	draw->x[1] = grid_x + 10;
	draw->y[1] = grid_y;
	scale_draw_variables(draw);
	attribute_iso_coordonates(draw);
	draw->x[0] += WINDOW_WIDTH / 2.5;
	draw->y[0] += WINDOW_HEIGHT / 2.5;
	draw->x[1] += WINDOW_WIDTH / 2.5;
	draw->y[1] += WINDOW_HEIGHT / 2.5;
	line->x = draw->x[0];
	line->y = draw->y[0];
	if (grid_x + 1 == draw->line_abs_len)
	{
		line->next = NULL;
		line->is_last = 1;
		return (line);
	}
	line = line->next;
	return (line);
}

void	choose_line(t_pxl *draw, t_vct *line, t_vct *line_ord, t_prog vars)
{
	if (draw->y[0] == 0)
		draw_first_line(line, draw, vars);
	else
		draw_line(line, line_ord, draw, vars);
}

t_vct	*start_process_draw(t_data *grid, t_prog vars, t_pxl *draw, t_vct *line)
{
	t_vct		*line_ord;
	t_vct		*save_line;
	int			iter[2];

	line_ord = NULL;
	make_inits(line_ord, iter, grid, draw);
	save_line = line;
	malloc_line(&line_ord, grid->x_max);
	while (++iter[1] < grid->y_max)
	{
		iter[0] = -1;
		if (!iter[1] == 0)
			save_coordonates_ord(save_line, &line_ord, grid->x_max);
		while (++iter[0] < grid->x_max)
		{
			attribute_z_coordonates(draw, grid, iter[0], iter[1]);
			line = segments_absord_calculating(draw, iter[0], iter[1], line);
			if (iter[0] + 1 > grid->x_max)
				break ;
		}
		line = save_line;
		draw->y[0] = iter[1];
		choose_line(draw, line, line_ord, vars);
	}
	// if (line_ord)
	// {
	// 	printf("IS HERE\n");
	// 	free_l(&line_ord, grid->y_max);
	// }
	// else 
	// 	printf("IS NOT HERE\n");
	return (line_ord);
}

void	center_draw(t_prog vars, t_data *grid)
{
	t_pxl		*draw;
	t_vct		*line;
	t_vct		*dump;

	line = NULL;
	draw = init_t_pxl();
	malloc_line(&line, grid->x_max);
	dump = start_process_draw(grid, vars, draw, line);
	free(draw);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img, 0, 0);
	if (dump)
		free_l(&dump, grid->x_max);
	if (line)
		free_l(&line, grid->x_max);
}
