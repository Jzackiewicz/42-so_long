/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:25:17 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 15:18:22 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	check_occurrences(char **map, char c)
{
	int	i;
	int	j;
	int	occurrences;

	i = 0;
	occurrences = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				occurrences++;
			j++;
		}
		i++;
	}
	return (occurrences);
}

t_map_data	init_map_data(char **map)
{
	int			i;
	int			j;
	t_map_data	map_data;

	map_data.map = ft_2d_strdup(map);
	map_data.collectible_count = check_occurrences(map_data.map, 'C');
	map_data.moves_count = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'P')
			{
				map_data.cur_x = j;
				map_data.cur_y = i;
				break ;
			}
		}
		if (map[i][j] == 'P')
			break ;
	}
	return (map_data);
}

void	check_near_nodes(t_map_data map_data)
{
	map_data.map[map_data.cur_x][map_data.cur_y] = '1';
	if (map_data.map[map_data.cur_x + 1][map_data.cur_y] != '1')
	{
		map_data.cur_x++;
		check_near_nodes(map_data);
	}
	if (map_data.map[map_data.cur_x][map_data.cur_y + 1] != '1')
	{
		map_data.cur_y++;
		check_near_nodes(map_data);
	}
	if (map_data.map[map_data.cur_x - 1][map_data.cur_y] != '1')
	{
		map_data.cur_x--;
		check_near_nodes(map_data);
	}
	if (map_data.map[map_data.cur_x][map_data.cur_y - 1] != '1')
	{
		map_data.cur_y--;
		check_near_nodes(map_data);
	}
}
