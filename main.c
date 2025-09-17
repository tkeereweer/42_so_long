/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:19:39 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/17 17:09:56 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_get_map(void)
{
	char	**map;

	map = (char **) malloc(5 * sizeof(char *));
	map[0] = ft_strdup("1111111111111");
	map[1] = ft_strdup("10010000000C1");
	map[2] = ft_strdup("1000011111001");
	map[3] = ft_strdup("1P0011E000001");
	map[4] = ft_strdup("1111111111111");
	return (map);
}

void	ft_new_window(t_program *prog)
{
	prog->window.size.x = 64 * 5;
	prog->window.size.y = 64 * 13;
	prog->window.win = mlx_new_window(prog->mlx,
			prog->window.size.x, prog->window.size.y, "so_long");
	mlx_hook(prog->window.win, 65307, 0, *ft_close, 0);
}

int	main(void)
{
	t_program	prog;
	t_map		map_struct;

	prog.mlx = mlx_init();
	ft_get_sprites(&prog);
	map_struct.map = ft_get_map();
	prog.map = &map_struct;
	prog.map->player_on_exit = 0;
	prog.map->coll_cnt = 1;
	prog.map->coll_found = 0;
	prog.map->player_x = 3;
	prog.map->player_y = 1;
	ft_new_window(&prog);
	ft_put_map(&prog);
	mlx_key_hook(prog.window.win, *ft_key_input, &prog);
	mlx_loop(prog.mlx);
}
