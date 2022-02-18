/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:25:10 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/18 10:41:38 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_array_length(char **array, int j, char *str)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	if (i != j)
	{
		printf("Error\n%s: Wrong number of information\n", str);
		exit(0);
	}
}

double	ft_atof(char *str)
{
	double	d;
	double	dec;
	int		place;

	dec = 0;
	place = 0;
	d = 0;
	d += ft_atoi(str);
	while (ft_isdigit(*str) || *str == '-')
		str++;
	if (!*str)
		return (d);
	str++;
	dec += ft_atoi(str);
	while (ft_isdigit(*str))
	{
		place++;
		str++;
	}
	if (d < 0)
		return (d - dec / pow(10, place));
	else
		return (d + dec / pow(10, place));
}

t_vec3	strtovec(char *str)
{
	t_vec3	vec;
	char	**data;

	data = ft_split(str, ',');
	ft_array_length(data, 3, "vec3");
	vec.v[0] = ft_atof(data[0]);
	vec.v[1] = ft_atof(data[1]);
	vec.v[2] = ft_atof(data[2]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data);
	return (vec);
}

void	color_check(t_vec3 color)
{
	if (color.col.r < 0 || color.col.r > 255
		|| color.col.g < 0 || color.col.g > 255
		|| color.col.b < 0 || color.col.b > 255)
	{
		printf("Error\ncolor: Values out of range\n");
		exit(0);
	}
	return ;
}

void	light_intensity_ceck(t_world *world)
{
	if (world->lights[world->n_lights].intensity < 0)
	{
		printf("Error\nintensity: Values out of range\n");
		exit(0);
	}
	color_check(world->lights[world->n_lights].color);
	world->r += world->lights[world->n_lights].color.col.r \
	* world->lights[world->n_lights].intensity;
	world->g += world->lights[world->n_lights].color.col.g \
	* world->lights[world->n_lights].intensity;
	world->b += world->lights[world->n_lights].color.col.b \
	* world->lights[world->n_lights].intensity;
	if (world->r > 255 || world->g > 255 || world->b > 255)
	{
		printf("Error\nintensity: Values out of range\n");
		exit(0);
	}
	return ;
}
