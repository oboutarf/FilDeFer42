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

t_vctr	*init_t_vctr(t_vctr	*vector)
{
	vector = malloc(sizeof(t_vctr));
	vector->x = 0;
	vector->y = 0;
	vector->z = 0;
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
	draw->angle = 0.4;
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

void	segments_absord_drawing(t_data img, t_pxl *draw, int grid_x, int grid_y)
{
	draw->x[0] = grid_x;
	draw->y[0] = grid_y;
	draw->x[1] = grid_x + 10;
	draw->y[1] = grid_y + 10;
	draw = scale_draw_variables(draw);
	draw = attribute_iso_coordonates(draw);
	draw->x[0] += draw->x_win;
	draw->y[0] += draw->y_win;
	draw->x[1] += draw->x_win;
	draw->y[1] += draw->y_win;
	my_mlx_pixel_put(&img, draw->x[0], draw->y[0], 0x00FF0000);











	
	// my_mlx_pixel_put(&img, draw->x[1], draw->y[1], 0xe80c0c);
}

void	center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	t_pxl		*draw;
	int			x;
	int			y;

	y = 0;
	draw = init_t_pxl(draw);
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			draw = attribute_z_coordonates(draw, grid, x, y);
			segments_absord_drawing(img, draw, x , y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 1920 / 2.5, 1080 / 3);
	mlx_loop(mlx);
}

// 	draw->z[0], draw->z[1], draw->z[2], y, x);
// printf("--- Z[0] =>  %f     ------ Z[1] =>   %f   ------ Z[2] =>  %f   ---\ny: %d\nx: %d\n\n",
// my_mlx_pixel_put(&img, round(draw->x[0]), round(draw->y[0]), 0x00FF0000);
