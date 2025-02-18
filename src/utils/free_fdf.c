/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:31:36 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/06 20:01:49 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  FREE FDF  :::                                 */
/*                                                                            */
/*   Function: free_fdf                                                       */
/*   Description: Frees all allocated resources within the FDF structure.     */
/*                                                                            */
/*   - Frees the parsed map data if allocated.                                */
/*   - Destroys the MiniLibX image if it exists.                              */
/*   - Destroys the MiniLibX window if it was created.                        */
/*   - Cleans up the MiniLibX display and frees the MLX instance.             */
/*   - Frees the FDF structure itself.                                        */
/*                                                                            */
/*   @param fdf Pointer to the FDF structure to be freed.                     */
/*                                                                            */
/* ************************************************************************** */
void	free_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		if (fdf->map)
			free_map(fdf->map);
		if (fdf->img.img)
			mlx_destroy_image(fdf->mlx, fdf->img.img);
		if (fdf->win)
		{
			mlx_destroy_window(fdf->mlx, fdf->win);
			fdf->win = NULL;
		}
		if (fdf->mlx)
		{
			mlx_destroy_display(fdf->mlx);
			free(fdf->mlx);
			fdf->mlx = NULL;
		}
		free(fdf);
	}
}
