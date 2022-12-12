/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:00:38 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/11 14:01:03 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	attribute_z_coordonates(t_pxl *draw, t_data *grid, int x, int y)
{
	draw->z[0] = (grid->grid_data[y][x]) * draw->z_scale;
	if (x + 1 == grid->x_max)
		return ;
	draw->z[1] = (grid->grid_data[y][x + 1]) * draw->z_scale;
}

void	scale_draw_variables(t_pxl *draw)
{
	draw->x[0] *= draw->scale;
	draw->y[0] *= draw->scale;
	draw->x[1] *= draw->scale;
	draw->y[1] *= draw->scale;
}

void	attribute_iso_coordonates(t_pxl *draw)
{
	draw->x[0] = (draw->x[0] - draw->y[0]) * cos(draw->angle);
	draw->y[0] = (draw->x[0] + draw->y[0]) * sin(draw->angle) - draw->z[0];
	draw->x[1] = (draw->x[1] - draw->y[1]) * cos(draw->angle);
	draw->y[1] = (draw->x[1] + draw->y[1]) * sin(draw->angle) - draw->z[1];
}
