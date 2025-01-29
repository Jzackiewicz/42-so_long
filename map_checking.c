/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:30:35 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 18:28:55 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	is_rectangular(char **map)
{
	int		i;
	size_t	line_len;

	i = 0;
	line_len = ft_strlen(map[i]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != line_len)
			return (0);
		i++;
	}
	return (1);
}

static int	is_content_valid(char **map)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			c = map[i][j];
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
				return (0);
		}
	}
	if (check_occurrences(map, 'E') != 1)
		return (0);
	if (check_occurrences(map, 'P') != 1)
		return (0);
	if (check_occurrences(map, 'C') < 1)
		return (0);
	return (1);
}

static int	is_closed(char **map)
{
	int	i;
	int	j;
	int	last_row;
	int	last_col;

	last_row = ft_2d_strlen(map) - 1;
	last_col = ft_strlen(map[0]) - 1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[0][j] != '1' || map[i][0] != '1' || map[last_row][j] != '1'
				|| map[i][last_col] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_path_valid(char **map)
{
	t_map_data	val_map_data;

	if (!map)
		return (-1);
	val_map_data = init_map_data(map);
	check_near_nodes(val_map_data);
	if (check_occurrences(val_map_data.map, 'E') > 0
		|| check_occurrences(val_map_data.map, 'P') > 0
		|| check_occurrences(val_map_data.map, 'C') > 0)
	{
		free_map(val_map_data.map);
		return (0);
	}
	free_map(val_map_data.map);
	return (1);
}

void	check_map(t_map_data map_data)
{
	if (!is_rectangular(map_data.map))
	{
		ft_printf("ERROR\n Provided map is not rectangular!\n");
	}
	else if (!is_content_valid(map_data.map))
	{
		ft_printf("ERROR\n Provided map has forbidden characters!\n");
	}
	else if (!is_closed(map_data.map))
	{
		ft_printf("ERROR\n Provided map is not surrounded by walls!\n");
	}
	else if (!is_path_valid(map_data.map))
	{
		ft_printf("ERROR\n Valid path on provided map cannot be found!\n");
		exit(-1);
	}
}
