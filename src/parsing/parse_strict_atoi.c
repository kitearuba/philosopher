/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strict_atoi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:07:41 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:00:17 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  SKIP WHITESPACE  :::                          */
/*                                                                            */
/*   Function: skip_whitespace                                                */
/*   Description: Skips leading whitespace characters in a string.            */
/*                                                                            */
/*   - Advances the pointer past spaces, tabs, newlines, and other spaces.    */
/*   - Modifies the pointer to the first non-whitespace character.            */
/*                                                                            */
/* ************************************************************************** */
static void	skip_whitespace(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\f'
		|| **str == '\v' || **str == '\r')
		(*str)++;
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  IS VALID NUMBER  :::                          */
/*                                                                            */
/*   Function: is_valid_number                                                */
/*   Description: Checks if a given string represents a valid number.         */
/*                                                                            */
/*   - Ensures the string is not NULL or empty.                               */
/*   - Verifies that all characters are digits.                               */
/*                                                                            */
/*   @param str The string to validate.                                       */
/*   @return 1 if the string is a valid number, 0 otherwise.                  */
/*                                                                            */
/* ************************************************************************** */
static int	is_valid_number(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  HANDLE SIGN  :::                              */
/*                                                                            */
/*   Function: handle_sign                                                    */
/*   Description: Determines the sign of a number from a string.              */
/*                                                                            */
/*   - Checks for leading '+' or '-' sign.                                    */
/*   - Returns 1 for positive numbers, -1 for negative numbers.               */
/*   - Advances the string pointer past the sign if present.                  */
/*                                                                            */
/*   @param str Pointer to the string to check.                               */
/*   @return The sign of the number (1 or -1).                                */
/*                                                                            */
/* ************************************************************************** */
static int	handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  HANDLE ERROR AND FREE  :::                    */
/*                                                                            */
/*   Function: handle_error_and_free                                          */
/*   Description: Frees allocated memory and prints an error message.         */
/*                                                                            */
/*   - Frees a dynamically allocated 2D array of strings.                     */
/*   - Prints an error message and terminates the program.                    */
/*                                                                            */
/*   @param msg The error message to display.                                 */
/*   @param args The 2D array to be freed before exiting.                     */
/*                                                                            */
/* ************************************************************************** */
static void	handle_error_and_free(char *msg, char **args)
{
	free_2d_array(args);
	fatal_error(msg);
}

/* ************************************************************************** */
/*                                                                            */
/*                         :::  PARSE STRICT ATOI  :::                        */
/*                                                                            */
/*   Function: parse_strict_atoi                                              */
/*   Description: Converts a string to an integer with strict validation.     */
/*                                                                            */
/*   - Skips leading whitespace characters.                                   */
/*   - Determines and applies the sign of the number.                         */
/*   - Ensures the string contains only valid digits.                         */
/*   - Detects integer overflows and underflows.                              */
/*   - Calls handle_error_and_free on invalid input or out-of-range values.   */
/*                                                                            */
/*   @param str The string to convert.                                        */
/*   @param args The 2D array to free in case of an error.                    */
/*   @return The converted integer value.                                     */
/*                                                                            */
/* ************************************************************************** */
int	parse_strict_atoi(const char *str, char **args)
{
	long long	result;
	int			sign;

	result = 0;
	if (!str || !*str)
		handle_error_and_free("Invalid input detected (empty string)", args);
	skip_whitespace(&str);
	sign = handle_sign(&str);
	if (!is_valid_number(str))
		handle_error_and_free("Invalid input detected (invalid number)", args);
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if ((sign * result) > MAX_INT || (sign * result) < MIN_INT)
			handle_error_and_free
				("Invalid input detected (out of range)", args);
		str++;
	}
	return ((int)(sign * result));
}
