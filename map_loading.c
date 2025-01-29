/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:21:08 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/29 14:02:34 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

static int	get_fd(int argc, char **argv)
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

void	load_map(int argc, char **argv, t_mlx_data *mlx_data)
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
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = 0;
		i++;
	}
	map = ft_realloc(map, i * sizeof(char *), (i + 1) * sizeof(char *));
	map[i] = NULL;
	close(fd);
	mlx_data->map_data = init_map_data(map);
	free_map(map);
}
