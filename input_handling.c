/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:47:01 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 13:02:12 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"
#include <X11/keysym.h>

int	handle_key_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
	{
		free_all_stuff(data);
		exit(1);
	}
	if (keysym == 119)
		move_in_direction(data, "up");
	if (keysym == 115)
		move_in_direction(data, "down");
	if (keysym == 97)
		move_in_direction(data, "left");
	if (keysym == 100)
		move_in_direction(data, "right");
	return (0);
}

int	close_window(t_mlx_data *data)
{
	free_all_stuff(data);
	exit(1);
	return (0);
}
