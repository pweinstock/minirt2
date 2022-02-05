/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 19:34:53 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

t_vec3	ray_color_ph(t_ray r, t_world *world, int depth)
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
	if (!rec.material->scatter(r, rec, &attenuation, &scattered))
		return (local_color);
	local_color = multiply_vec_doub(local_color, 1 - rec.material->reflective);
	return (plus_vec_vec(local_color, multiply_vec_doub(
				ray_color_ph(scattered, world, depth - 1),
				rec.material->reflective)));
}

t_vec3	ray_color_sh(t_ray r, t_world *world, int depth)
{
	t_hit_record	rec;
	double			light;
	t_ray			scattered;
	t_vec3			attenuation;

	if (depth <= 0)
		return (setvec(1, 1, 1));
	if (!hit(r, world, INFINITY, &rec))
		return (setvec(1, 1, 1));
	light = ComputeLightning(world, &rec, &r);
	if (!rec.material->scatter(r, rec, &attenuation, &scattered))
		return (setvec(light, light, light));
	return (multiply_vec_doub(multiply_vec_vec(
				ray_color_sh(scattered, world, depth - 1),
				attenuation), light));
}

t_color	ray_average_color(t_world *world, t_camera *cam, double u, double v)
{
	t_color	color;
	size_t	i;
	t_ray	r;

	i = 0;
	color = setvec(0, 0, 0);
	while (i < SAMPLES_PER_PIXEL)
	{
		r = get_ray(*cam, u, v);
		color = plus_vec_vec(color, ray_color_ph(r, world, MAX_DEPTH));
		i++;
	}
	color.v[0] = sqrt(color.v[0] / SAMPLES_PER_PIXEL);
	color.v[1] = sqrt(color.v[1] / SAMPLES_PER_PIXEL);
	color.v[2] = sqrt(color.v[2] / SAMPLES_PER_PIXEL);
	return (color);
}

void	count_pixel(t_world *w, int hight,
			int width, int (*arr)[HIGHT][WIDTH])
{
	t_color	col;
	int		x;
	int		y;
	double	u;
	double	v;

	y = hight - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < width)
		{
			u = (double)(x + random_double()) / (width - 1);
			v = (double)(y + random_double()) / (hight - 1);
			col = ray_average_color(w, &w->cam[w->current_cam], u, v);
			if (arr == NULL)
				my_mlx_pixel_put(&w->cam[w->current_cam].img,
					 x, MLX_HIGHT - y - 1, col);
			else
				(*arr)[y][x] = create_trgb(0, col);
			x++;
		}
		y--;
	}
}

void	ft_make_mlx_imige(t_world *world)
{
	size_t	n;

	world->current_cam = 0;
	n = world->current_cam;
	world->cam[n].img.img = mlx_new_image(world->mlx, MLX_WIDTH, MLX_HIGHT);
	world->cam[n].img.addr = mlx_get_data_addr(world->cam[n].img.img,
			&world->cam[n].img.bits_per_pixel, &world->cam[n].img.line_length,
			&world->cam[n].img.endian);
	count_pixel(world, MLX_HIGHT, MLX_WIDTH, NULL);
	mlx_put_image_to_window(world->mlx, world->mlx_win,
		world->cam[n].img.img, 0, 0);
	mlx_destroy_image(world->mlx, world->cam[n].img.img);
}
