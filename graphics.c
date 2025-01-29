/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:51:03 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 18:34:12 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	choose_best_resolution(t_mlx_data *mlx_data)
{
	int	window_height;
	int	window_width;

	window_height = ft_2d_strlen(mlx_data->map_data.map);
	window_width = ft_strlen(mlx_data->map_data.map[0]);
	mlx_data->height = 1080;
	mlx_data->width = 1920;
	if (window_height * 64 < mlx_data->height && window_width
		* 64 < mlx_data->width)
		mlx_data->img_side_len = 64;
	else if (window_height * 32 < mlx_data->height && window_width
		* 32 < mlx_data->width)
		mlx_data->img_side_len = 32;
	else
		mlx_data->img_side_len = 16;
	mlx_data->height = window_height * mlx_data->img_side_len;
	mlx_data->width = window_width * mlx_data->img_side_len;
	if (mlx_data->img_side_len == 64)
		mlx_data->textures_subdir = "textures/64x64/";
	else if (mlx_data->img_side_len == 32)
		mlx_data->textures_subdir = "textures/32x32/";
	else if (mlx_data->img_side_len == 16)
		mlx_data->textures_subdir = "textures/16x16/";
}

static void	load_images(t_mlx_data *mlx_data)
{
	int		i;
	char	*filename;

	mlx_data->images = (void **)ft_calloc(sizeof(void *), 7);
	i = -1;
	while (++i < 6)
	{
		if (i == 0)
			filename = ft_strjoin(mlx_data->textures_subdir, "grass.xpm");
		if (i == 1)
			filename = ft_strjoin(mlx_data->textures_subdir, "wall.xpm");
		if (i == 2)
			filename = ft_strjoin(mlx_data->textures_subdir, "coll.xpm");
		if (i == 3)
			filename = ft_strjoin(mlx_data->textures_subdir, "end_red.xpm");
		if (i == 4)
			filename = ft_strjoin(mlx_data->textures_subdir, "char.xpm");
		if (i == 5)
			filename = ft_strjoin(mlx_data->textures_subdir, "end.xpm");
		mlx_data->images[i] = mlx_xpm_file_to_image(mlx_data->mlx_ptr, filename,
				&mlx_data->img_side_len, &mlx_data->img_side_len);
		free(filename);
	}
}

void	visualize_map(t_mlx_data *mlx_data)
{
	int	i;
	int	j;
	int	img_id;

	i = -1;
	load_images(mlx_data);
	while (mlx_data->map_data.map[++i])
	{
		j = -1;
		while (mlx_data->map_data.map[i][++j])
		{
			img_id = 0;
			if (mlx_data->map_data.map[i][j] == '1')
				img_id = 1;
			if (mlx_data->map_data.map[i][j] == 'C')
				img_id = 2;
			if (mlx_data->map_data.map[i][j] == 'E')
				img_id = 3;
			if (mlx_data->map_data.map[i][j] == 'P')
				img_id = 4;
			mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr,
				mlx_data->images[img_id], j * mlx_data->img_side_len, i
				* mlx_data->img_side_len);
		}
	}
}
