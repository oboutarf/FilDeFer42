/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:15:30 by oboutarf          #+#    #+#             */
/*   Updated: 2022/12/11 17:55:12 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>

size_t	ft_strlen(char *str);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	ft_mylstbuf(char *buf, char *lgn, int s_bin);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_getbn(char *lgn, int s_bin);
int		ft_strbn(char *str);

#endif
