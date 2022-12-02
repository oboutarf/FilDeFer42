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

t_pxl	*attribute_z_coordonates(t_pxl *draw, r_data grid, int x, int y)
{
	draw->z[0] = (grid.grid_data[y][x])(10*3);
	draw->z[1] = (grid.grid_data[y][x + 1])+(10*3);
	draw->z[2] = grid.grid_data[y + 1][x]+(10*3);
}

t_vctr	*init_t_vctr(t_vctr	*vector)
{
	vector = malloc(sizeof(t_vctr));
	vector->a[0] = 0;
	vector->a[1] = 0;
	vector->b[0] = 0;
	vector->b[1] = 0;
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
	draw->win_x = 800;
	draw->win_y = 500;
	draw->angle = 0.6;
	draw->scale = 20;
}

void	scale_center_pixel(int *x, int *y, t_pxl *draw)
{
	*x *= draw->scale;
	*y *= draw->scale;
	*x += draw->win_x;
	*y += draw->win_y;
}

void	segments_absord_drawing(t_data img, t_pxl *draw, int x, int y)
{
	int		i = 0;

	scale_center_pixel(&x, &y, draw);
	draw->x[0] = (x - y) * cos(draw->angle);
	draw->y[0] = (x + y) * sin(draw->angle) - draw->z[0];
	my_mlx_pixel_put(&img, draw->x[0], draw->y[0], 0x00FF0000);
}

void	center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	t_vctr		*vector;
	t_pxl		*draw;
	int			x;
	int			y;

	y = 0;
	draw = init_t_pxl(draw);
	vector = init_t_vctr(vector);
	while (y < grid->y_max)
	{
		x = 0;
		while (x < grid->x_max)
		{
			draw = attribute_z_coordonates(draw, *grid, x, y);
			segments_absord_drawing(img, draw, x, y);
			x++;
		}
		draw->space += 10;
		y++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

// 	draw->z[0], draw->z[1], draw->z[2], y, x);
// printf("--- Z[0] =>  %f     ------ Z[1] =>   %f   ------ Z[2] =>  %f   ---\ny: %d\nx: %d\n\n",