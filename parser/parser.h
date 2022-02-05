/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:30:06 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 20:03:30 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdint.h>
# include <stdlib.h>
# include "../world.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

int		parser(char *file, t_world *world);
int		identifier(char *line, t_world *world);

//parser_helper
void	count_object(t_world *world, char *line);
void	count_objects(t_world *world, int fd);
t_bool	fil_world(t_world *world, int fd);
void	init_array(t_world *world);
int		is_whitespace(char c);

//parser_utils.c
void	ft_array_length(char **array, int j, char *str);
double	ft_atof(char *str);
t_vec3	strtovec(char *str);
void	color_check(t_vec3 color);
void	light_intensity_ceck(t_world *world);

//light.c
int		ambient(char *line, t_world *world);
int		light_l(char *line, t_world *world);
int		light_d(char *line, t_world *world);

//camera
int		camera(char *line, t_world *world);

//object
int		sphere(char *line, t_world *world);
int		plane(char *line, t_world *world);
int		cylinder(char *line, t_world *world);

#endif
