/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:17 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 18:21:01 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;

	load_map(argc, argv, &mlx_data);
	check_map(mlx_data.map_data);
	mlx_data.mlx_ptr = mlx_init();
	if (!mlx_data.mlx_ptr)
		free_all_exit(&mlx_data, -1);
	choose_best_resolution(&mlx_data);
	mlx_data.win_ptr = mlx_new_window(mlx_data.mlx_ptr, mlx_data.width,
			mlx_data.height, "so_long");
	if (!mlx_data.win_ptr)
		free_all_exit(&mlx_data, -1);
	mlx_key_hook(mlx_data.win_ptr, handle_key_input, &mlx_data);
	mlx_hook(mlx_data.win_ptr, 17, 0, close_window, &mlx_data);
	visualize_map(&mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
