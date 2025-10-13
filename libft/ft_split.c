/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:42:49 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/08/30 15:39:56 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_chrcat(char *dst, const char c)
{
	int	i;

	i = 0;
	while (dst[i] != '\0')
		i++;
	dst[i] = c;
	dst[i + 1] = '\0';
}

void	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
}

static void	strsplit(char **arr, char *tmp, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			ft_chrcat(tmp, s[i]);
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				arr[j] = (char *) malloc((ft_strlen(tmp) + 1) * sizeof(char));
				if (arr[j] == (void *) 0)
					return ;
				ft_strcpy(arr[j], tmp);
				j++;
				tmp[0] = '\0';
			}
		}
		i++;
	}
	arr[j] = (void *) 0;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*tmp;

	if (s == (void *) 0)
		return ((void *) 0);
	arr = (char **) malloc((ft_strlen(s) / 2 + 2) * sizeof(char *));
	if (arr == (void *) 0)
		return (arr);
	tmp = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (tmp == (void *) 0)
	{
		free(arr);
		return ((void *) 0);
	}
	tmp[0] = '\0';
	strsplit(arr, tmp, s, c);
	free(tmp);
	return (arr);
}
