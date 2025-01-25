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
		i++;
	}
	map = ft_realloc(map, i * sizeof(char *), (i + 1) * sizeof(char *));
	map[i] = NULL;
	close(fd);
	return (map);
}

