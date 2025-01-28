/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:31 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/25 17:41:49 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
//# include "mlx/mlx.h"

typedef struct	s_mlx_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}			t_mlx_data;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

//			map_checking
char		**load_map(int argc, char **argv);

//			input_handling
int			handle_key_input(int keysym, t_mlx_data *data);
int			close_window(t_mlx_data *data);
#endif