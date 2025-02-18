/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:52:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/05 22:42:24 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  FILL MAP VALUES  :::                          */
/*                                                                            */
/*   Function: fill_map_values                                                */
/*   Description: Extracts and assigns height and color values for a cell.    */
/*                                                                            */
/*   - Converts the first token into an integer and stores it in map->data.   */
/*   - If a second token exists, it is interpreted as a hexadecimal color.    */
/*   - If no color is provided, assigns a default color.                      */
/*                                                                            */
/*   @param split_value The array of tokens (height and optional color).      */
/*   @param map Pointer to the map structure.                                 */
/*   @param row The current row index in the map.                             */
/*   @param col The current column index in the map.                          */
/*                                                                            */
/* ************************************************************************** */
static void	fill_map_values(char **split_value, t_map *map, int row, int col)
{
	if (split_value[0])
		map->data[row][col] = parse_strict_atoi(split_value[0], split_value);
	if (split_value[1])
		map->colors[row][col] = (int)ft_strtol(split_value[1], NULL, 16);
	else
		map->colors[row][col] = DEFAULT_COLOR;
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  PROCESS TOKENS  :::                           */
/*                                                                            */
/*   Function: process_tokens                                                 */
/*   Description: Processes individual tokens from a line and fills the map.  */
/*                                                                            */
/*   - Trims whitespace and newlines from tokens.                            */
/*   - Splits each token into height and optional color components.           */
/*   - Calls fill_map_values to store the extracted values.                   */
/*   - Frees allocated memory after processing each token.                    */
/*   - Fills remaining columns with default values if the row is shorter.     */
/*                                                                            */
/*   @param tokens Array of strings representing the parsed line.             */
/*   @param map Pointer to the map structure.                                 */
/*   @param row The row index being processed.                                */
/*   @return 1 if successful, 0 if an error occurs.                           */
/*                                                                            */
/* ************************************************************************** */
static int	process_tokens(char **tokens, t_map *map, int row)
{
	int		col;
	char	*trimmed;
	char	**split_value;

	col = 0;
	while (tokens[col] && col < map->width)
	{
		trimmed = ft_strtrim(tokens[col], "\n");
		split_value = ft_split(trimmed, ',');
		free(trimmed);
		fill_map_values(split_value, map, row, col);
		free_2d_array(split_value);
		col++;
	}
	while (col < map->width)
	{
		map->data[row][col] = 0;
		map->colors[row][col] = DEFAULT_COLOR;
		col++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  PARSE ROWS  :::                               */
/*                                                                            */
/*   Function: parse_rows                                                     */
/*   Description: Reads and processes each line from the file.                */
/*                                                                            */
/*   - Reads each line using get_next_line.                                   */
/*   - Splits the line into individual tokens (numbers and colors).           */
/*   - Calls process_tokens to extract and store height/color values.         */
/*   - Manages memory cleanup for each line and token array.                  */
/*                                                                            */
/*   @param fd File descriptor of the opened map file.                        */
/*   @param map Pointer to the map structure storing parsed values.           */
/*   @param row Pointer to the row index being processed.                     */
/*   @return 1 if successful, 0 if an error occurs.                           */
/*                                                                            */
/* ************************************************************************** */
int	parse_rows(int fd, t_map *map, int *row)
{
	char	*line;
	char	**tokens;
	int		success;

	line = get_next_line(fd);
	while (line)
	{
		tokens = ft_split(line, ' ');
		free(line);
		if (!tokens)
			return (0);
		success = process_tokens(tokens, map, *row);
		free_2d_array(tokens);
		if (!success)
			return (0);
		(*row)++;
		line = get_next_line(fd);
	}
	return (1);
}
