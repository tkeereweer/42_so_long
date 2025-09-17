/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:35:11 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/17 17:10:20 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close(void)
{
	exit(0);
}

static char	ft_next_tile(int key, t_map *map)
{
	if (key == 65363)
		return (map->map[map->player_x + 1][map->player_y]);
	else if (key == 65361)
		return (map->map[map->player_x - 1][map->player_y]);
	else if (key == 65364)
		return (map->map[map->player_x][map->player_y + 1]);
	else
		return (map->map[map->player_x][map->player_y - 1]);
}

static void	ft_move(int key, t_map *map)
{
	if (map->player_on_exit == 1)
	{
		map->map[map->player_x][map->player_y] = 'E';
		map->player_on_exit = 0;
	}
	else
		map->map[map->player_x][map->player_y] = '0';
	if (key == 65363)
		map->player_x += 1;
	else if (key == 65361)
		map->player_x -= 1;
	else if (key == 65364)
		map->player_y += 1;
	else if (key == 65362)
		map->player_y -= 1;
	map->map[map->player_x][map->player_y] = 'P';
}

int	ft_key_input(int key, void *param)
{
	t_program	*prog;
	char		next_tile;

	prog = (t_program *)param;
	next_tile = ft_next_tile(key, prog->map);
	if (next_tile == '1')
		return (0);
	else if (next_tile == 'C')
		prog->map->coll_found += 1;
	ft_move(key, prog->map);
	if (next_tile == 'E')
	{
		if (prog->map->coll_cnt == prog->map->coll_found)
		{
			exit(0);
		}
		prog->map->player_on_exit = 1;
	}
	ft_put_map(prog);
	return (0);
}
