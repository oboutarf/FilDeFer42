
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:24:41 by oboutarf          #+#    #+#             */
/*   Updated: 2022/11/02 22:02:26 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 10000
# define SEP 10
// # define DEFAULT grid[0][0]

# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

// STRUCTURE FOR MAP
/**/
/**/

typedef struct
{
	char	*addr;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct
{
	int		**grid_data;
	int		last_data;
	int		y_max;
	int		x_max;
}				r_data;

// 	SPLIT_FUNCS
//	************
static char	**mallocrash(char **tab);
static char	*ft_mystrlcpy(char *dest, char *src, int size, int i);
static int	tablength(char const *s, char c);
static int	myanti_c(char const *s, int i, char c);
char	**ft_split(char const *s, char c);


// 	READ INPUT MAP TO GATHER INFORMATION
//	************************************
void	print_grid_data(r_data *grid);
r_data 	*parse_grid(char *input_file, int fd);
size_t	ft_strlen(char *str);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	ft_mylstbuf(char *buf, char *lgn, int s_bin);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_getbn(char *lgn, int s_bin);
int		ft_strbn(char *str);
void    ft_error_noinput(void);

// 	DRAWING FUNCTIONS
//	************************************
void	center_draw(t_data img, r_data *grid, void *mlx, void *mlx_win);

#endif
