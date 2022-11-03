
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
# define BUFFER_SIZE 1
// # define DEFAULT map[0][0]

#include "../mlx/mlx_int.h"
#include "../mlx/mlx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

// STRUCTURE FOR MAP
/**/
/**/

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}			t_data;

/* typedef struct
{
	float		x;
	float		y;
	float		z;
	int			is_last;

	int			color;
	int			scale;
	int			z_scale;
	int			shift_x;
	int			shift_y;
	int			is_isometric;
	double		angle;
	int			win_x;
	int			win_y;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_data;
 */


// 	SPLIT_FUNCS
//	************
static char	**mallocrash(char **tab);
static char	*ft_mystrlcpy(char *dest, char *src, int size, int i);
static int	tablength(char const *s, char c);
static int	myanti_c(char const *s, int i, char c);
char	**ft_split(char const *s, char c);


// 	READ INPUT MAP TO GATHER INFORMATION
//	************************************
int	   	**parse_grid(char *input_file, int fd);
char	*get_next_line(int fd);
size_t	ft_strlen(char *str);
void	ft_bzero(void *s, size_t n);
void	ft_mylstbuf(char *buf, char *lgn, int s_bin);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_getbn(char *lgn, int s_bin);
int		ft_strbn(char *str);
void    ft_error_noinput(void);

#endif
