/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:19:39 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/09 09:37:44 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	file_read_errors(t_program *prog, int mode)
{
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	if (mode == 0)
		ft_putstr_fd("Error\nInvalid path", 2);
	else if (mode == 1)
	{
		free(prog->map->map);
		ft_putstr_fd("Error\nEmpty file", 2);
	}
	exit(1);
}

int	read_file(t_program *prog, char *line, int fd)
{
	int	i;

	i = 1;
	while (line != (void *) 0)
	{
		prog->map->map = ft_realloc(prog->map->map, (i + 1) * sizeof(char *));
		if (prog->map->map == (void *) 0)
			exit(1);
		line = get_next_line(fd);
		if (line != (void *) 0)
			prog->map->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (i);
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
		file_read_errors(prog, 0);
	map = (char **) malloc(1 * sizeof(char *));
	if (map == (void *) 0)
		file_read_errors(prog, -1);
	prog->map->map = map;
	line = get_next_line(fd);
	if (line == (void *) 0)
		file_read_errors(prog, 1);
	prog->map->map[0] = ft_strdup(line);
	free (line);
	i = read_file(prog, line, fd);
	prog->map->size.x = ft_strlen_sl(prog->map->map[0]);
	prog->map->size.y = i - 1;
	close(fd);
}

static void	ft_new_window(t_program *prog)
{
	prog->window.size.x = 64 * prog->map->size.x;
	prog->window.size.y = 64 * prog->map->size.y;
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
	prog.map = &map;
	ft_get_map(argv[1], &prog);
	prog.map->coll_cnt = 0;
	prog.map->player_on_exit = 0;
	prog.map->coll_found = 0;
	prog.map->player_cnt = 0;
	prog.map->exit_cnt = 0;
	ft_valid_map(&prog);
	ft_get_sprites(&prog);
	prog.move_cnt = 1;
	ft_new_window(&prog);
	mlx_loop_hook(prog.mlx, *ft_update, &prog);
	mlx_key_hook(prog.window.win, *ft_key_input, &prog);
	mlx_hook(prog.window.win, 17, 0, *ft_close, &prog);
	mlx_loop(prog.mlx);
}
