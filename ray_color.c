/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 15:01:12 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

static t_vec3	ray_color_ph(t_ray r, t_world *world, int depth)
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
	local_color = multiply_vec_vec(rec.material->emitted(&rec),
			computelightning(world, &rec, &r));
	if (depth <= 0)
		return (local_color);
	if (!rec.material->scatter(r, rec, &attenuation, &scattered))
		return (local_color);
	local_color = multiply_vec_doub(local_color, 1 - rec.material->reflective);
	return (plus_vec_vec(local_color, multiply_vec_doub(
				ray_color_ph(scattered, world, depth - 1),
				rec.material->reflective)));
}

static t_color	ray_average_color(t_world *world, t_picture_part *part,
			size_t samples_per_pixel, int max_depth)
{
	t_color	color;
	size_t	i;
	t_ray	r;
	double	u;
	double	v;

	i = 0;
	color = setvec(0, 0, 0);
	while (i < samples_per_pixel)
	{
		u = (double)(part->x.current) / (part->x.to - 1);
		v = (double)(part->y.current) / (part->ges_y.to - 1);
		r = get_ray(world->cam, u, v);
		color = plus_vec_vec(color, ray_color_ph(r, world, max_depth));
		i++;
	}
	color.v[0] = sqrt(color.v[0] / samples_per_pixel);
	color.v[1] = sqrt(color.v[1] / samples_per_pixel);
	color.v[2] = sqrt(color.v[2] / samples_per_pixel);
	return (color);
}

static void	set_pixel(int *arr, int y, int x, int color)
{
	arr[y * WIDTH + x] = color;
}

void	count_pixel(t_world *w, t_picture_part *part,
			int *arr, t_data *img)
{
	t_color	col;

	part->y.current--;
	while (part->y.current >= part->y.from)
	{
		part->x.current = 0;
		while (part->x.current < part->x.to)
		{
			if (arr == NULL)
			{
				col = ray_average_color(w, part, MLX_SAMPLES_PER_PIXEL,
						MLX_MAX_DEPTH);
				my_mlx_pixel_put(img,
					part->x.current, MLX_HIGHT - 1 - part->y.current, col);
			}
			else
			{
				col = ray_average_color(w, part, SAMPLES_PER_PIXEL, MAX_DEPTH);
				set_pixel(arr, part->y.current, part->x.current,
					create_trgb(0, col));
			}
			part->x.current++;
		}
		part->y.current--;
	}
}
