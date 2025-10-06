/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:49:02 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/06 14:54:36 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

static void	ft_map_error(char *error_msg, t_program *prog)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error_msg, 2);
	ft_free_2d(prog->map->map, prog->map);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	exit(1);
}

void	ft_valid_map(t_program *prog)
{
	if (ft_valid_rectangle(prog->map) != 1)
		ft_map_error("The map is not a rectangle", prog);
	else if (ft_valid_items(prog->map) != 1)
		ft_map_error("The map does not have all valid items", prog);
	if (ft_valid_walls(prog->map) != 1)
		ft_map_error("The map is not enclosed by walls", prog);
	if (ft_valid_path(prog->map) != 1)
		ft_map_error("There is no valid path to finish the game", prog);
}
