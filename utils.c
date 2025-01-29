/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:23:16 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 18:35:56 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

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
	while (mlx_data->images[i])
	{
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->images[i]);
		i++;
	}
	free(mlx_data->images);
}

void	free_all_stuff(t_mlx_data *mlx_data)
{
	if (mlx_data->map_data.map)
		free_map(mlx_data->map_data.map);
	if (mlx_data->images)
		free_all_images(mlx_data);
	if (mlx_data->win_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	if (mlx_data->mlx_ptr)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

void	free_all_exit(t_mlx_data *mlx_data, int err_id)
{
	free_all_stuff(mlx_data);
	exit(err_id);
}
