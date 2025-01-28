/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:30:35 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/28 14:39:55 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(char **map)
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

int	is_content_valid(char **map)
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

int	is_closed(char **map)
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

int	is_path_valid(char **map)
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

void	check_map(char **map)
{
	if (!is_rectangular(map) || !is_content_valid(map) || !is_closed(map)
		|| !is_path_valid(map))
	{
		ft_printf("ERROR\n Invalid map!\n");
		exit(-1);
	}
}

/* int main(int argc, char **argv)
{
	char	**test_map;

	test_map = load_map(argc, argv);
	if (!is_rectangular(test_map) || !is_content_valid(test_map)
		|| !is_closed(test_map) || !is_path_valid(test_map))
	{
		ft_printf("ERROR\n");
		free_map(test_map);
		return(-1);
	}
	print_map(test_map);
	free_map(test_map);
	return (0);
} */