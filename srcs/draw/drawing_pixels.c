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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float	delta_max_x(float delta_x, float delta_y, float x1)
{
	if (delta_x > delta_y)
		increment_x = x1 / delta_x;
	else
		increment_x = x1 / delta_y;
	return (increment_x);
}

float	delta_max_y(float delta_x, float delta_y, float x1)
{
	if (delta_x > delta_y)
		increment_y = y1 / delta_x;
	else
		increment_y = y1 / delta_y;
	return (increment_y)
}

void	draw_segments_y_axis(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	float 	x1 = 0;
	float	y1 = 0;
	float	x2 = x1 + 1;
	float	y2 = y1 + 1;
    float   delta_x = 0;
    float   delta_y = 0;
    float   increment_x = 0;
    float	increment_y = 0;

	while (y1 <= grid->y_max)
	{
		while (x1 < grid->x_max)
		{
			delta_x = x2 - x1;
			delta_y = y2 - y1;
			increment_x = delta_max_x(delta_x, delta_y, x1);
			increment_y = delta_max_y(delta_x, delta_y, y1);
			while (increment_x != x2 && increment_y != y2)
			{
				if (increment_x != x2)
					my_mlx_pixel_put();
				if (increment_y != y2)
					my_mlx_pixel_put();
				increment_x += increment_x;
				increment_y += increment_y;
			}
			x1++;
			x2 = x1 + 1;
		}
		y1++;
	}
}

void	draw_segments_x_axis(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	float 	x1 = 0;
	float	y1 = 0;
	float	x2 = x1 + 1;
	float	y2 = y1 + 1;
    float   delta_x = 0;
    float   delta_y = 0;
    float   increment_x = 0;
    float	increment_y = 0;

	while (y1 <= grid->y_max)
	{
		while (x1 < grid->x_max)
		{
			delta_x = x2 - x1;
			delta_y = y2 - y1;
			increment_x = delta_max_x(delta_x, delta_y, x1);
			increment_y = delta_max_y(delta_x, delta_y, y1);
			while (increment_x != x2 && increment_y != y2)
			{
				if (increment_x != x2)
					my_mlx_pixel_put();
				if (increment_y != y2)
					my_mlx_pixel_put();
				increment_x += increment_x;
				increment_y += increment_y;
			}
			x1++;
			x2 = x1 + 1;
		}
		y1++;
	}
}

void	center_drawing()
{
	while (y++ <= grid->y_max)
	{
		draw_segments_x_axis(img, grid, mlx,  mlx_win);
		draw_segments_y_axis(img, grid, mlx,  mlx_win);
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 1920 / 2.5, 1080 / 3);
	mlx_loop(mlx);
}

/* void    place_pixels(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
    int     segvar = 0;
    int     sep = 10;
    int     ywin = sep;
    int     xwin = sep;
    int     ywin_sv = sep;
    int     x = 0;
    int     y = 0;

    while (y <= grid->y_max)
    {
        while (x < grid->x_max)
        {
            if (grid->grid_data[y][x] == 0)
            {
                my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin,  0x0000ffff);
                while (segvar++ < 10)
                {
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin, 0x7FFDC000);
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin_sv, 0x7FFDC000);
                    ywin_sv--;
                    xwin++;
                    ywin++;
                }
            }
            else
            {
                my_mlx_pixel_put(&img, 100 + xwin, ((grid->grid_data[y][x] * 3) * - 1) + ywin,  0x00FF0000);
                while (segvar++ < 10)
                {
                    my_mlx_pixel_put(&img, 100 + xwin, ((grid->grid_data[y][x] * 3) * - 1) + ywin, 0x7FFDC000);
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin_sv, 0x7FFDC000);
                    ywin_sv--;
                    xwin++;
                    ywin++;
                }
            }
            ywin_sv = ywin;
            segvar = 0;
            x++;
        }
        ywin_sv = 10 + sep;
        ywin = 10 + sep;
        xwin = 10 - sep;
        sep += 10;
        x = 0;
        y++;
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 1920 / 2.5, 1080 / 3);
    mlx_loop(mlx);corcorans meurtre
} */

/* void    center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	place_pixels(img, grid, mlx, mlx_win);
} */