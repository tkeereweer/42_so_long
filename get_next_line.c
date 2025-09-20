/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:12 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/19 11:27:34 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	eol_found(char *line)
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

static char	*return_line(char *out, char *line)
{
	out = ft_realloc_gnl(out, ft_strlen_gnl(out) + ft_strlen_gnl(line) + 1);
	if (out == (void *) 0)
		return (out);
	ft_strncat_gnl(out, line, eol_found(line) + 1);
	ft_strcpy_gnl(line, &line[eol_found(line) + 1]);
	return (out);
}

char	*get_next_line(int fd)
{
	char			*out;
	static char		*line;
	int				cnt;
	// static size_t	len_line = 0;

	out = (void *) 0;
	line = ft_realloc_gnl(line, BUFFER_SIZE + 1);
	if (line == (void *) 0)
		return (line);
	cnt = -2;
	while (cnt != 0 && cnt != -1)
	{
		if (eol_found(line) != -1)
		{
			return (return_line(out, line));
		}
		out = ft_realloc_gnl(out, ft_strlen_gnl(out) + ft_strlen_gnl(line) + 1);
		if (out == (void *) 0)
			return (out);
		ft_strncat_gnl(out, line, ft_strlen_gnl(line));
		cnt = read(fd, line, BUFFER_SIZE);
		line[cnt] = '\0';
	}
	// free(line);
	if (ft_strlen_gnl(out) == 0)
	{
		free(out);
		out = (void *) 0;
	}
	return (out);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	ft_putstr_fd(get_next_line(fd), 1);
// 	ft_putstr_fd(get_next_line(fd), 1);
// 	close(fd);
// 	return (0);
// }
