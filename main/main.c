/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:27:16 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/17 15:57:34 by oboutarf         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	r_data	*grid;
	t_data	img;
	void	*mlx_win;
	void	*mlx;
	int		fd = 0;
	int		x = 0;
	int		y = 0;

// # Init struct grid # //
	if (ac == 2)
		fd = open(av[ac - 1], O_RDONLY);
	else
		return ((write(1, "\nERROR!\nNO_INPUT!\n\n", 19)), 1);
	grid = parse_grid(av[ac - 1], fd);
	// print_grid_data(grid);
// # Implement struct grid with MiniLibx Projection # //
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// # Checking Coordonates # //	-> UNACTIVATED
	print_grid_data(grid);
// # Implement struct grid with MiniLibx Projection # //
	mlx_put_image_to_window(mlx, mlx_win, img.img, 1920 / 4, 1080 / 2);
	mlx_loop(mlx);
// # Terminate Program # //

	close(fd);
// # End
}


// # Save Shit # //
/* int	main(int ac, char **av)
{
	r_data		*grid;
	int		fd = 0;

	if (ac == 2)
		fd = open(av[ac - 1], O_RDONLY);
	else
		return ((write(1, "\nERROR!\nNO_INPUT!\n\n", 19)), 1);
	grid = parse_grid(av[ac - 1], fd);
	// print_grid_data(grid);
	close(fd);
	return (0); */
		// printf("%s\n", grid_output);
	// printf("\n\ny is: %d\n\n", y);
	// printf("%s\n",*ft_split(grid_output, ' '));
	// printf("\n\ny_max is : %d\n\n", grid->y_max);
	// printf("\n\n%d\n\n", (grid->x_max * grid->y_max));
	// printf("\n\n%d | %d\n\n", grid->x_max, grid->y_max);
	// printf("\n\nLign is ----->    %s   \n\n", lines[y]);
	// printf( "\n\nx_max is: %d;\ny_max is: %d;\n\n", grid->x_max, grid->y_max);
	// printf("\n\ngrid_x_max is: %d || grid_y_max is: %d || pointer on grid_data is: %p\n\n", grid->x_max, grid->y_max, grid->grid_data);
	// printf("\n\n  --  lines is: %s --  \n\n", lines[i + 7]);
	// printf("\n\n%d\n\n", grid->x_max);
	// printf("\n\n%d\n\n", grid->grid_data[2][2]);
	// printf("\n\n--- grid->x_max is: %d || grid->y_max is: %d ---\n\n", grid->x_max, grid->y_max);
	// printf("grid_x_max is: %d\n", grid->x_max);
	// printf("\n\n%d\n\n", x);
	// printf("\033[0;31m");
	// printf("\n\n%d || %d\n\n", *grid[y], y);
	// printf("\033[0m");
	// printf("\n\n%s || %d\n\n", line, y);
	// printf("\n\n%s || %d\n\n", line, y);
	/* 	while (i < 100)
			printf("\n%s\n", lines[i]);
			i++;
		}
		return (grid); 
	*/