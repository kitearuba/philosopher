/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrrodri <chrrodri@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:25:01 by chrrodri          #+#    #+#             */
/*   Updated: 2025/02/06 19:39:58 by chrrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* ************************************************************************** */
/*                               Includes                                     */
/* ************************************************************************** */

# include <unistd.h>
# include <fcntl.h> // For open()
# include <stdlib.h> // For exit() and abs()
# include <math.h>
# include <errno.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/include/libft.h"
# include "fdf_structs.h"
# include "fdf_macros.h"

/* ************************************************************************** */
/*                          Parsing & Validation                              */
/* ************************************************************************** */

int			parse_map(const char *filename, t_map *map);
int			validate_dimensions(const char *line, t_map *map);
int			parse_rows(int fd, t_map *map, int *row);
int			parse_strict_atoi(const char *str, char **args);

/* ************************************************************************** */
/*                          Error Handling                                    */
/* ************************************************************************** */

void		free_on_error(t_fdf *fdf, const char *error_message);
void		fatal_error(const char *msg);
void		parse_error(char *str, int fd, t_map *map);

/* ************************************************************************** */
/*                          Initialization                                    */
/* ************************************************************************** */

t_fdf		*init_fdf(t_map *map);
void		set_window_size(t_fdf *fdf);

/* ************************************************************************** */
/*                          Rendering & Projection                            */
/* ************************************************************************** */

void		render_fdf(t_fdf *fdf);
void		find_min_max_z(t_fdf *fdf);
t_point		apply_isometric(t_fdf *fdf, t_point p);
t_point		apply_parallel(t_fdf *fdf, int x, int y, int z);

/* ************************************************************************** */
/*                          Line Drawing                                      */
/* ************************************************************************** */

void		draw_line(t_fdf *fdf, t_point p1, t_point p2);
void		draw_thick_line(t_fdf *fdf, t_point p1, t_point p2);
void		bresenham_draw(t_fdf *fdf, t_point p1, t_point p2, t_line *line);

/* ************************************************************************** */
/*                          Color Handling                                    */
/* ************************************************************************** */

int			get_color(t_fdf *fdf, int z);
float		clamp_ratio(float ratio);
int			interpolate_color(int low_color, int high_color, float ratio);

/* ************************************************************************** */
/*                          Event Handling                                    */
/* ************************************************************************** */

int			handle_key_press(int key, t_fdf *fdf);
int			handle_key_release(int key, t_fdf *fdf);
int			update_frame(t_fdf *fdf);
int			handle_exit(t_fdf *fdf);

/* ************************************************************************** */
/*                          Memory Management                                 */
/* ************************************************************************** */

void		free_map(t_map *map);
void		free_fdf(t_fdf *fdf);
void		free_2d_array(char **arr);

#endif /* FDF_H */
