/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:56:26 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/11 15:08:03 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	paint_it(t_pxl *draw, float *x, float *y, t_prog vars)
{
	while (draw->steps[0]-- > 0)
	{
		if (x[0] > WINDOW_WIDTH || y[0] > WINDOW_HEIGHT
			|| x[0] < 0 || y[0] < 0)
			break ;
		display_px(vars, round(x[0]), round(y[0]), 0x00FF0000);
		x[0] += draw->x_incr[0];
		y[0] += draw->y_incr[0];
	}
	while (draw->steps[1]-- > 0)
	{
		if (x[2] > WINDOW_WIDTH || y[2] > WINDOW_HEIGHT
			|| x[2] < 0 || y[2] < 0)
			break ;
		display_px(vars, round(x[2]), round(y[2]), 0x00FF0000);
		x[2] += draw->x_incr[1];
		y[2] += draw->y_incr[1];
	}
}

void	assign_coordonates_dda(t_vct *line, t_vct *line_ord, float *x, float *y)
{
	x[0] = line->x;
	y[0] = line->y;
	x[1] = line->next->x;
	y[1] = line->next->y;
	x[2] = line->x;
	y[2] = line->y;
	x[3] = line_ord->x;
	y[3] = line_ord->y;
}

void	calculate_delta_between_coordonates(t_pxl *draw, float *x, float *y)
{
	draw->x_delta[0] = x[1] - x[0];
	draw->y_delta[0] = y[1] - y[0];
	draw->x_delta[1] = x[3] - x[2];
	draw->y_delta[1] = y[3] - y[2];
}

t_pxl	*calculate_pixels_first_incrementation(t_pxl *draw, float *x,
		float *y, t_vct *line)
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

t_pxl	*calculate_pixels_incrementation(t_pxl *draw)
{
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
