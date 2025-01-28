/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:17 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 16:55:45 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_mlx_data *mlx_data)
{
	int		i;
	t_img	img;
	char	*filename;
	
	mlx_data->img_side_len = 64;
	mlx_data->images = (t_img *)ft_calloc(sizeof(t_img), 5);
	img.img_ptr = mlx_new_image(mlx_data->mlx_ptr, mlx_data->img_side_len, mlx_data->img_side_len);
	img.img_pixels_ptr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_len, &img.endian);
	i = -1;
	while (++i < 5)
	{
		if (i == 0)
			filename = "textures/64x64/grass.xpm";
		if (i == 1)
			filename = "textures/64x64/wall.xpm";
		if (i == 2)
			filename = "textures/64x64/coll.xpm";
		if (i == 3)
			filename = "textures/64x64/end.xpm";
		if (i == 4)
			filename = "textures/64x64/char.xpm";
		mlx_data->images[i] = mlx_xpm_file_to_image(mlx_data->mlx_ptr, filename, &mlx_data->img_side_len, &mlx_data->img_side_len);
	}
}

void	visualize_map(t_mlx_data *mlx_data)
{
	int		i;
	int		j;
	int		img_id;
	
	i = -1;
	load_images(mlx_data);
	while(mlx_data->map[++i])
	{
		j = -1;
		while(mlx_data->map[i][++j])
		{
			if (mlx_data->map[i][j] == '0')
				img_id = 0;
			if (mlx_data->map[i][j] == '1')
				img_id = 1;
			if (mlx_data->map[i][j] == 'C')
				img_id = 2;
			if (mlx_data->map[i][j] == 'E')
				img_id = 3;
			if (mlx_data->map[i][j] == 'P')
				img_id = 4;
			mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->images[img_id], j*mlx_data->img_side_len, i*mlx_data->img_side_len);
		}
	}
}

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	
	mlx_data.map = load_map(argc, argv);
	check_map(mlx_data.map);
	mlx_data.mlx_ptr = mlx_init();
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, ft_strlen(mlx_data.map[0]) * 64, ft_2d_strlen(mlx_data.map) * 64, "so_long");
	if (!mlx_data.mlx_ptr)
	{
		free_map(mlx_data.map);
		exit(-1);
	}
		
	if (!mlx_data.win_ptr)
	{
		mlx_destroy_display(mlx_data.mlx_ptr);
		free(mlx_data.win_ptr);
		free_map(mlx_data.map);
		exit(-1);
	}
	mlx_key_hook(mlx_data.win_ptr, handle_key_input, &mlx_data);
	mlx_hook(mlx_data.win_ptr, 17, 0, close_window, &mlx_data);
	visualize_map(&mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	mlx_destroy_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
	mlx_destroy_display(mlx_data.mlx_ptr);
	free_all_images(&mlx_data);
	free(mlx_data.mlx_ptr);
	return (0);
}
