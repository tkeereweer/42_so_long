/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 22:15:11 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/01 13:52:24 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_format
{
	int	ht;
	int	space;
	int	plus;
}	t_format;

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_putchar(char c);
int		ft_putnbr(int n, t_format *format);
int		ft_putuint(unsigned int n, int ret);
int		ft_putstr(char *s);
int		ft_puthex(unsigned int n, int cap, t_format *format);
int		ft_putptr(void *ptr);
int		ft_printf(const char *str, ...);

#endif
