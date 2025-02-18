/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 21:54:02 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  FREE ON ERROR  :::                            */
/*                                                                            */
/*   Function: free_on_error                                                  */
/*   Description: Cleans up memory and exits on fatal error.                  */
/*                                                                            */
/*   - Uses free_fdf to clean all allocated structures.                       */
/*   - Calls fatal_error to display an error message and terminate.           */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure.                                 */
/*   @param error_message Error message to be displayed.                      */
/*                                                                            */
/* ************************************************************************** */

void	free_on_error(t_fdf *fdf, const char *error_message)
{
	free_fdf(fdf);
	fatal_error(error_message);
}
