/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/02 21:12:57 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

double	Computespecular(double intensity, t_hit_record *rec, t_ray *ray, t_ray *L)
{
	t_vec3	V;
	t_vec3	R;
	double	r_dot_v;

	V = invert(ray->dir);
	R = reflect(L->dir, rec->normal);
	r_dot_v = dot(R, V);
	if (r_dot_v > 0)
		return (intensity * pow(r_dot_v / (length(&R) * length(&V)), rec->material->specular));
	return (0);
}

double	Compute_D_L(double *intensity, t_hit_record *rec, t_ray *ray, t_ray *L)
{
	t_vec3			r_l;
	double		n_dot_l;

	r_l = minus_vec_vec(world->lights[i].position, rec->p);
	if (world->lights[i].type == POINT)
		*L = set_ray(rec->p, unit_vector(r_l));
	else if (world->lights[i].type == DIRECTIONAL)
		*L = set_ray(rec->p, invert(world->lights[i].direction));
	hit(L, world, INFINITY, &record);
	if ((record.t != INFINITY && world->lights[i].type == DIRECTIONAL)
		|| (world->lights[i].type == POINT && record.t < length(&r_l)))
		return (1);
	n_dot_l = dot(rec->normal, L.dir);
	if (n_dot_l > 0)
		*intensity += world->lights[i].intensity * n_dot_l);
	return (0)
}

double	ComputeLightning(t_world *world, t_hit_record* rec, t_ray* ray)
{
	size_t			i;
	double			intensity;
	t_hit_record	record;
	t_ray			L;


	i = 0;
	intensity = 0;
	while (i < world->n_lights)
	{
		if (world->lights[i].type == AMBIENT)
			intensity += world->lights[i].intensity;
		else
		{
			if (Compute_D_L(&intensity, rec, ray, &L))
			{
				i++;
				continue;
			}
			if (rec->material->specular != -1)
				intensity += Computespecular(world->lights[i].intensity, rec, ray, &L);
		}
		i++;
	}
	return (intensity);
}
