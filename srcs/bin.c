/* double	obtaining_delta_max(double *drawing_vars)
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
	drawing_vars[x_2] = 0;
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

void	draw_segment(double *drawing_vars, r_data *grid, t_data img, void *mlx, void *mlx_win)
{
	long	x = drawing_vars[x_1];
	long	y = drawing_vars[y_1];
	int		i = 0;

	drawing_vars[x_2] = drawing_vars[x_win_px] + grid->grid_data[y][x];
	drawing_vars[y_2] = drawing_vars[y_win_px] + (grid->grid_data[y][x + 1] * 3);

	drawing_vars[delta_x] = drawing_vars[x_2] - drawing_vars[x_1];
	drawing_vars[delta_y] = drawing_vars[y_2] - drawing_vars[y_1];
	obtaining_delta_max(drawing_vars);
	drawing_vars[increment_x] = delta_max_x(drawing_vars);
	drawing_vars[increment_y] = delta_max_y(drawing_vars);
	while (i <= drawing_vars[delta_max])
	{
		x = round(drawing_vars[x_1]);
		y = round(drawing_vars[y_1]);
		my_mlx_pixel_put(&img, drawing_vars[x_1], drawing_vars[y_1], 0x00FF0000);
		i++;
		drawing_vars[x_1] += drawing_vars[increment_x];
		drawing_vars[y_1] += drawing_vars[increment_y];
	}
}

double	convert_coordonates_for_win(double *drawing_vars, r_data *grid)
{
	drawing_vars[x_win_px] += drawing_vars[x_2] + (grid->grid_data[y_2][x_2] * 3);
	drawing_vars[y_win_px] += drawing_vars[y_2] + (grid->grid_data[y_2][x_2] * 3);
}

void	grant_deltas_of_segment(double *drawing_vars)
{
	drawing_vars[delta_x] = drawing_vars[x_2] - drawing_vars[x_1];
	drawing_vars[delta_y] = drawing_vars[y_2] - drawing_vars[y_1];
}

void	grant_incremation_of_pixels(double *drawing_vars)
{
	drawing_vars[increment_x] = delta_max_x(drawing_vars);
	drawing_vars[increment_y] = delta_max_y(drawing_vars);
}

void	round_position_pixels(long *x, long *y, double *drawing_vars)
{
	*x = round(drawing_vars[x_1]);
	*y = round(drawing_vars[y_1]);
}

void	draw_segment(double *drawing_vars, t_data img, void *mlx, void *mlx_win)
{
	long	x = drawing_vars[x_1];
	long	y = drawing_vars[y_1];
	int		i = 0;

	drawing_vars[x_1] = drawing_vars[x_win_px],
	drawing_vars[y_1] = drawing_vars[y_win_px],
	drawing_vars[x_2] = drawing_vars[x_win_px],
	drawing_vars[y_2] = drawing_vars[y_win_px],
	printf("---- X2 -> %f ---- Y1 -> %f ---- X2 -> %f ---- Y2 -> %f ---- \n\n ----------------------- \n\n", drawing_vars[x_1], drawing_vars[y_1], drawing_vars[x_2], drawing_vars[y_2]);
	grant_deltas_of_segment(drawing_vars);
	obtaining_delta_max(drawing_vars);
	grant_deltas_of_segment(drawing_vars);
	while (i <= drawing_vars[delta_max])
	{
		round_position_pixels(&x, &y, drawing_vars);
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		drawing_vars[x_1] += drawing_vars[increment_x];
		drawing_vars[y_1] += drawing_vars[increment_y];
		i++;
	}
}

void	update_projection(double *drawing_vars)
{
    drawing_vars[y_win_px] = 10 + drawing_vars[sep];
    drawing_vars[x_win_px] = 10 - drawing_vars[sep];
    drawing_vars[sep] += 10;
}

void	scale(double *drawing_vars, double scale)
{
	drawing_vars[x_1] *= scale;
	drawing_vars[y_1] *= scale;
	drawing_vars[x_2] *= scale;
	drawing_vars[y_2] *= scale;
}

// draw_segment((double [12]){ }, img, mlx, mlx_win);
void	segment_tracking(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	double	*drawing_vars;
	double	drawing_vars_save[12];

	drawing_vars = (double [12]){0};
	init_tracking(drawing_vars);
	while (drawing_vars[y_2] < grid->y_max)
	{
        drawing_vars[x_2] = 0;
		while (drawing_vars[x_2] < grid->x_max)
		{
			// scale(drawing_vars, 50);
			feeding_drawing_vars_save(drawing_vars, drawing_vars_save);
			// update_projection(drawing_vars_save);
			convert_coordonates_for_win(drawing_vars_save, grid);
			draw_segment(drawing_vars_save, img, mlx, mlx_win);
			drawing_vars[x_win_px] = drawing_vars_save[x_win_px];
			drawing_vars[y_win_px] = drawing_vars_save[y_win_px];
			drawing_vars[x_1] = drawing_vars[x_2];
			drawing_vars[x_2]++;
		}
		drawing_vars[y_2]++;
		drawing_vars[y_1] = drawing_vars[y_2];
	}

}

void	transforme(double *x, double *y)
{
	double	X;
	double	Y;

	X = (*x);
	Y = (*y);
	(*x) = X - Y;
	(*y) = (X * 0.5) + (Y * 0.5);
}

void	transforme_map(r_data *grid, double *x, double *y, double sep)
{
	// (*x) -= grid->x_max / 2;
	// (*y) += grid->y_max / 2;
	(*x) *= sep;
	(*y) *= sep;
}

//printf("%f %f %f %f \n", point[x_1], point[y_1], point[x_2], point[y_2]);
//transforme_map(grid, &point[x_2], &point[y_2], sep);
//transforme(&point[x_2], &point[y_2]);
void    place_pixels(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
    int     x;
    int     y;
	int		sep;
	double	*point;

	sep = 30;
	point = (double [12]){0};
	y = 0;
    while (y <= grid->y_max)
    {
		x = 0;

		point[x_1] = x;
		point[y_1] = y;
        while (x < grid->x_max)
        {
			point[x_2] = x;
			point[y_2] = y;
			transforme_map(grid, &point[x_2], &point[y_2], sep);
			transforme(&point[x_2], &point[y_2]);

			draw_segment(point, img, mlx, mlx_win);
			point[x_1] = point[x_2];
			point[y_1] = point[y_2];
            x++;

        }
        y++;
    }
}

void    center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win)
{
	segment_tracking(img, grid, mlx, mlx_win);
	// place_pixels(img, grid, mlx, mlx_win);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 1920 / 2.5, 1080 / 3);
	mlx_loop(mlx);
} */