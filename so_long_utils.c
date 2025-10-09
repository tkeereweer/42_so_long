/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:20:25 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/10/09 09:37:15 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_sl(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	return (i);
}

void	ft_free_2d(char **strs, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size.y)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_realloc(char **strs, int size)
{
	char	**out;

	out = (char **) malloc(size * sizeof(char *));
	if (out == (void *) 0)
		return (out);
	if (strs != (void *) 0)
		out = (char **) ft_memmove(out, strs, size - sizeof(char *));
	free(strs);
	return (out);
}

t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	img;

	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	if (img.pointer == (void *) 0)
		exit(1);
	img.pixels = mlx_get_data_addr(img.pointer, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	return (img);
}
