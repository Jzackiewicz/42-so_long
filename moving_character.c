/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:38:58 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 18:36:14 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static void	change_exit_block(t_mlx_data *mlx_data)
{
	int	exit_x;
	int	exit_y;

	exit_x = -1;
	while (mlx_data->map_data.map[++exit_x])
	{
		exit_y = -1;
		while (mlx_data->map_data.map[exit_x][++exit_y])
		{
			if (mlx_data->map_data.map[exit_x][exit_y] == 'E')
				break ;
		}
		if (mlx_data->map_data.map[exit_x][exit_y] == 'E')
			break ;
	}
	if (mlx_data->map_data.collectible_count == 0)
		mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
			mlx_data->images[5], exit_y * mlx_data->img_side_len, exit_x
			* mlx_data->img_side_len);
}

static void	check_collectibles(t_mlx_data *mlx_data, int new_x, int new_y)
{
	if (mlx_data->map_data.map[new_y][new_x] == 'C')
		mlx_data->map_data.collectible_count--;
	if (mlx_data->map_data.map[new_y][new_x] == 'E'
		&& mlx_data->map_data.collectible_count == 0)
	{
		free_all_stuff(mlx_data);
		exit(1);
	}
}

static void	update_window(t_mlx_data *mlx_data, int new_x, int new_y)
{
	int	cur_x;
	int	cur_y;

	cur_x = mlx_data->map_data.cur_x;
	cur_y = mlx_data->map_data.cur_y;
	check_collectibles(mlx_data, new_x, new_y);
	change_exit_block(mlx_data);
	mlx_data->map_data.map[cur_y][cur_x] = '0';
	mlx_data->map_data.map[new_y][new_x] = 'P';
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
		mlx_data->images[0], cur_x * mlx_data->img_side_len, cur_y
		* mlx_data->img_side_len);
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
		mlx_data->images[4], new_x * mlx_data->img_side_len, new_y
		* mlx_data->img_side_len);
	mlx_data->map_data.cur_x = new_x;
	mlx_data->map_data.cur_y = new_y;
}

static void	move(t_mlx_data *mlx_data, int new_x, int new_y)
{
	int	max_x;
	int	max_y;

	max_x = mlx_data->width / mlx_data->img_side_len;
	max_y = mlx_data->height / mlx_data->img_side_len;
	if (mlx_data->map_data.map[new_y][new_x] != '1'
		&& new_x >= 0 && new_y >= 0
		&& new_x <= max_x && new_y <= max_y
		&& (mlx_data->map_data.map[new_y][new_x] != 'E'
			|| !mlx_data->map_data.collectible_count))
	{
		mlx_data->map_data.moves_count++;
		ft_printf("Moves count: %d\n", mlx_data->map_data.moves_count);
		update_window(mlx_data, new_x, new_y);
	}
}

void	move_in_direction(t_mlx_data *mlx_data, char *direction)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = mlx_data->map_data.cur_x;
	tmp_y = mlx_data->map_data.cur_y;
	if (!ft_strncmp(direction, "up", 2))
		move(mlx_data, tmp_x, tmp_y - 1);
	if (!ft_strncmp(direction, "down", 5))
		move(mlx_data, tmp_x, tmp_y + 1);
	if (!ft_strncmp(direction, "left", 5))
		move(mlx_data, tmp_x - 1, tmp_y);
	if (!ft_strncmp(direction, "right", 6))
		move(mlx_data, tmp_x + 1, tmp_y);
}
