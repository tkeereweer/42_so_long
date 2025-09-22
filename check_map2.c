/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:13:49 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/22 15:15:07 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_valid_walls(t_map *map)
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

void	ft_flood_fill(t_map *map, t_path *path, int i, int j)
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

int	ft_valid_path(t_map *map)
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
