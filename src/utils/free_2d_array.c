/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:06:54 by chrrodri          #+#    #+#             */
/*   Updated: 2025/01/18 12:08:55 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                         :::  FREE 2D ARRAY  :::                            */
/*                                                                            */
/*   Function: free_2d_array                                                  */
/*   Description: Frees a dynamically allocated 2D array of strings.          */
/*                                                                            */
/*   - Iterates through each element of the array and frees each string.      */
/*   - Frees the array itself after all elements are released.                */
/*   - Ensures no memory leaks by setting freed pointers to NULL.             */
/*                                                                            */
/*   @param arr Pointer to the 2D array to be freed.                          */
/*                                                                            */
/* ************************************************************************** */
void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
