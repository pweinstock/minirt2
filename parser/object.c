/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:38:38 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/08 21:00:30 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	sphere(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	ft_array_length(data, 4, "sp");
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].radius = ft_atof(data[2]) / 2;
	world->hittabels[world->n_hittabels].mat.color \
	= division(strtovec(data[3]), 255);
	world->hittabels[world->n_hittabels].hit = hit_sphere;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat.specular = -1;
	world->hittabels[world->n_hittabels].mat.reflective = 0;
	world->hittabels[world->n_hittabels].mat.ir = 1.5;
	free(data);
	return (1);
}

int	plane(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	ft_array_length(data, 4, "pl");
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].orientation = strtovec(data[2]);
	world->hittabels[world->n_hittabels].mat.color \
	= division(strtovec(data[3]), 255);
	world->hittabels[world->n_hittabels].hit = hit_plane;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat.specular = -1;
	world->hittabels[world->n_hittabels].mat.reflective = 0;
	world->hittabels[world->n_hittabels].mat1.color = setvec(1,1,1);
	world->hittabels[world->n_hittabels].mat1.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat1.specular = -1;
	world->hittabels[world->n_hittabels].mat1.reflective = 0;
	world->hittabels[world->n_hittabels].mat1.ir = 1.5;
	free(data);
	return (0);
}

int	cylinder(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	ft_array_length(data, 6, "cy");
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].orientation = strtovec(data[2]);
	world->hittabels[world->n_hittabels].radius = ft_atof(data[3]) / 2;
	world->hittabels[world->n_hittabels].hight = ft_atof(data[4]);
	world->hittabels[world->n_hittabels].mat.color \
	= division(strtovec(data[5]), 255);
	world->hittabels[world->n_hittabels].hit = hit_cylinder;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	initmatrix(&world->hittabels[world->n_hittabels]);
	matrix_transponieren(&world->hittabels[world->n_hittabels]);
	world->hittabels[world->n_hittabels].mat.specular = -1;
	world->hittabels[world->n_hittabels].mat.reflective = 0;
	world->hittabels[world->n_hittabels].mat.ir = 1.5;
	if (line[1] == 'o')
	{
		world->hittabels[world->n_hittabels].hit = hit_cone;
		world->hittabels[world->n_hittabels].hight *= 2;
	}
	free(data);
	return (0);
}
