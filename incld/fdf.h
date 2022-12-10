
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
# define BUFFER_SIZE 10
# define SPACE 10
# define WINDOW_HEIGHT 1442
# define WINDOW_WIDTH 2700
# define WIN_X WINDOW_WIDTH / 2.5
# define WIN_Y WINDOW_HEIGHT / 2.5

# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/cursorfont.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>


// MLX
typedef	struct
{
	void		*mlx_win;
	void		*mlx;
	char		*addr;
	void		*img;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}					t_prog;
// VECT
typedef	struct		s_vct
{
	float			x;
	float			y;
	int				is_last;
	struct s_vct	*next;
}					t_vct;
// DRAW
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
	int		space;
	float	z_scale;
} 			t_pxl;
// GRID
typedef struct
{
	int		**grid_data;
	int		y_max;
	int		x_max;
}				r_data;
// // FUNCS
// GRID
r_data	*push_coordonnates(r_data *grid, char *grid_output);
r_data 	*parse_grid(int fd);
// PRINT
void	print_line(t_vct *line);
void	print_grid_data(r_data *grid);
// MAIN
int		check_fd(int ac);
// ERROR
void       ft_error(char *error_message);
// DRAW
void	center_draw(t_prog vars, r_data *grid);
void	my_mlx_pixel_put(t_prog vars, int x, int y, int color);
void 	draw_line(t_vct *line, t_vct *line_ord, t_pxl *draw, t_prog vars);
void	draw_first_line(t_vct *line, t_pxl *draw, t_prog vars);
void 	is_last_ordonnate_segment(t_vct *line, t_vct *line_ord, t_pxl *draw, t_prog vars);
// SAVE
t_vct	*save_coordonates_ord(t_vct *input, int len);
// CALC
int		data_width(char *line);
r_data	*assign_coordonnates_max(char *buf);
r_data 	*get_number_of_lines(char *buf, r_data *grid);
void	attribute_z_coordonates(t_pxl *draw, r_data *grid, int x, int y);
void	scale_draw_variables(t_pxl *draw);
void	attribute_iso_coordonates(t_pxl *draw);
t_vct	*segments_absord_calculating(t_pxl *draw, int grid_x, int grid_y, t_vct *line);
t_pxl	*calculate_pixels_first_incrementation(t_pxl *draw, float *x, float *y, t_vct *line);
t_pxl	*calculate_pixels_incrementation(t_pxl *draw, float *x, float *y, t_vct *line, t_vct *line_ord);
// CONVERT
int	ft_atoi(char *nptr);
// GNL
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
// INIT
t_pxl	*init_t_pxl(void);
// FREE
// 
// ALLOC
// static char	**mallocrash(char **tab);
t_vct		*elem_addto_line(t_vct **line);
t_vct		*save_coordonates_ord(t_vct *input, int len);
void		malloc_line(t_vct **line, int number_elems);
// SPLIT
char	**ft_split(char const *s, char c);


#endif
