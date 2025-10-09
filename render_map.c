/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:50:17 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/08 14:35:53 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_image_to_buffer(t_image *dst, t_image *src, int dx, int dy)
{
	int				y;
	int				x;
	unsigned int	color;

	y = 0;
	while (y < src->size.y && dy + y < dst->size.y)
	{
		x = 0;
		while (x < src->size.x && dx + x < dst->size.x)
		{
			color = *(unsigned int *)(src->pixels + y * src->line_size
					+ x * (src->bits_per_pixel / 8));
			if (color != 0xFFFFFFFF && color != 0xFF000000)
				*(unsigned int *)(dst->pixels + (dy + y) * dst->line_size
						+ (dx + x) * (dst->bits_per_pixel / 8)) = color;
			x++;
		}
		y++;
	}
}

void	ft_get_sprites(t_program *prog)
{
	prog->sprites.img_back = ft_new_sprite(prog->mlx,
			"textures/back_block.xpm");
	prog->sprites.img_walls = ft_new_sprite(prog->mlx, "textures/walls.xpm");
	prog->sprites.img_player = ft_new_sprite(prog->mlx, "textures/player.xpm");
	prog->sprites.img_coll = ft_new_sprite(prog->mlx, "textures/fruit.xpm");
	prog->sprites.img_exit = ft_new_sprite(prog->mlx, "textures/exit.xpm");
}

void	ft_put_background(t_program *prog)
{
	int	i;
	int	j;

	i = 0;
	while (prog->window.size.y > 64 * i)
	{
		j = 0;
		while (prog->window.size.x > 64 * j)
		{
			draw_image_to_buffer(&(prog->window.buffer),
				&prog->sprites.img_back, 64 * j, 64 * i);
			j++;
		}
		i++;
	}
}

void	ft_map_to_buffer(t_program *prog, int *i, int *j)
{
	if (prog->map->map[*i][*j] == 'P' && prog->map->player_on_exit == 1)
	{
		draw_image_to_buffer(&(prog->window.buffer),
			&prog->sprites.img_exit, 64 * *j, 64 * *i);
		draw_image_to_buffer(&(prog->window.buffer),
			&prog->sprites.img_player, 64 * *j, 64 * *i);
	}
	else if (prog->map->map[*i][*j] == 'P')
		draw_image_to_buffer(&(prog->window.buffer),
			&prog->sprites.img_player, 64 * *j, 64 * *i);
	else if (prog->map->map[*i][*j] == 'C')
		draw_image_to_buffer(&(prog->window.buffer),
			&prog->sprites.img_coll, 64 * *j, 64 * *i);
	else if (prog->map->map[*i][*j] == 'E')
		draw_image_to_buffer(&(prog->window.buffer),
			&prog->sprites.img_exit, 64 * *j, 64 * *i);
	else if (prog->map->map[*i][*j] == '1')
		draw_image_to_buffer(&(prog->window.buffer),
			&prog->sprites.img_walls, 64 * *j, 64 * *i);
}

void	ft_put_map(t_program *prog)
{
	int		i;
	int		j;

	i = 0;
	prog->window.buffer.pointer = mlx_new_image(prog->mlx, prog->window.size.x,
			prog->window.size.y);
	prog->window.buffer.pixels = mlx_get_data_addr(prog->window.buffer.pointer,
			&(prog->window.buffer.bits_per_pixel),
			&(prog->window.buffer.line_size), &(prog->window.buffer.endian));
	prog->window.buffer.size.x = prog->window.size.x;
	prog->window.buffer.size.y = prog->window.size.y;
	ft_put_background(prog);
	while (prog->window.size.y > 64 * i)
	{
		j = 0;
		while (prog->window.size.x > 64 * j)
		{
			ft_map_to_buffer(prog, &i, &j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(prog->mlx, prog->window.win,
		prog->window.buffer.pointer, 0, 0);
}
