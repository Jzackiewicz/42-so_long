/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:31 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 16:47:03 by jzackiew         ###   ########.fr       */
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
}			t_map_data;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	void	**images;
	int		img_side_len;
}			t_mlx_data;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

//			map_checking
char		**load_map(int argc, char **argv);

//			input_handling
int			handle_key_input(int keysym, t_mlx_data *data);
int			close_window(t_mlx_data *data);

//			map_loading
char		**load_map(int argc, char **argv);

//			map_checking
void		check_map(char **map);

//			map_checking_utils
int			check_occurrences(char **map, char c);
t_map_data	init_map_data(char **map);
void		check_near_nodes(t_map_data map_data);

//			utils
void		free_map(char **map);
void		print_map(char **map);
void		free_all_images(t_mlx_data *mlx_data);
#endif