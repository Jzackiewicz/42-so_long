/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:17 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/25 18:17:19 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	void		*img;
	int			width;
	int			height;
	char		*filename;
	char		**map;
	
	map = load_map(argc, argv);
	int i = 0;
	int	j = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			ft_printf("%c", map[i][j]);
			j++;
		}
		i++;
	}
	mlx_data.mlx_ptr = mlx_init();
	if (!mlx_data.mlx_ptr)
		exit(-1);
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, 800, 600, "so_long");
	if (!mlx_data.win_ptr)
	{
		mlx_destroy_display(mlx_data.mlx_ptr);
		free(mlx_data.mlx_ptr);
		exit(-1);
	}
	mlx_key_hook(mlx_data.win_ptr, handle_key_input, &mlx_data);
	mlx_hook(mlx_data.win_ptr, 17, 0, close_window, &mlx_data);
	width = 16;
	height = 16;
	filename = "textures/grass.xpm";
	img = mlx_xpm_file_to_image(mlx_data.mlx_ptr, filename, &width, &height);
	mlx_put_image_to_window(mlx_data.mlx_ptr, mlx_data.win_ptr, img, 300, 300);
	mlx_loop(mlx_data.mlx_ptr);
	mlx_destroy_window(mlx_data.mlx_ptr, mlx_data.win_ptr);
	mlx_destroy_display(mlx_data.mlx_ptr);
	free(mlx_data.mlx_ptr);
	return (0);
}