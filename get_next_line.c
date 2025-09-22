/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:12 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/21 16:42:35 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	init_var(char **line, int fd, char **out, int mode)
{
	int	cnt;

	if (mode == 0)
	{
		*line = ft_realloc_gnl(*line, BUFFER_SIZE + 1);
		if (*line == (void *) 0)
			return (0);
		cnt = read(fd, *line, BUFFER_SIZE);
		line[0][cnt] = '\0';
		return (1);
	}
	else
	{
		*out = (char *) malloc(1 * sizeof(char));
		if (*out == (void *) 0)
			return (0);
		out[0][0] = '\0';
		return (1);
	}
}

static char	*ret_null(char *out)
{
	free(out);
	out = (void *) 0;
	return (out);
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

static int	read_line(char **out, char *line, int fd)
{
	int	cnt;

	*out = ft_realloc_gnl(*out, ft_strlen_gnl(*out) + ft_strlen_gnl(line) + 1);
	if (*out == (void *) 0)
		return (-1);
	ft_strncat_gnl(*out, line, ft_strlen_gnl(line));
	cnt = read(fd, line, BUFFER_SIZE);
	line[cnt] = '\0';
	return (cnt);
}

char	*get_next_line(int fd)
{
	char			*out;
	static char		*line;
	int				cnt;

	if (line == 0)
	{
		if (init_var(&line, fd, (void *) 0, 0) == 0)
			return (line);
	}
	cnt = -2;
	if (init_var((void *) 0, fd, &out, 1) == 0)
		return (out);
	while (cnt != 0 && cnt != -1)
	{
		if (eol_found(line) != -1)
			return (return_line(out, line));
		cnt = read_line(&out, line, fd);
	}
	if (ft_strlen_gnl(out) == 0)
		out = ret_null(out);
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
