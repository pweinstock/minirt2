/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:29:15 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/09 14:29:11 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ambient(char *line, t_world *world)
{
	char	**data;

	if (world->A_flag == TRUE)
	{
		printf("Error\nAmbient lighting already exists\n");
		exit(0);
	}
	data = ft_split_space(line);
	ft_array_length(data, 3, "A");
	world->lights[world->n_lights].intensity = ft_atof(data[1]);
	world->lights[world->n_lights].color = division(strtovec(data[2]), 255);
	world->lights[world->n_lights].type = AMBIENT;
	light_intensity_ceck(world);
	free(data);
	return (0);
}

int	light_l(char *line, t_world *world)
{
	char	**data;

	if (world->L_flag == TRUE)
	{
		printf("Error\nlighting already exists\n");
		exit(0);
	}
	data = ft_split_space(line);
	ft_array_length(data, 4, "L");
	world->lights[world->n_lights].position = strtovec(data[1]);
	world->lights[world->n_lights].intensity = ft_atof(data[2]);
	world->lights[world->n_lights].color = division(strtovec(data[3]), 255);
	world->lights[world->n_lights].type = POINT;
	light_intensity_ceck(world);
	free(data);
	return (0);
}

int	light_d(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	ft_array_length(data, 5, "D");
	world->lights[world->n_lights].direction = strtovec(data[1]);
	world->lights[world->n_lights].intensity = ft_atof(data[2]);
	world->lights[world->n_lights].color = division(strtovec(data[3]), 255);
	world->lights[world->n_lights].type = DIRECTIONAL;
	light_intensity_ceck(world);
	free(data);
	return (0);
}
