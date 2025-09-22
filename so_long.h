/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:39:42 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/22 15:25:34 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <mlx.h>

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_map
{
	char		**map;
	t_vector	size;
	t_vector	player_pos;
	int			coll_cnt;
	int			coll_found;
	int			player_on_exit;
	int			player_cnt;
	int			exit_cnt;
}	t_map;

typedef struct s_path
{
	int		exit_fnd;
	int		coll_fnd;
	char	**cpy;
}	t_path;

typedef struct s_image
{
	void		*pointer;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}	t_image;

typedef struct s_sprites
{
	t_image	img_back;
	t_image	img_walls;
	t_image	img_player;
	t_image	img_coll;
	t_image	img_exit;
}	t_sprites;

typedef struct s_window
{
	void		*win;
	t_image		*buffer;
	t_vector	size;
}	t_window;

typedef struct s_program
{
	void		*mlx;
	t_window	window;
	t_map		*map;
	t_sprites	sprites;
	int			move_cnt;
}	t_program;

int		ft_strlen_sl(const char *s);
int		ft_valid_walls(t_map *map);
void	ft_flood_fill(t_map *map, t_path *path, int i, int j);
int		ft_valid_path(t_map *map);
void	ft_valid_map(t_map *map);
void	ft_free_2d(char **strs, t_map *map);
t_image	ft_new_sprite(void *mlx, char *path);
void	ft_get_sprites(t_program *prog);
void	ft_put_map(t_program *prog);
int		ft_key_input(int key, void *param);
int		ft_update(void *param);

#endif
