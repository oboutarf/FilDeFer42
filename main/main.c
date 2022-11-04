/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:27:16 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/04 05:17:03 by oboutarf         ###   ########.fr       */
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

int	main(int ac, char **av)
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
	return (0);
}


/* void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		x = 0;
	int		y = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
} */


	// t_data		**map;
	// if (ac != 2)
	// 	return (ft_error_noinput(), 1);
	// map = map_data_collector(av[ac]);









