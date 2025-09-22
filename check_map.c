/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:49:02 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/22 15:21:02 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_valid_rectangle(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size.y)
	{
		if (ft_strlen_sl(map->map[i]) != map->size.x)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_items(t_map *map, int *i, int *j)
{
	if (map->map[*i][*j] == 'E')
		map->exit_cnt++;
	else if (map->map[*i][*j] == 'P')
	{
		map->player_cnt++;
		map->player_pos.x = *j;
		map->player_pos.y = *i;
	}
	else if (map->map[*i][*j] == 'C')
		map->coll_cnt++;
	else if (map->map[*i][*j] != '0' && map->map[*i][*j] != '1')
		return (0);
	return (1);
}

static int	ft_valid_items(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			if (ft_check_items(map, &i, &j) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (map->exit_cnt != 1 || map->player_cnt != 1 || map->coll_cnt < 1)
		return (0);
	return (1);
}

void	ft_valid_map(t_map *map)
{
	if (ft_valid_rectangle(map) != 1)
	{
		ft_putstr_fd("Error\nInvalid map", 1);
		ft_free_2d(map->map, map);
		exit(0);
	}
	else if (ft_valid_items(map) != 1)
	{
		ft_putstr_fd("Error\nInvalid map", 1);
		ft_free_2d(map->map, map);
		exit(0);
	}
	if (ft_valid_walls(map) != 1)
	{
		ft_putstr_fd("Error\nInvalid map", 1);
		ft_free_2d(map->map, map);
		exit(0);
	}
	if (ft_valid_path(map) != 1)
	{
		ft_putstr_fd("Error\nInvalid map", 1);
		ft_free_2d(map->map, map);
		exit(0);
	}
}
