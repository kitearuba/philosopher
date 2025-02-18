/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dimensions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 23:24:07 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/05 21:56:15 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  HANDLE INVALID LINE  :::                      */
/*                                                                            */
/*   Function: handle_invalid_line                                            */
/*   Description: Checks if a given line is empty or NULL.                    */
/*                                                                            */
/*   - Prints an error message if the line is empty or NULL.                  */
/*   - Ensures that the function does not proceed with an invalid line.       */
/*                                                                            */
/*   @param line The string to check.                                         */
/*   @return 1 if the line is valid, 0 if it is invalid.                      */
/*                                                                            */
/* ************************************************************************** */
static int	handle_invalid_line(const char *line)
{
	if (!line || !*line)
	{
		ft_printf_fd(STDERR, "Invalid input detected (empty string)\n");
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  IS VALID NUMBER  :::                          */
/*                                                                            */
/*   Function: is_valid_number                                                */
/*   Description: Determines if a given string is a valid numeric value.      */
/*                                                                            */
/*   - Checks if the first character is a digit or a minus sign.              */
/*   - Prints an error if a non-numeric character is found.                   */
/*                                                                            */
/*   @param str The string to validate.                                       */
/*   @return 1 if the string is a valid number, 0 otherwise.                  */
/*                                                                            */
/* ************************************************************************** */
static int	is_valid_number(const char *str)
{
	if (!ft_isdigit(str[0]) && str[0] != '-')
	{
		ft_printf_fd(STDERR, "Error: Non-numeric value found: %s\n", str);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  VALIDATE DIMENSIONS  :::                      */
/*                                                                            */
/*   Function: validate_dimensions                                            */
/*   Description: Ensures that a map line contains only valid numbers.        */
/*                                                                            */
/*   - Splits the line into tokens.                                           */
/*   - Validates that each token represents a number.                         */
/*   - Updates the map width if the current line has more columns.            */
/*   - Ensures proper memory cleanup in case of failure.                      */
/*                                                                            */
/*   @param line The line to validate.                                        */
/*   @param map Pointer to the map structure.                                 */
/*   @return 1 if the line is valid, 0 otherwise.                             */
/*                                                                            */
/* ************************************************************************** */
int	validate_dimensions(const char *line, t_map *map)
{
	char	**tokens;
	int		col_count;

	if (!handle_invalid_line(line))
		return (0);
	tokens = ft_split(line, ' ');
	if (!tokens)
	{
		ft_printf_fd(STDERR, "Error: ft_split failed on line: %s\n", line);
		return (0);
	}
	col_count = 0;
	while (tokens[col_count])
	{
		if (!is_valid_number(tokens[col_count]))
		{
			free_2d_array(tokens);
			return (0);
		}
		col_count++;
	}
	if (col_count > map->width)
		map->width = col_count;
	free_2d_array(tokens);
	return (1);
}
