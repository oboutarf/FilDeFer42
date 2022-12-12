/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:01:47 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 00:43:56 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_coordonates_ord(t_vct *input, t_vct **output, int len)
{
	t_vct	*save_head;
	int		i;

	i = 0;
	save_head = (*output);
	while (i < len)
	{
		(*output)->x = input->x;
		(*output)->y = input->y;
		(*output)->is_last = input->is_last;
		(*output) = (*output)->next;
		input = input->next;
		i++;
	}
	(*output) = save_head;
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
			if (x[0] > WINDOW_WIDTH || y[0] > WINDOW_HEIGHT
				|| x[0] < 0 || y[0] < 0)
				break ;
			display_px(vars, round(x[0]), round(y[0]), 0x00FF0000);
			x[0] += draw->x_incr[0];
			y[0] += draw->y_incr[0];
		}
		line = line->next;
	}
}

void	is_last_ordonnate_segment(t_vct *line, t_vct *line_ord,
		t_pxl *draw, t_prog vars)
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
			if (x[0] > WINDOW_WIDTH || y[0] > WINDOW_HEIGHT
				|| x[0] < 0 || y[0] < 0)
				break ;
			display_px(vars, round(x[0]), round(y[0]), 0x00FF0000);
			x[0] += draw->x_incr[0];
			y[0] += draw->y_incr[0];
		}
	}
}

void	draw_line(t_vct *line, t_vct *line_ord, t_pxl *draw, t_prog vars)
{
	float	x[4];
	float	y[4];

	while (line->next)
	{
		assign_coordonates_dda(line, line_ord, x, y);
		calculate_delta_between_coordonates(draw, x, y);
		draw = calculate_pixels_incrementation(draw);
		paint_it(draw, x, y, vars);
		line = line->next;
		line_ord = line_ord->next;
	}
	is_last_ordonnate_segment(line, line_ord, draw, vars);
}
