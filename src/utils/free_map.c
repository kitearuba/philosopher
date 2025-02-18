/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/06 20:29:30 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  FREE MAP  :::                                 */
/*                                                                            */
/*   Function: free_map                                                       */
/*   Description: Frees all allocated memory for the map & colors structure.  */
/*                                                                            */
/*   - Iterates through the 2D data array and frees each row.                 */
/*   - Frees the map's and colors's data array.                               */
/*   - Resets the map dimensions to prevent accidental access.                */
/*                                                                            */
/* ************************************************************************** */
static void	free_map_data(t_map *map)
{
	int	i;

	if (!map || !map->data)
		return ;
	if (map->data)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->data[i]);
			i++;
		}
		free(map->data);
		map->data = NULL;
	}
}

static void	free_map_colors(t_map *map)
{
	int	i;

	if (!map || !map->colors)
		return ;
	if (map->colors)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->colors[i]);
			i++;
		}
		free(map->colors);
		map->colors = NULL;
	}
}

void	free_map(t_map *map)
{
	free_map_data(map);
	free_map_colors(map);
	map->height = 0;
	map->width = 0;
}
