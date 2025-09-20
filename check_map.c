/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:49:02 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/20 11:34:29 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_valid_items(t_map *map)
{
	int	i;
	int	j;
	int	exit_cnt;
	int	player_cnt;

	i = 0;
	exit_cnt = 0;
	player_cnt = 0;
	while (i < map->size.y)
	{
		j = 0;
		while (j < map->size.x)
		{
			if (map->map[i][j] == 'E')
				exit_cnt++;
			else if (map->map[i][j] == 'P')
			{
				player_cnt++;
				map->player_pos.x = j;
				map->player_pos.y = i;
			}
			else if (map->map[i][j] == 'C')
				map->coll_cnt++;
			else if (map->map[i][j] != '0' && map->map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	if (exit_cnt != 1 || player_cnt != 1 || map->coll_cnt < 1)
		return (0);
	else
		return (1);
}

static int	ft_valid_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size.y)
	{
		if (map->map[i][0] != '1' || map->map[i][map->size.x - 1] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->size.x)
	{
		if (map->map[0][i] != '1' || map->map[map->size.y - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_flood_fill(t_map *map, t_path *path, int i, int j)
{
	if (map->map[i][j] == '1' || path->cpy[i][j] == '1')
		return ;
	else if (map->map[i][j] == 'E')
		path->exit_fnd++;
	else if (map->map[i][j] == 'C')
		path->coll_fnd++;
	path->cpy[i][j] = '1';
	ft_flood_fill(map, path, i + 1, j);
	ft_flood_fill(map, path, i - 1, j);
	ft_flood_fill(map, path, i, j + 1);
	ft_flood_fill(map, path, i, j - 1);
}

static int	ft_valid_path(t_map *map)
{
	t_path	path;
	char	**cpy;
	int		i;

	path.coll_fnd = 0;
	path.exit_fnd = 0;
	cpy = (char **) malloc(map->size.y * sizeof(char *));
	if (cpy == (void *) 0)
		return (0);
	i = 0;
	while (i < map->size.y)
	{
		cpy[i] = ft_strdup(map->map[i]);
		i++;
	}
	path.cpy = cpy;
	ft_flood_fill(map, &path, map->player_pos.y, map->player_pos.x);
	ft_free_2d(path.cpy, map);
	if (path.coll_fnd == map->coll_cnt && path.exit_fnd == 1)
		return (1);
	return (0);
}

void	ft_valid_map(t_map *map)
{
	if (ft_valid_items(map) != 1)
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
