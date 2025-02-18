/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:29:05 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 21:53:20 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  FATAL ERROR  :::                              */
/*                                                                            */
/*   File: fatal_error.c                                                      */
/*   Description: Displays an error message and exits the program.            */
/*                                                                            */
/*   - Prints the provided error message to STDERR.                           */
/*   - Appends a newline character for proper formatting.                     */
/*   - Exits the program with a failure status.                               */
/*                                                                            */
/* ************************************************************************** */
void	fatal_error(const char *msg)
{
	ft_printf_fd(STDERR, "%s\n", msg);
	exit(EXIT_FAILURE);
}
