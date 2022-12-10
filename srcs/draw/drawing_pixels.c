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
	element->is_last = 0;
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

void	my_mlx_pixel_put(t_prog vars, int x, int y, int color)
{
	char	*dst;

	y *= vars.line_length;
	x *= (vars.bits_per_pixel / 8);
	dst = vars.addr + (y + x);
	*(unsigned int*)dst = color;
}

void attribute_z_coordonates(t_pxl *draw, r_data *grid, int x, int y)
{
	draw->z[0] = (grid->grid_data[y][x]) * draw->z_scale;
	if (x + 1 == grid->x_max)
		return ;
	draw->z[1] = (grid->grid_data[y][x + 1]) * draw->z_scale;
}

t_pxl	*init_t_pxl(void)
{
	t_pxl	*draw;

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
	draw->angle = 0.5;
	draw->scale = 5;
	draw->z_scale = 30;
	return (draw);
}

void	scale_draw_variables(t_pxl *draw)
{
	draw->x[0] *=  draw->scale;
	draw->y[0] *=  draw->scale;
	draw->x[1] *=  draw->scale;
	draw->y[1] *=  draw->scale;
}

void 	attribute_iso_coordonates(t_pxl *draw)
{
	draw->x[0] = (draw->x[0] - draw->y[0]) * cos(draw->angle);
	draw->y[0] = (draw->x[0] + draw->y[0]) * sin(draw->angle) - draw->z[0];
	draw->x[1] = (draw->x[1] - draw->y[1]) * cos(draw->angle);
	draw->y[1] = (draw->x[1] + draw->y[1]) * sin(draw->angle) - draw->z[1];
}

t_vct	*segments_absord_calculating(t_pxl *draw, int grid_x, int grid_y, t_vct *line)
{
	draw->x[0] = grid_x;
	draw->y[0] = grid_y;
	draw->x[1] = grid_x + 10;
	draw->y[1] = grid_y;
	scale_draw_variables(draw);
	attribute_iso_coordonates(draw);
	draw->x[0] += WIN_X;
	draw->y[0] += WIN_Y;
	draw->x[1] += WIN_X;
	draw->y[1] += WIN_Y;
	line->x = draw->x[0];
	line->y = draw->y[0];
	if (grid_x + 1 == draw->line_abs_len)
	{
		line->next = NULL;
		line->is_last = 1;
		return (line) ;
	}
	line = line->next;
	return (line);
}

void	print_line(t_vct *line)
{
	while (line->next)
	{
		printf("LINES == %f  ---  %f    -%d\n", line->x, line->y, line->is_last);
		if (!line)
			return ;
		line = line->next;
	}
}

t_pxl	*calculate_pixels_first_incrementation(t_pxl *draw, float *x, float *y, t_vct *line)
{
	if (!(line->is_last == 1))
	{
		x[0] = line->x;
		y[0] = line->y;
		x[1] = line->next->x;
		y[1] = line->next->y;
		draw->x_delta[0] = x[1] - x[0];
		draw->y_delta[0] = y[1] - y[0];
	}
	else
	{
		draw->x_delta[0] = x[1] - x[0];
		draw->y_delta[0] = y[1] - y[0];
	}
	if (abs(draw->x_delta[0]) > abs(draw->y_delta[0]))
		draw->steps[0] = abs(draw->x_delta[0]);
	else
		draw->steps[0] = abs(draw->y_delta[0]);
	draw->x_incr[0] = draw->x_delta[0] / draw->steps[0];
	draw->y_incr[0] = draw->y_delta[0] / draw->steps[0];
	return (draw);
}

t_pxl	*calculate_pixels_incrementation(t_pxl *draw, float *x, float *y, t_vct *line, t_vct *line_ord)
{
	x[0] = line->x;
	y[0] = line->y;
	x[1] = line->next->x;
	y[1] = line->next->y;
	x[2] = line->x;
	y[2] = line->y;
	x[3] = line_ord->x;
	y[3] = line_ord->y;
	draw->x_delta[0] = x[1] - x[0];
	draw->y_delta[0] = y[1] - y[0];
	draw->x_delta[1] = x[3] - x[2];
	draw->y_delta[1] = y[3] - y[2];
	if (abs(draw->x_delta[0]) > abs(draw->y_delta[0]))
		draw->steps[0] = abs(draw->x_delta[0]);
	else
		draw->steps[0] = abs(draw->y_delta[0]);
	if (abs(draw->x_delta[1]) > abs(draw->y_delta[1]))
		draw->steps[1] = abs(draw->x_delta[1]);
	else
		draw->steps[1] = abs(draw->y_delta[1]);
	draw->x_incr[0] = draw->x_delta[0] / draw->steps[0];
	draw->y_incr[0] = draw->y_delta[0] / draw->steps[0];

	draw->x_incr[1] = draw->x_delta[1] / draw->steps[1];
	draw->y_incr[1] = draw->y_delta[1] / draw->steps[1];
	return (draw);
}

