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

/* void    draw_segment()
{
    
} */

void    place_pixels(t_data img, r_data *grid, void *mlx, void *mlx_win)
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
                while (segvar < 10)
                {
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin, 0x7FFDC000);
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin_sv, 0x7FFDC000);
                    ywin_sv--;
                    xwin++;
                    ywin++;
                    segvar++;
                }
            }
            else
            {
                my_mlx_pixel_put(&img, 100 + xwin, ((grid->grid_data[y][x] + 40) * - 1) + ywin,  0x00FF0000);
                while (segvar < 10)
                {
                    my_mlx_pixel_put(&img, 100 + xwin, ((grid->grid_data[y][x] + 40) * - 1) + ywin, 0x7FFDC000);
                    my_mlx_pixel_put(&img, 100 + xwin, 0 + ywin_sv, 0x7FFDC000);
                    ywin_sv--;
                    xwin++;
                    ywin++;
                    segvar++;
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
}

void    center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
    place_pixels(img, grid, mlx, mlx_win);
}
