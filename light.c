/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 14:59:47 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

double	compute_spec(double intensity, t_hit_record *rec,
			t_ray *ray, t_ray *L)
{
	t_vec3	v;
	t_vec3	r;
	double	r_dot_v;

	v = invert(ray->dir);
	r = reflect(L->dir, rec->normal);
	r_dot_v = dot(r, v);
	if (r_dot_v > 0)
		return (intensity * pow(r_dot_v / (length(&r) * length(&v)),
				rec->material->specular));
	return (0);
}

t_color	compute_d_l(t_world *world, t_hit_record *rec, t_ray *L, t_light *light)
{
	t_vec3			r_l;
	double			n_dot_l;
	t_hit_record	record;

	r_l = minus_vec_vec(light->position, rec->p);
	if (light->type == POINT)
		*L = set_ray(rec->p, unit_vector(r_l));
	else if (light->type == DIRECTIONAL)
		*L = set_ray(rec->p, invert(light->direction));
	hit(*L, world, INFINITY, &record);
	if ((record.t != INFINITY && light->type == DIRECTIONAL)
		|| (light->type == POINT && record.t < length(&r_l)))
		return (multiply_vec_doub(light->color, 0));
	n_dot_l = dot(rec->normal, L->dir);
	if (n_dot_l > 0)
		return (multiply_vec_doub(light->color, (light->intensity * n_dot_l)));
	return (multiply_vec_doub(light->color, 0));
}

t_color	computelightning(t_world *world, t_hit_record *rec, t_ray *ray)
{
	size_t			i;
	t_color			intensity;
	t_ray			l;
	t_color			tmp_inten;

	i = -1;
	intensity = setvec(0, 0, 0);
	while (++i < world->n_lights)
	{
		if (world->lights[i].type == AMBIENT)
		{
			intensity = plus_vec_vec(intensity, \
			multiply_vec_doub(world->lights[i].color, \
			world->lights[i].intensity));
			continue ;
		}
		tmp_inten = compute_d_l(world, rec, &l, &world->lights[i]);
		if (length_squared(&tmp_inten) == 0)
			continue ;
		intensity = plus_vec_vec(intensity, tmp_inten);
		if (rec->material->specular > 0)
			intensity = plus_vec_doub(intensity, \
			compute_spec(world->lights[i].intensity, rec, ray, &l));
	}
	return (intensity);
}
