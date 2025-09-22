/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:23:30 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/21 16:45:48 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (s == (void *) 0)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_strcpy_gnl(char *dst, char *src)
{
	size_t	i;

	i = 0;
	if (src == (void *) 0)
		return ;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	ft_strncat_gnl(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (src == (void *) 0)
		return ;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
}

char	*ft_realloc_gnl(char *ptr, size_t size)
{
	char	*out;

	out = (char *) malloc(size);
	if (out == (void *) 0)
	{
		if (ptr != (void *) 0)
			free(ptr);
		return (out);
	}
	ft_strcpy_gnl(out, ptr);
	if (ptr != (void *) 0)
		free(ptr);
	return (out);
}

int	eol_found(char *line)
{
	int	i;

	i = 0;
	if (line == (void *) 0)
		return (-1);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
