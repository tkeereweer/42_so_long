/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:50:17 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/17 17:13:22 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	img;

	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.pointer, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	return (img);
}

void	ft_get_sprites(t_program *prog)
{
	prog->sprites.img_back = ft_new_sprite(prog->mlx, "sprites/back_block.xpm");
	prog->sprites.img_walls = ft_new_sprite(prog->mlx, "sprites/walls.xpm");
	prog->sprites.img_player = ft_new_sprite(prog->mlx, "sprites/player.xpm");
	prog->sprites.img_coll = ft_new_sprite(prog->mlx, "sprites/fruit.xpm");
	prog->sprites.img_exit = ft_new_sprite(prog->mlx, "sprites/exit.xpm");
}

void	ft_put_background(t_program *prog)
{
	int	i;
	int	j;

	i = 0;
	while (prog->window.size.x > 64 * i)
	{
		j = 0;
		while (prog->window.size.y > 64 * j)
		{
			mlx_put_image_to_window(prog->mlx, prog->window.win,
				prog->sprites.img_back.pointer, 64 * i, 64 * j);
			j++;
		}
		i++;
	}
}

void	ft_put_map(t_program *prog)
{
	int	i;
	int	j;

	i = 0;
	ft_put_background(prog);
	while (prog->window.size.x > 64 * i)
	{
		j = 0;
		while (prog->window.size.y > 64 * j)
		{
			if (prog->map->map[i][j] == 'P')
				mlx_put_image_to_window(prog->mlx, prog->window.win,
					prog->sprites.img_player.pointer, 64 * i, 64 * j);
			else if (prog->map->map[i][j] == 'C')
				mlx_put_image_to_window(prog->mlx, prog->window.win,
					prog->sprites.img_coll.pointer, 64 * i, 64 * j);
			else if (prog->map->map[i][j] == 'E')
				mlx_put_image_to_window(prog->mlx, prog->window.win,
					prog->sprites.img_exit.pointer, 64 * i, 64 * j);
			else if (prog->map->map[i][j] == '1')
				mlx_put_image_to_window(prog->mlx, prog->window.win,
					prog->sprites.img_walls.pointer, 64 * i, 64 * j);
			j++;
		}
		i++;
	}
}
