/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:27:16 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/23 11:43:49 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incld/fdf.h"

int	check_fd(int ac)
{
	if (ac == 2)
		return (0);
	else
		return (1);
}

int		terminate_prog(t_prog *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	return (0);
}

int	key_hook(int keycode, t_prog *vars)
{
	if (keycode == XK_Escape)
		terminate_prog(vars);
	// if (keycode == XC_X_cursor)
	// 	terminate_prog(vars);
	return (0);
}

int	main(int ac, char **av)
{
	r_data	*grid;
	t_prog	vars;
	int		fd = 0;

// # Init struct grid # //
	if (ac == 2)
		fd = open(av[ac - 1], O_RDONLY);
	else
		return ((write(1, "\nERROR!\nNO_INPUT!\n\n", 19)), 1);
	grid = parse_grid(fd);
	print_grid_data(grid);
	close(fd);
//==================================================================================//
// # Implement struct grid with MiniLibx Projection # //
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf42 -oboutarf");
	vars.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
// # Checking grid data (unactivated) # //
	// print_grid_data(grid);
// # Implement struct grid with MiniLibx Projection # //
//==================================================================================//
	center_draw(vars, grid);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_loop(vars.mlx);
	/* mlx_hook() */
// # Terminate Program # //
// # End
	return (0);
}

