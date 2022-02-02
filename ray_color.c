/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/02 20:40:55 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

t_vec3	ray_color(t_ray r, t_world *world, int depth)
{
	t_hit_record	rec;
	t_color			local_color;
	t_color			reflected_color;
	t_ray			scattered;
	t_vec3			attenuation;

	reflected_color = setvec(0, 0, 0);
	local_color = setvec(0, 0, 0);
	if (!hit(r, world, INFINITY, &rec))
		return (world->backround);
	local_color = multiply_vec_doub(rec.material->color,
			ComputeLightning(world, &rec, &r));
	if (depth <= 0)
		return (local_color);
	local_color = multiply_vec_doub(local_color, 1 - rec.material->reflective);
	if (!rec.material->scatter(r, rec, &attenuation, &scattered))
		return (local_color);
	return (plus_vec_vec(local_color, multiply_vec_doub(
				ray_color(scattered, world, depth - 1),
				rec.material->reflective)));
}

void	ray_average_color(t_world *world, t_camera *cam, int x, int y)
{
	t_color	color;
	size_t	i;
	double	u;
	double	v;
	t_ray	r;

	i = 0;
	color = setvec(0, 0, 0);
	while (i < SAMPLES_PER_PIXEL)
	{
		u = (double)(x + random_double()) / (WIDTH - 1);
		v = (double)(y + random_double()) / (HIGHT - 1);
		r = get_ray(*world->cam, u, v);
		color = plus_vec_vec(color, ray_color(r, world, MAX_DEPTH));
		i++;
	}
	color.v[0] = sqrt(color.v[0] / SAMPLES_PER_PIXEL);
	color.v[1] = sqrt(color.v[1] / SAMPLES_PER_PIXEL);
	color.v[2] = sqrt(color.v[2] / SAMPLES_PER_PIXEL);
	write_color(color, cam->fd);
	// my_mlx_pixel_put(&cam->img, x, HIGHT - y, color);
}
