/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:24:41 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/12 16:01:55 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 1440
# endif
# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 2560
# endif

# include "../mlx/mlx_int.h"
# include "../gnl/get_next_line.h"
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
typedef struct s_prog
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
typedef struct s_vct
{
	float			x;
	float			y;
	float			is_last;
	struct s_vct	*next;
}					t_vct;
// DRAW
typedef struct s_pxl
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
}			t_pxl;
// GRID
typedef struct s_data
{
	int		**grid_data;
	int		y_max;
	int		x_max;
}				t_data;

// // FUNCS
// EVENTS
int		key_hook(int keycode, t_prog *vars);
// GRID
t_data	*push_coordonnates(t_data *grid, char *grid_output);
t_data	*parse_grid(int fd);
// PRINT
void	print_line(t_vct *line);
void	print_grid_data(t_data *grid);
// MAIN
int		check_fd(int ac);
// ERROR
void	ft_error(char *error_message);
// DRAW
void	center_draw(t_prog vars, t_data *grid);
t_vct	*start_process_draw(t_data *grid, t_prog vars,
			t_pxl *draw, t_vct *line);
void	paint_it(t_pxl *draw, float *x, float *y, t_prog vars);
void	display_px(t_prog vars, int x, int y, int color);
void	choose_line(t_pxl *draw, t_vct *line,
			t_vct *line_ord, t_prog vars);
void	draw_line(t_vct *line, t_vct *line_ord, t_pxl *draw, t_prog vars);
void	draw_first_line(t_vct *line, t_pxl *draw, t_prog vars);
void	is_last_ordonnate_segment(t_vct *line, t_vct *line_ord,
			t_pxl *draw, t_prog vars);
// SAVE
void	save_coordonates_ord(t_vct *input, t_vct **output, int len);
// CALC
int		data_width(char *line);
t_data	*assign_coordonnates_max(char *buf);
void	calculate_delta_between_coordonates(t_pxl *draw, float *x, float *y);
void	assign_coordonates_dda(t_vct *line, t_vct *line_ord,
			float *x, float *y);
t_data	*get_number_of_lines(char *buf, t_data *grid);
void	attribute_z_coordonates(t_pxl *draw, t_data *grid, int x, int y);
void	scale_draw_variables(t_pxl *draw);
void	attribute_iso_coordonates(t_pxl *draw);
t_vct	*segments_absord_calculating(t_pxl *draw, int grid_x,
			int grid_y, t_vct *line);
t_pxl	*calculate_pixels_first_incrementation(t_pxl *draw, float *x,
			float *y, t_vct *line);
t_pxl	*calculate_pixels_incrementation(t_pxl *draw);
// CONVERT
int		ft_atoi(char *nptr);
// GNL
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
// INIT
t_pxl	*init_t_pxl(t_data *grid);
void	make_inits(t_vct *line_ord, int *iter, t_data *grid, t_pxl *draw);
// FREE
// 
// ALLOC
// static char	**mallocrash(char **tab);
t_vct	*elem_addto_line(t_vct **line);
void	free_l(t_vct **line, int size);
void	free_grid_data(t_data *grid);
void	*ft_calloc(size_t nmemb, size_t size);
void	malloc_line(t_vct **line, int number_elems);
void	*ft_memset(void *s, int c, size_t n);
t_data	*malloc_grid(t_data *grid, int y);
// SPLIT
char	**ft_split(char const *s, char c);

#endif
