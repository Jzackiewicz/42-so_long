/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:23:16 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 16:02:48 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_all_images(t_mlx_data *mlx_data)
{
	int	i;

	i = 0;
	while(mlx_data->images[i])
	{
		ft_printf("i: %d\n", i);
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->images[i]);
		i++;
	}
	free(mlx_data->images);
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_printf("|%c|", map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
