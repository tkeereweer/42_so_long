/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:19:39 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/20 12:39:55 by mkeerewe         ###   ########.fr       */
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
	out = (char **) ft_memmove(out, strs, size - sizeof(char *));
	return (out);
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
		return ;
	map = (char **) malloc(1 * sizeof(char *));
	if (map == (void *) 0)
		return ;
	prog->map->map = map;
	line = get_next_line(fd);
	prog->map->map[0] = ft_strdup(line);
	while (line != (void *) 0)
	{
		prog->map->map = ft_realloc(prog->map->map, (i + 1) * sizeof(char *));
		if (prog->map->map == (void *) 0)
			return ;
		line = get_next_line(fd);
		if (line != (void *) 0)
			prog->map->map[i] = ft_strdup(line);
		i++;
	}
	prog->map->size.x = ft_strlen(prog->map->map[0]) - 1;
	prog->map->size.y = i - 1;
	close(fd);
}

void	ft_free_2d(char **strs, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size.y)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
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
	// get map size from read file
	// prog.map->size.x = 13;
	// prog.map->size.y = 5;
	ft_valid_map(prog.map);
	// prog.map->player_pos.x = 1;
	// prog.map->player_pos.y = 3;
	ft_new_window(&prog);
	ft_put_map(&prog);
	mlx_key_hook(prog.window.win, *ft_key_input, &prog);
	mlx_loop_hook(prog.mlx, *ft_update, &prog);
	mlx_loop(prog.mlx);
}