void	draw_first_line(t_vct *line, t_pxl *draw, t_prog vars)
{
	float	x[2];
	float	y[2];

	while (line->next)
	{
		draw = calculate_pixels_first_incrementation(draw, x, y, line);
		while (draw->steps[0]-- > 0)
		{
			if (x[0] > WINDOW_WIDTH || y[0] > WINDOW_HEIGHT || x[0] < 0 || y[0] < 0)
				break ;
			my_mlx_pixel_put(vars, round(x[0]), round(y[0]), 0x00FF0000);
			x[0] += draw->x_incr[0];
			y[0] += draw->y_incr[0];
		}
		line = line->next;
	}
}

void 	is_last_ordonnate_segment(t_vct *line, t_vct *line_ord, t_pxl *draw, t_prog vars)
{
	float	x[2];
	float	y[2];

	if (line->is_last == 1 && line_ord->is_last == 1)
	{
		x[0] = line->x;
		y[0] = line->y;
		x[1] = line_ord->x;
		y[1] = line_ord->y;
		draw = calculate_pixels_first_incrementation(draw, x, y, line);
		while (draw->steps[0]-- > 0)
		{
			if (x[0] > WINDOW_WIDTH || y[0] > WINDOW_HEIGHT || x[0] < 0 || y[0] < 0)
				break ;
			my_mlx_pixel_put(vars, round(x[0]), round(y[0]), 0x00FF0000);
			x[0] += draw->x_incr[0];
			y[0] += draw->y_incr[0];
		}
	}
}

void 	draw_line(t_vct *line, t_vct *line_ord, t_pxl *draw, t_prog vars)
{
	float	x[4];
	float	y[4];

	while (line->next)
	{
		draw = calculate_pixels_incrementation(draw, x, y, line, line_ord);
		while (draw->steps[0]-- > 0)
		{
			if (x[0] > WINDOW_WIDTH || y[0] > WINDOW_HEIGHT || x[0] < 0 || y[0] < 0)
				break ;
			my_mlx_pixel_put(vars, round(x[0]), round(y[0]), 0x00FF0000);
			x[0] += draw->x_incr[0];
			y[0] += draw->y_incr[0];
		}
		while (draw->steps[1]-- > 0)
		{
			if (x[2] > WINDOW_WIDTH || y[2] > WINDOW_HEIGHT || x[2] < 0 || y[2] < 0)
				break ;
			my_mlx_pixel_put(vars, round(x[2]), round(y[2]), 0x00FF0000);
			x[2] += draw->x_incr[1];
			y[2] += draw->y_incr[1];
		}
		line = line->next;
		line_ord = line_ord->next;
	}

	is_last_ordonnate_segment(line, line_ord, draw, vars);


}

t_vct	*save_coordonates_ord(t_vct *input, int len)
{
	t_vct	*save_head;
	t_vct	*sv_coord;
	int		i = 0;

	sv_coord = malloc(sizeof(t_vct));
	save_head = sv_coord;
	while (i < len)
	{
		sv_coord->x = input->x;
		sv_coord->y = input->y;
		sv_coord->is_last = input->is_last;
		sv_coord->next = malloc(sizeof(t_vct));
		sv_coord = sv_coord->next;
		input = input->next;
		i++;
	}
	sv_coord = save_head;
	return (sv_coord);
}

void	center_draw(t_prog vars, r_data *grid)
{
	t_pxl		*draw;
	t_vct		*line_ord;
	t_vct		*save_line;
	t_vct		*line;
	int			x;
	int			y;

	y = 0;
	draw = init_t_pxl();
	malloc_line(&line, grid->x_max);
	malloc_line(&line_ord, grid->x_max);
	draw->line_abs_len = grid->x_max;
	save_line = line;
	while (y < grid->y_max)
	{
		x = 0;
		if (!y == 0)
			line_ord = save_coordonates_ord(save_line, grid->x_max);
		while (x < grid->x_max)
		{
			attribute_z_coordonates(draw, grid, x, y);
			line = segments_absord_calculating(draw, x , y, line);
			x++;
			if (x + 1 > grid->x_max)
				break ; 
		}
		line = save_line;
		if (y == 0)
			draw_first_line(line, draw, vars);
		else
			draw_line(line, line_ord, draw, vars);
		y++;
	}
	free(draw);
	// free_t_vcts(&line, &line_ord);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.img, 0, 0);
}
