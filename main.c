/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:19:39 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/26 11:20:42 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

// char	**ft_get_map(void)
// {
// 	char	**map;

// 	map = (char **) malloc(5 * sizeof(char *));
// 	map[0] = ft_strdup("1111111111111");
// 	map[1] = ft_strdup("10010000000C1");
// 	map[2] = ft_strdup("1000011111001");
// 	map[3] = ft_strdup("1P0011E000001");
// 	map[4] = ft_strdup("1111111111111");
// 	return (map);
// }

char	**ft_realloc(char **strs, int size)
{
	char	**out;

	out = (char **) malloc(size * sizeof(char *));
	if (out == (void *) 0)
		return (out);
	if (strs != (void *) 0)
		out = (char **) ft_memmove(out, strs, size - sizeof(char *));
	free(strs);
	return (out);
}

void	read_file(t_program *prog, char **line, int fd, int i)
{
	prog->map->map = ft_realloc(prog->map->map, (i + 1) * sizeof(char *));
	if (prog->map->map == (void *) 0)
		return ;
	*line = get_next_line(fd);
	if (*line != (void *) 0)
		prog->map->map[i] = ft_strdup(*line);
}

void	ft_get_map(char *file, t_program *prog)
{
	char	**map;
	int		i;
	char	*line;
	int		fd;

	i = 1;
	line = (void *) 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);
	map = (char **) malloc(1 * sizeof(char *));
	if (map == (void *) 0)
		return ;
	prog->map->map = map;
	line = get_next_line(fd);
	prog->map->map[0] = ft_strdup(line);
	while (line != (void *) 0)
	{
		read_file(prog, &line, fd, i);
		i++;
	}
	prog->map->size.x = ft_strlen_sl(prog->map->map[0]);
	prog->map->size.y = i - 1;
	close(fd);
}

static void	ft_new_window(t_program *prog)
{
	prog->window.size.x = 64 * prog->map->size.x;
	prog->window.size.y = 64 * prog->map->size.y + 32;
	prog->window.win = mlx_new_window(prog->mlx,
			prog->window.size.x, prog->window.size.y, "so_long");
}

int	main(int argc, char *argv[])
{
	t_program	prog;
	t_map		map;

	if (argc != 2)
		exit(0);
	prog.mlx = mlx_init();
	ft_get_sprites(&prog);
	prog.map = &map;
	ft_get_map(argv[1], &prog);
	prog.map->coll_cnt = 0;
	prog.map->player_on_exit = 0;
	prog.map->coll_found = 0;
	prog.map->player_cnt = 0;
	prog.map->exit_cnt = 0;
	ft_valid_map(prog.map);
	prog.move_cnt = 1;
	ft_new_window(&prog);
	ft_put_map(&prog);
	mlx_key_hook(prog.window.win, *ft_key_input, &prog);
	mlx_hook(prog.window.win, 17, 0, *ft_close, prog.map);
	mlx_loop_hook(prog.mlx, *ft_update, &prog);
	mlx_loop(prog.mlx);
}
