/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 09:46:59 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/21 16:44:43 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen_gnl(const char *s);
void	ft_strcpy_gnl(char *dst, char *src);
void	ft_strncat_gnl(char *dst, char *src, size_t n);
char	*ft_realloc_gnl(char *ptr, size_t size);
int		eol_found(char *line);
char	*get_next_line(int fd);

#endif