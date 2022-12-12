/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:56:30 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 00:24:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pxl	*init_t_pxl(void)
{
	t_pxl	*draw;

	draw = malloc(sizeof(t_pxl));
	draw->space = 10;
	draw->angle = 0.8;
	draw->scale = 1.9;
	draw->z_scale = 2;
	return (draw);
}

void	malloc_line(t_vct **line, int number_elems)
{
	t_vct	*element;

	while (number_elems > 0)
	{
		element = malloc(sizeof(t_vct));
		if (!element)
			return ;
		element->x = 0;
		element->y = 0;
		element->is_last = 0;
		element->next = *line;
		*line = element;
		number_elems--;
	}
}

void	make_inits(t_vct *line_ord, int *iter, t_data *grid, t_pxl *draw)
{
	iter[1] = -1;
	draw->line_abs_len = grid->x_max;
	(void)line_ord;
}
