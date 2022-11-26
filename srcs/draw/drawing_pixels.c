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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	obtaining_delta_max(double *drawing_vars)
{
	if (drawing_vars[delta_x] > drawing_vars[delta_y])
		drawing_vars[delta_max] = drawing_vars[delta_x];
	else
		drawing_vars[delta_max] = drawing_vars[delta_y];
}

void	feeding_drawing_vars_save(double *drawing_vars_src, double *drawing_vars_dest)
{
	int		step = 0;

	while (step < 12)
	{
		drawing_vars_dest[step] = drawing_vars_src[step];
		step++;
	}
}

double	delta_max_x(double *drawing_vars)
{
	if (drawing_vars[delta_x] > drawing_vars[delta_y])
		drawing_vars[increment_x] = drawing_vars[delta_x] / drawing_vars[delta_x];
	else
		drawing_vars[increment_x] = drawing_vars[delta_x] / drawing_vars[delta_y];
	return (drawing_vars[increment_x]);
}

double	delta_max_y(double *drawing_vars)
{
	if (drawing_vars[delta_x] > drawing_vars[delta_y])
		drawing_vars[increment_y] = drawing_vars[delta_y] / drawing_vars[delta_x];
	else
		drawing_vars[increment_y] = drawing_vars[delta_y] / drawing_vars[delta_y];
	return (drawing_vars[increment_y]);
}

double	*init_tracking(double *drawing_vars)
{
	drawing_vars[x_1] = 0;
	drawing_vars[x_2] = 1;
	drawing_vars[y_1] = 0;
	drawing_vars[y_2] = 0;
	drawing_vars[sep] = 10;
	drawing_vars[delta_x] = 0;
	drawing_vars[delta_y] = 0;
	drawing_vars[delta_max] = 0;
	drawing_vars[x_win_px] = 10;
	drawing_vars[y_win_px] = 10;
	drawing_vars[increment_x] = 0;
	drawing_vars[increment_y] = 0;
	return (drawing_vars);
}
// printf("for x: %ld || y: %ld =>> delta_x is: %f || delta_y is: %f\n", x, y, drawing_vars[delta_x], drawing_vars[delta_y]);
// printf("y is: %ld for delta_max: %f  ||  increment_x: %f  increment_y: %f\n", y, drawing_vars[delta_max], drawing_vars[increment_x], drawing_vars[increment_y]);
// printf("%d  ||  INCREMENT_X: %f ; INCREMENT_Y: %f  ||  X_WIN=%f  Y_WIN=%f\n\n", i, drawing_vars[increment_x], drawing_vars[increment_y], drawing_vars[x_win_px], drawing_vars[y_win_px]);
// printf("X_1: %f for Y_1: %f\n", drawing_vars[x_1], drawing_vars[y_1]);
// init_segmentY();

void	init_segment(double *drawing_vars, r_data *grid, int y_win_px_save, t_data img, void *mlx, void *mlx_win)
{
	long	x = drawing_vars[x_1];
	long	y = drawing_vars[y_1];
	int		i = 0;

	drawing_vars[y_2] = y + drawing_vars[sep] + ((grid->grid_data[y][x + 1] * 3) * -1);
	// drawing_vars[x_2] = x + 10 + ((grid->grid_data[y][x + 1] * 3) * -1);
	// printf("%f\n", drawing_vars[y_2]);
	drawing_vars[delta_x] = drawing_vars[x_2] - drawing_vars[x_1];
	drawing_vars[delta_y] = drawing_vars[y_2] - drawing_vars[y_1];
	obtaining_delta_max(drawing_vars);
	drawing_vars[increment_x] = delta_max_x(drawing_vars);
	drawing_vars[increment_y] = delta_max_y(drawing_vars);
	while (i <= drawing_vars[delta_max])
	{
		x = round(drawing_vars[x_win_px]);
		y = round(drawing_vars[y_win_px]);
		my_mlx_pixel_put(&img, 250 + x, 0 + y, 67176);
		my_mlx_pixel_put(&img, 250 + x, 0 + y_win_px_save, 0x00FF0000);
		y_win_px_save--;
		i++;
		drawing_vars[delta_max]--;
		drawing_vars[x_win_px] += drawing_vars[increment_x];
		drawing_vars[y_win_px] += drawing_vars[increment_y];
	}
}

void	segment_tracking(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	double	drawing_vars[12];
	double	drawing_vars_save[12];
	int		y_win_px_save;

	init_tracking(drawing_vars);
	y_win_px_save = drawing_vars[sep];
	while (drawing_vars[y_1] <= grid->y_max)
	{
		while (drawing_vars[x_1] < grid->x_max)
		{
			feeding_drawing_vars_save(drawing_vars, drawing_vars_save);
			init_segment(drawing_vars_save, grid, y_win_px_save, img, mlx, mlx_win);
			drawing_vars[x_1]++;
			drawing_vars[x_2]++;
			drawing_vars[y_win_px] = drawing_vars[y_1];
		}
        drawing_vars[y_win_px] = 10 + drawing_vars[sep];
        drawing_vars[x_win_px] = 10 - drawing_vars[sep];
		y_win_px_save = drawing_vars[y_win_px];
        drawing_vars[sep] += 10;
        drawing_vars[x_1] = 0;
		drawing_vars[x_2] = drawing_vars[x_1] + 1;
		drawing_vars[y_1]++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 1920 / 2.5, 1080 / 3);
	mlx_loop(mlx);
}

void    center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	segment_tracking(img, grid, mlx, mlx_win);
}

/* void	draw_segments_x_axis(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
    double   	increment[2];
	double		win_px[2];
	int			SPACE = 10;
	double 		x[2];
	double		y[2];
    double   	delta_x = 0;
    double   	delta_y = 0;

	x[0] = 0;
	x[1] = x[0] + 1;
	y[0] = 0;
	y[1] = 0;
	win_px[0] = sep;
	win_px[1] = sep;
	while (y[0] <= grid->y_max)
	{
		while (x[0] < grid->x_max)
		{
			y[1] = y[0] + (grid->grid_data[y[0]][x[1]] * 3);
			delta_x = x[1] - x[0];
			delta_y = y[1] - y[0];
			increment[0] = delta_max_x(delta_x, delta_y, x[0]);
			increment[1] = delta_max_y(delta_x, delta_y, y[0]);
			while (increment[0] != x[1] && increment[1] != y[0])
			{
				my_mlx_pixel_put(&img, 100 + win_px[0] + , 0 + win_px[1], 0x00FF0000);
				increment[0] += increment[0];
				increment[1] += increment[1];
			}
			x[0]++;
			x[1] = x[0] + 1;
		}
		y[0]++;
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
} */

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
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin, 0x00FF0000);
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin_sv, 0x00FF0000);
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
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin_sv, 12731);
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
    mlx_loop(mlx);
} */