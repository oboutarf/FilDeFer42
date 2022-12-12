/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:27:16 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 01:03:58 by oboutarf         ###   ########.fr       */
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

int	key_hook(int keycode, t_prog *vars)
{
	if (keycode == 65307)
	{
		mlx_loop_end(vars->mlx);
		return (0);
	}
	return (0);
}

int	free_mlx(t_prog *vars)
{
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->mlx_win)
	{
		mlx_clear_window(vars->mlx, vars->mlx_win);
		mlx_destroy_window(vars->mlx, vars->mlx_win);
	}	
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	return (0);
}

t_prog	init_mlx_vars()
{
	t_prog	new;

	new.mlx = mlx_init();
	if (!new.mlx)
		return (free_mlx(&new), new);
	new.mlx_win = mlx_new_window(new.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "fdf42 -oboutarf");
	new.img = mlx_new_image(new.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel,
			&new.line_length, &new.endian);
	return (new);
}

void	free_grid_data(t_data *grid)
{
	size_t	len;

	len = grid->y_max; 
	if (!grid->grid_data)
		return ;
	while (len > 0)
		free(grid->grid_data[--len]);
	free(grid->grid_data);
	free(grid);
}

int	main(int ac, char **av)
{
	t_data	*grid;
	t_prog	vars;
	int		fd;
	int test;

	printf("test : %p", &test);

	fd = 0;
	if (ac == 2)
		fd = open(av[ac - 1], O_RDONLY);
	else
		return ((write(1, "\nERROR!\nNO_INPUT!\n\n", 19)), 1);
	if (fd < 0)
		return (1) ;
	grid = parse_grid(fd);
	if (grid == NULL)
		return (1);
	close(fd);
	vars = init_mlx_vars();
	center_draw(vars, grid);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_hook(vars.mlx_win, 17, 0, mlx_loop_end, vars.mlx);
	mlx_loop(vars.mlx);
	free_mlx(&vars);
	free_grid_data(grid);
	// fonction free
	return (0);
}
