/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:50:17 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/22 15:25:35 by mkeerewe         ###   ########.fr       */
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
			if (color != 0x00FFFFFF)
				*(unsigned int *)(dst->pixels + (dy + y) * dst->line_size
						+ (dx + x) * (dst->bits_per_pixel / 8)) = color;
			x++;
		}
		y++;
	}
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
	while (prog->window.size.y > 64 * i)
	{
		j = 0;
		while (prog->window.size.x > 64 * j)
		{
			draw_image_to_buffer(prog->window.buffer,
				&prog->sprites.img_back, 64 * j, 64 * i);
			j++;
		}
		i++;
	}
	// mlx_set_font(prog->mlx, prog->window.win, "-*-arial-medium-*-*-*-*-*-*-*-*-*-*-*");
	// mlx_string_put(prog->mlx, prog->window.win, prog->window.size.x / 2, 8, 0x00000000, "Hello");
}

void	ft_map_to_buffer(t_program *prog, int *i, int *j)
{
	if (prog->map->map[*i][*j] == 'P')
		draw_image_to_buffer(prog->window.buffer,
			&prog->sprites.img_player, 64 * *j, 64 * *i + 32);
	else if (prog->map->map[*i][*j] == 'C')
		draw_image_to_buffer(prog->window.buffer,
			&prog->sprites.img_coll, 64 * *j, 64 * *i + 32);
	else if (prog->map->map[*i][*j] == 'E')
		draw_image_to_buffer(prog->window.buffer,
			&prog->sprites.img_exit, 64 * *j, 64 * *i + 32);
	else if (prog->map->map[*i][*j] == '1')
		draw_image_to_buffer(prog->window.buffer,
			&prog->sprites.img_walls, 64 * *j, 64 * *i + 32);
}

void	ft_put_map(t_program *prog)
{
	int		i;
	int		j;
	t_image	buffer;

	i = 0;
	buffer.pointer = mlx_new_image(prog->mlx, prog->window.size.x,
			prog->window.size.y);
	buffer.pixels = mlx_get_data_addr(buffer.pointer,
			&buffer.bits_per_pixel, &buffer.line_size, &buffer.endian);
	prog->window.buffer = &buffer;
	buffer.size.x = prog->window.size.x;
	buffer.size.y = prog->window.size.y;
	ft_put_background(prog);
	while (prog->window.size.y > 64 * i + 32)
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
		prog->window.buffer->pointer, 0, 0);
}
