/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzackiew <jzackiew@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:32:57 by jzackiew          #+#    #+#             */
/*   Updated: 2025/01/25 16:54:49 by jzackiew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_in_string(char *str, char x)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (x == str[i])
			return (1);
		i++;
	}
	return (0);
}
