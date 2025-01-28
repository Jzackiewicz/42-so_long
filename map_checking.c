/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:30:35 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/25 18:14:55 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	print_map(char **map)
{
	int i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			ft_printf("|%c|", map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new;

	if (!ptr)
	{
		new = malloc(new_size);
		if (!new)
			return (NULL);
	}
	else
	{
		if (old_size < new_size)
		{
			new = malloc(new_size);
			if (!new)
				return (NULL);
			ft_memcpy(new, ptr, old_size);
		}
		else
			new = ptr;
		free(ptr);
	}
	return (new);
}

int	get_fd(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_printf("Error! \n./so_long <map_dir>\n");
		exit(-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Map <%s> can't be found!\n", argv[1]);
		exit(-1);
	}
	return (fd);
}

char	**load_map(int argc, char **argv)
{
	char	*line;
	char	**map;
	int		fd;
	size_t	i;

	map = NULL;
	i = 0;
	fd = get_fd(argc, argv);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = ft_realloc(map, i * sizeof(char *), (i + 1) * sizeof(char *));
		map[i] = line;
		if(map[i][ft_strlen(map[i])-1] == '\n')
			map[i][ft_strlen(map[i])-1] = 0;
		i++;
	}
	map = ft_realloc(map, i * sizeof(char *), (i + 1) * sizeof(char *));
	map[i] = NULL;
	close(fd);
	return (map);
}

int	ft_2d_strlen(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		i++;
	return(i);
}

int is_rectangular(char **map)
{
	int 	i;
	size_t	line_len;

	i = 0;
	line_len = ft_strlen(map[i]);
	while(map[i])
	{
		if (ft_strlen(map[i]) != line_len)
			return (0);
		i++;
	}
	return (1);
}

int check_occurrences(char **map, char c)
{
	int		i;
	int		j;
	int 	occurrences;

	i = 0;
	occurrences = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == c)
				occurrences++;
			j++;
		}
		i++;
	}
	return (occurrences);
}

int is_content_valid(char **map)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while(map[i][++j])
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

int is_closed(char **map)
{
	int i;
	int j;
	int last_row;
	int	last_col;

	last_row = ft_2d_strlen(map) - 1;
	last_col = ft_strlen(map[0]) - 1;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[0][j] != '1' || map [i][0] != '1' || map[last_row][j] != '1' || map[i][last_col] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_2d_strdup(char **arr)
{
	int i;
	int arr_len;
	char **new_arr;

	if (!arr)
		return(NULL);
	arr_len = ft_2d_strlen(arr);
	i = 0;
	new_arr = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!new_arr)
		return(NULL);
	while(arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = 0;
	return (new_arr);
}

typedef struct s_map_data
{
	char **map;
	int x;
	int y;
}				t_map_data;

t_map_data get_starting_point(char **map)
{
	int i;
	int j;
	t_map_data point;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				point.x = i;
				point.y = j;
				break;
			}
			j++;
		}
		if (map[i][j] == 'P')
			break;
		i++;
	}
	return (point);
}

void	check_near_nodes(t_map_data map_data)
{
	map_data.map[map_data.x][map_data.y] = '1';
	if (map_data.map[map_data.x + 1][map_data.y] != '1')
	{
		map_data.x++;
		check_near_nodes(map_data);
	}
	if (map_data.map[map_data.x][map_data.y + 1] != '1')
	{
		map_data.y++;
		check_near_nodes(map_data);
	}
	if (map_data.map[map_data.x - 1][map_data.y] != '1')
	{
		map_data.x--;
		check_near_nodes(map_data);
	}
	if (map_data.map[map_data.x][map_data.y - 1] != '1')
	{
		map_data.y--;
		check_near_nodes(map_data);
	}
}

int is_path_valid(char **map)
{
	t_map_data val_map_data;

	if (!map)
		return (-1);
	val_map_data = get_starting_point(map);
	val_map_data.map = ft_2d_strdup(map);
	check_near_nodes(val_map_data);
	if (check_occurrences(val_map_data.map, 'E') > 0 || check_occurrences(val_map_data.map, 'P') > 0 || check_occurrences(val_map_data.map, 'C') > 0)
	{
		free_map(val_map_data.map);
		return (0);
	}
	free_map(val_map_data.map);
	return (1);
}

//int check_map(char **map)
//{
//	if (is_rectangular(map) && is_content_valid(map) && is_closed(map) && is_path_valid(map))
//		return (1);
//	else
//		return (0);
//}

int main(int argc, char **argv)
{
	char	**test_map;

	test_map = load_map(argc, argv);
	if (!is_rectangular(test_map) || !is_content_valid(test_map) || !is_closed(test_map) || !is_path_valid(test_map))
	{
		ft_printf("ERROR\n");
		free_map(test_map);
		return(-1);
	}
	print_map(test_map);
	free_map(test_map);
    return (0);
}