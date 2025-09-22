/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:35:11 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/22 15:19:00 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_close(t_map *map)
{
	ft_free_2d(map->map, map);
	exit(0);
}

static char	ft_next_tile(int key, t_map *map)
{
	if (key == 65363)
		return (map->map[map->player_pos.y][map->player_pos.x + 1]);
	else if (key == 65361)
		return (map->map[map->player_pos.y][map->player_pos.x - 1]);
	else if (key == 65364)
		return (map->map[map->player_pos.y + 1][map->player_pos.x]);
	else
		return (map->map[map->player_pos.y - 1][map->player_pos.x]);
}

static void	ft_move(int key, t_map *map)
{
	if (map->player_on_exit == 1)
	{
		map->map[map->player_pos.y][map->player_pos.x] = 'E';
		map->player_on_exit = 0;
	}
	else
		map->map[map->player_pos.y][map->player_pos.x] = '0';
	if (key == 65363)
		map->player_pos.x += 1;
	else if (key == 65361)
		map->player_pos.x -= 1;
	else if (key == 65364)
		map->player_pos.y += 1;
	else if (key == 65362)
		map->player_pos.y -= 1;
	map->map[map->player_pos.y][map->player_pos.x] = 'P';
}

int	ft_key_input(int key, void *param)
{
	t_program	*prog;
	char		next_tile;

	prog = (t_program *)param;
	if (key == 65307)
		ft_close(prog->map);
	next_tile = ft_next_tile(key, prog->map);
	if (next_tile == '1')
		return (0);
	ft_printf("Move count: %i\n", prog->move_cnt++);
	if (next_tile == 'C')
		prog->map->coll_found += 1;
	ft_move(key, prog->map);
	if (next_tile == 'E')
	{
		if (prog->map->coll_cnt == prog->map->coll_found)
			ft_close(prog->map);
		prog->map->player_on_exit = 1;
	}
	ft_put_map(prog);
	return (0);
}

int	ft_update(void *param)
{
	t_program	*prog;

	prog = (t_program *)param;
	ft_put_map(prog);
	return (0);
}
