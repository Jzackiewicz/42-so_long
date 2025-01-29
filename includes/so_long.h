/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:31 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 17:09:02 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_map_data
{
	char	**map;
	int		cur_x;
	int		cur_y;
	int		collectible_count;
	int		moves_count;
}			t_map_data;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map_data	map_data;
	void		**images;
	int			img_side_len;
	int			height;
	int			width;
	char		*textures_subdir;
}			t_mlx_data;

//			map_checking
void		check_map(t_map_data map_data);

//			input_handling
int			handle_key_input(int keysym, t_mlx_data *data);
int			close_window(t_mlx_data *data);

//			map_loading
void		load_map(int argc, char **argv, t_mlx_data *mlx_data);

//			map_checking_utils
int			check_occurrences(char **map, char c);
t_map_data	init_map_data(char **map);
void		check_near_nodes(t_map_data map_data);

//			graphics
void		choose_best_resolution(t_mlx_data *mlx_data);
void		visualize_map(t_mlx_data *mlx_data);

//			moving_character
void		move_in_direction(t_mlx_data *mlx_data, char *direction);

//			utils
void		free_map(char **map);
void		free_all_images(t_mlx_data *mlx_data);
void		free_all_stuff(t_mlx_data *mlx_data);
void		free_all_exit(t_mlx_data *mlx_data, int err_id);
#endif