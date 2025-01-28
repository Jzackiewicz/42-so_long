/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:17 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 15:09:42 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	visualize_map(char **map, t_mlx_data *mlx_data)
{
	int		i;
	int		j;
	int		img_side_len;
	void	*img;
	char	*filename;

	img_side_len = 64;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == '0')
				filename = "textures/64x64/grass.xpm";
			if (map[i][j] == '1')
				filename = "textures/64x64/wall.xpm";
			if (map[i][j] == 'C')
				filename = "textures/64x64/coll.xpm";
			if (map[i][j] == 'E')
				filename = "textures/64x64/end.xpm";
			if (map[i][j] == 'P')
				filename = "textures/64x64/char.xpm";
			img = mlx_xpm_file_to_image(mlx_data->mlx_ptr, filename, &img_side_len, &img_side_len);
			mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, img, j*img_side_len, i*img_side_len);
			j++;
		}
		i++;
	}
}

void	prepare_display(t_mlx_data *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, ft_strlen(mlx_data->map[0]) * 64, ft_2d_strlen(mlx_data->map) * 64, "so_long");
	if (!mlx_data->mlx_ptr)
		exit(-1);
	if (!mlx_data->win_ptr)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
		exit(-1);
	}
	mlx_key_hook(mlx_data->win_ptr, handle_key_input, &mlx_data);
	mlx_hook(mlx_data->win_ptr, 17, 0, close_window, &mlx_data);
}

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	
	mlx_data.map = load_map(argc, argv);
	check_map(mlx_data.map);
	prepare_display(&mlx_data);
	//visualize_map(map, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	mlx_destroy_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
	mlx_destroy_display(mlx_data.mlx_ptr);
	free(mlx_data.mlx_ptr);
	return (0);
}