
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
# define SPACE 10

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

/* enum	e_vars_coordonates__int
{
	x,
	y,
	z,
	sep,
	z_angle,
	size_map_abs,
	size_map_ord
}; */

/* typedef struct
{
	int 	win_x;
	int		win_y;
}			t_prm;
 */



typedef	struct	t_vct
{
	float			x;
	float			y;
	int				is_last;
	struct t_vct	*next;
}					t_vct;
	
typedef struct
{	
	int		line_abs_len;
	float	x[3];
	float	y[3];
	float	z[3];
	float	steps[2];
	float	x_incr[2];
	float	y_incr[2];
	int		x_delta[2];
	int		y_delta[2];
	float	angle;
	float	scale;
	int		x_win;
	int		y_win;
	int		space;
	float	z_scale;
} 			t_pxl;

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
