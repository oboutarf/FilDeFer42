/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:44:45 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/23 11:44:22 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incld/fdf.h"
#include <math.h>

t_vct	*elem_addto_line(t_vct **line)
{
	t_vct	*element;

	element = malloc(sizeof(t_vct));
	if (!element)
		return (NULL);
	element->x = 0;
	element->y = 0;
	element->next = *line;
	*line = element;
	return (element);
}

void	malloc_line(t_vct **line, int number_elems)
{
	while (number_elems > 0)
	{
		(*line) = elem_addto_line(line);
		number_elems--;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	y *= data->line_length;
	x *= (data->bits_per_pixel / 8);
	dst = data->addr + (y + x);
	*(unsigned int*)dst = color;
}

t_pxl	*attribute_z_coordonates(t_pxl *draw, r_data *grid, int x, int y)
{
	draw->z[0] = (grid->grid_data[y][x]) * draw->z_scale;
	draw->z[1] = (grid->grid_data[y][x + 1]) * draw->z_scale;
	draw->z[2] = grid->grid_data[y + 1][x] * draw->z_scale;
}

t_pxl	*init_t_pxl(t_pxl *draw)
{
	draw = malloc(sizeof(t_pxl));
	draw->x[0] = 0;
	draw->x[1] = 0;
	draw->x[2] = 0;
	draw->y[0] = 0;
	draw->y[1] = 0;
	draw->y[2] = 0;
	draw->z[0] = 0;
	draw->z[1] = 0;
	draw->z[2] = 0;
	draw->steps[0] = 0;
	draw->steps[1] = 0;
	draw->x_incr[0] = 0;
	draw->x_incr[1] = 0;
	draw->y_incr[0] = 0;
	draw->y_incr[1] = 0;
	draw->x_delta[0] = 0;
	draw->x_delta[1] = 0;
	draw->y_delta[0] = 0;
	draw->y_delta[1] = 0;
	draw->space = 10;
	draw->x_win = 800;
	draw->y_win = 500;
	draw->angle = 0.8;
	draw->scale = 15;
	draw->z_scale = 10;
}

t_pxl	*scale_draw_variables(t_pxl *draw)
{
	draw->x[0] *=  draw->scale;
	draw->y[0] *=  draw->scale;
	draw->x[1] *=  draw->scale;
	draw->y[1] *=  draw->scale;
}

t_pxl 	*attribute_iso_coordonates(t_pxl *draw)
{
	draw->x[0] = (draw->x[0] - draw->y[0]) * cos(draw->angle);
	draw->y[0] = (draw->x[0] + draw->y[0]) * sin(draw->angle) - draw->z[0];
	draw->x[1] = (draw->x[1] - draw->y[1]) * cos(draw->angle);
	draw->y[1] = (draw->x[1] + draw->y[1]) * sin(draw->angle) - draw->z[1];
}

t_vct	*segments_absord_calculating(t_data img, t_pxl *draw, int grid_x, int grid_y, t_vct *line)
{
	draw->x[0] = grid_x;
	draw->y[0] = grid_y;
	draw->x[1] = grid_x + 10;
	draw->y[1] = grid_y;
	draw = scale_draw_variables(draw);
	draw = attribute_iso_coordonates(draw);
	draw->x[0] += draw->x_win;
	draw->y[0] += draw->y_win;
	draw->x[1] += draw->x_win;
	draw->y[1] += draw->y_win;

	line->x = draw->x[0];
	line->y = draw->y[0];
	if (grid_x + 1 == draw->line_abs_len)
		line->is_last = 1;
	line = line->next;
	my_mlx_pixel_put(&img, draw->x[0], draw->y[0], 0x00FF0000);
	return (line);
}

void	print_line(t_vct *line)
{
	while (line)
	{
		printf("LINES == %f  ---  %f    -%d\n", line->x, line->y, line->is_last);
		line = line->next;
	}
}


t_pxl	*calculate_pixels_incrementation(t_pxl *draw, float *x, float *y, t_vct *line)
{
	x[0] = line->x;
	y[0] = line->y;
	x[1] = line->next->x;
	y[1] = line->next->y;
	draw->x_delta[0] = x[1] - x[0];
	draw->y_delta[0] = y[1] - y[0];
	if (abs(draw->x_delta[0]) > abs(draw->y_delta[0]))
		draw->steps[0] = abs(draw->x_delta[0]);
	else
		draw->steps[0] = abs(draw->y_delta[0]);
	draw->x_incr[0] = draw->x_delta[0] / draw->steps[0];
	draw->y_incr[0] = draw->y_delta[0] / draw->steps[0];
	printf("STEPS is : %f\n", draw->steps[0]);
	return (draw);
}


void	draw_line(t_vct *line, t_pxl *draw, t_data img)
{
	float	x[2];
	float	y[2];
	float	px_x;
	float	px_y;

	while (line->next)
	{
		if (line->is_last == 1)
			break ;
		draw = calculate_pixels_incrementation(draw, x, y, line);
		while (draw->steps[0] > 0)
		{
			my_mlx_pixel_put(&img, round(x[0]), round(y[0]), 0x00FF0000);
			x[0] += draw->x_incr[0];
			y[0] += draw->y_incr[0];
			draw->steps[0]--;
		}
		line = line->next;
	}
}

void	center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	t_pxl		*draw;
	t_vct		*save_line;
	t_vct		*line;
	int			x;
	int			y;

	y = 0;
	draw = init_t_pxl(draw);
	malloc_line(&line, grid->x_max);
	draw->line_abs_len = grid->x_max;
	save_line = line;
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			draw = attribute_z_coordonates(draw, grid, x, y);
			line = segments_absord_calculating(img, draw, x , y, line);
			// if (x + 1 != grid->x_max)
			x++;
		}
		line->next = NULL;
		line = save_line;
		// print_line(line);
		draw_line(line, draw, img);
		// reset_line(line);
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
