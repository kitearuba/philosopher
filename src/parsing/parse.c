/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/05 22:43:54 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  COUNT DIMENSIONS  :::                         */
/*                                                                            */
/*   Function: count_dimensions                                               */
/*   Description: Determines the width and height of the map.                 */
/*                                                                            */
/*   - Reads each line to count the number of rows (height).                  */
/*   - Calls validate_dimensions to determine the width consistency.          */
/*   - Ensures proper error handling and resource cleanup.                    */
/*                                                                            */
/*   @param filename Path to the map file.                                    */
/*   @param map Pointer to the map structure to store the dimensions.         */
/*   @return 1 if successful, 0 if an error occurs.                           */
/*                                                                            */
/* ************************************************************************** */
static int	count_dimensions(int fd, t_map *map)
{
	char	*line;

	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!validate_dimensions(line, map))
		{
			free(line);
			return (0);
		}
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  ALLOCATE ROW MEMORY  :::                      */
/*                                                                            */
/*   Function: allocate_row_memory                                            */
/*   Description: Allocates memory for a row in the map.                      */
/*                                                                            */
/*   - Allocates memory for storing height values.                            */
/*   - Allocates memory for storing color values.                             */
/*   - Ensures memory allocation was successful.                              */
/*   - Initializes height values to 0.                                        */
/*   - Frees the entire map and returns 0 in case of failure.                 */
/*                                                                            */
/*   @param map Pointer to the map structure.                                 */
/*   @param i Row index to allocate memory for.                               */
/*   @return 1 if successful, 0 if allocation fails.                          */
/*                                                                            */
/* ************************************************************************** */
static int	allocate_row_memory(t_map *map, int i)
{
	map->data[i] = (int *)malloc(map->width * sizeof(int));
	map->colors[i] = (int *)malloc(map->width * sizeof(int));
	if (!map->data[i] || !map->colors[i])
	{
		free_map(map);
		return (0);
	}
	ft_memset(map->data[i], 0, map->width * sizeof(int));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  ALLOCATE MAP MEMORY  :::                      */
/*                                                                            */
/*   Function: allocate_map_memory                                            */
/*   Description: Allocates memory for the entire map structure.              */
/*                                                                            */
/*   - Allocates memory for the row pointers of height and color data.        */
/*   - Iterates over each row and allocates memory using allocate_row_memory. */
/*   - Ensures proper cleanup in case of allocation failure.                  */
/*                                                                            */
/*   @param map Pointer to the map structure.                                 */
/*   @return 1 if successful, 0 if allocation fails.                          */
/*                                                                            */
/* ************************************************************************** */
static int	allocate_map_memory(t_map *map)
{
	int	i;

	map->data = (int **)malloc(map->height * sizeof(int *));
	map->colors = (int **)malloc(map->height * sizeof(int *));
	if (!map->data || !map->colors)
	{
		free_map(map);
		return (0);
	}
	i = 0;
	while (i < map->height)
	{
		if (!allocate_row_memory(map, i))
		{
			free_map(map);
			return (0);
		}
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  PARSE VALUES  :::                             */
/*                                                                            */
/*   Function: parse_values                                                   */
/*   Description: Parses numerical values and colors from the file.           */
/*                                                                            */
/*   - Iterates through the rows, extracting numerical height and color data. */
/*   - Ensures memory cleanup in case of failure.                             */
/*                                                                            */
/*   @param filename Path to the map file.                                    */
/*   @param map Pointer to the map structure to store parsed values.          */
/*   @return 1 if successful, 0 if parsing fails.                             */
/*                                                                            */
/* ************************************************************************** */
static int	parse_values(int fd, t_map *map)
{
	int	row;

	row = 0;
	if (!parse_rows(fd, map, &row))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  PARSE MAP  :::                                */
/*                                                                            */
/*   File: parse_map.c                                                        */
/*   Description: Reads and processes the map file to store its data.         */
/*                                                                            */
/*   - Counts the dimensions (width and height) of the map.                   */
/*   - Allocates memory for storing map data and colors.                      */
/*   - Parses the file and extracts numerical values and colors.              */
/*   - Ensures proper cleanup in case of failure.                             */
/*                                                                            */
/*   @param filename Path to the map file.                                    */
/*   @param map Pointer to the map structure to store the data.               */
/*   @return 1 if successful, 0 if an error occurs.                           */
/*                                                                            */
/* ************************************************************************** */
int	parse_map(const char *filename, t_map *map)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			parse_error("Error: File does not exist\n", fd, map);
		else if (errno == EACCES)
			parse_error("Error: Permission denied\n", fd, map);
		else
			parse_error(strerror(errno), fd, map);
	}
	if (!count_dimensions(fd, map))
		parse_error("Error: Failed to count map dimensions\n", fd, map);
	close(fd);
	if (!allocate_map_memory(map))
		parse_error("Error: Memory allocation failed\n", fd, map);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		parse_error("Error: Failed to reopen file\n", fd, map);
	if (!parse_values(fd, map))
		parse_error("Error: Failed to parse map values\n", fd, map);
	close(fd);
	return (1);
}
