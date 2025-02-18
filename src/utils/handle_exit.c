/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/31 22:54:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  HANDLE EXIT  :::                              */
/*                                                                            */
/*   Function: handle_exit                                                    */
/*   Description: Cleans up all resources and safely exits the program.       */
/*                                                                            */
/*   - Calls free_fdf to release all allocated resources.                     */
/*   - Terminates the program using exit(0).                                  */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure to be freed before exiting.      */
/*   @return Always returns 0 (for compatibility with MiniLibX hooks).        */
/*                                                                            */
/* ************************************************************************** */
int	handle_exit(t_fdf *fdf)
{
	free_fdf(fdf);
	exit(0);
}
