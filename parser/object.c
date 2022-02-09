/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:38:38 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/09 15:12:33 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sphere(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	ft_array_length(data, 6, "sp");
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].radius = ft_atof(data[2]) / 2;
	world->hittabels[world->n_hittabels].mat.color1 \
	= division(strtovec(data[3]), 255);
	world->hittabels[world->n_hittabels].hit = hit_sphere;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat.specular = ft_atof(data[4]);
	world->hittabels[world->n_hittabels].mat.reflective = ft_atof(data[5]);
	world->hittabels[world->n_hittabels].mat.emitted = emitted_color;
	world->hittabels[world->n_hittabels].mat.ir = 1.5;
	free(data);
	return (1);
}

int	plane(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	ft_array_length(data, 8, "pl");
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].orientation = strtovec(data[2]);
	world->hittabels[world->n_hittabels].mat.color1 \
	= division(strtovec(data[3]), 255);
	world->hittabels[world->n_hittabels].hit = hit_plane;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat.specular = ft_atof(data[4]);
	world->hittabels[world->n_hittabels].mat.reflective = ft_atof(data[5]);
	if (ft_atof(data[6]))
	{
		world->hittabels[world->n_hittabels].mat.emitted = \
		emitted_checkerboard;
		world->hittabels[world->n_hittabels].mat.color2 = \
		division(strtovec(data[7]), 255);
	}
	else
		world->hittabels[world->n_hittabels].mat.emitted = emitted_color;
	free(data);
	return (0);
}

int	cylinder(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	ft_array_length(data, 8, "cy");
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].orientation = strtovec(data[2]);
	world->hittabels[world->n_hittabels].radius = ft_atof(data[3]) / 2;
	world->hittabels[world->n_hittabels].hight = ft_atof(data[4]);
	world->hittabels[world->n_hittabels].mat.color1 \
	= division(strtovec(data[5]), 255);
	world->hittabels[world->n_hittabels].hit = hit_cylinder;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	initmatrix(&world->hittabels[world->n_hittabels]);
	matrix_transponieren(&world->hittabels[world->n_hittabels]);
	world->hittabels[world->n_hittabels].mat.specular = ft_atof(data[6]);
	world->hittabels[world->n_hittabels].mat.reflective = ft_atof(data[7]);
	world->hittabels[world->n_hittabels].mat.ir = 1.5;
	world->hittabels[world->n_hittabels].mat.emitted = emitted_color;
	if (line[1] == 'o')
	{
		world->hittabels[world->n_hittabels].hit = hit_cone;
		world->hittabels[world->n_hittabels].hight *= 2;
	}
	free(data);
	return (0);
}
