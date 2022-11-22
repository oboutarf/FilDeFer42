/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 05:12:24 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/22 17:28:30 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_grid_data(r_data *grid)
{
	int		y1 = 0;
	int		x = 0;

	while (y1 <= grid->y_max)
	{
		x = 0;
		while (x < grid->x_max && y1 <= grid->y_max)
		{
			printf("[%d][%d] = %d\n", y1, x, grid->grid_data[y1][x]);
			x++;
		}
		printf("\n\n");
		y1++;
	}
}