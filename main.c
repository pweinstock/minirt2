/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/14 21:49:09 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"

void ft_readinput(t_world* world)
{
	int i;
	int	j;
	int ball;
	// double choose_mat;
	// t_vec3 center;
	ball = 0;

	world->hittabels = (t_object *)malloc(sizeof(t_object) * 22 * 22 +1);
	i = -11;
	j = -11;

	world->hittabels[ball].mat.scatter = scatter_lambertian;
	world->hittabels[ball].mat.albedo = setvec(1, 0.1, 0.1);
	world->hittabels[ball].hit = hit_plane;
	world->hittabels[ball].center = setvec(0, 0, 0);
	world->hittabels[ball].orientation = setvec(1,1,1);
	world->hittabels[ball].radius = 10;
	ball++;
	// while (i < 11)
	// {
	// 	j = -11;
	// 	while (j < 11)
	// 	{
	// 		choose_mat = random_double();
	// 		center = setvec(i + 0.9 * random_double(), 0.2, j+ 0.9 * random_double());
	// 		t_vec3 tmp;
	// 		tmp = minus_vec_vec(center, setvec(4, 0.2, 0));
	// 		if(length(&tmp) > 0.9)
	// 		{
	// 			world->hittabels[ball].radius = 0.2;
	// 			world->hittabels[ball].center = center;
	// 			world->hittabels[ball].hit = hit_sphere;
	// 			if(choose_mat < 0.8)
	// 			{
	// 				world->hittabels[ball].mat.scatter = scatter_lambertian;
	// 				world->hittabels[ball].mat.albedo = random_vec3(0.1, 0.9);
	// 			}
	// 			else if (choose_mat < 0.95)
	// 			{
	// 				world->hittabels[ball].mat.scatter = scatter_metal;
	// 				world->hittabels[ball].mat.albedo = random_vec3(0.5, 1);
	// 				world->hittabels[ball].mat.fuzz = random_doublem(0, 0.5);
	// 			}
	// 			else
	// 			{
	// 				world->hittabels[ball].mat.scatter = scatter_dielectric;
	// 				world->hittabels[ball].mat.ir = 1.5;
	// 			}
	// 			ball++;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }

	// world->hittabels[ball].radius = 1.0;
	// world->hittabels[ball].hit = hit_sphere;
	// world->hittabels[ball].mat.scatter = scatter_dielectric;
	// world->hittabels[ball].mat.ir = 1.5;
	// world->hittabels[ball].center = setvec(0, 1, 0);
	// ball++;
	world->hittabels[ball].radius = 1;
	world->hittabels[ball].hit = hit_sphere;
	world->hittabels[ball].mat.scatter = scatter_lambertian;
	world->hittabels[ball].mat.albedo = setvec(0.4, 0.2, 0.1);
	world->hittabels[ball].center = setvec(0, 0, 0);
	ball++;
	// world->hittabels[ball].radius = 1;
	// world->hittabels[ball].hit = hit_sphere;
	// world->hittabels[ball].mat.scatter = scatter_metal;
	// world->hittabels[ball].mat.albedo = random_vec3(0.5, 1);
	// world->hittabels[ball].mat.fuzz = 0.1;
	// world->hittabels[ball].center = setvec(4, 1, 0);
	// ball++;

	world->n_hittabels = ball;
	world->cam = set_cam(setvec(0, 0, 10),setvec(0, 0,-1) , 40);
}

void transphere(t_hit_record* rec, t_hit_record* tmp)
{
	rec->p = tmp->p;
	rec->normal = tmp->normal;
	rec->material = tmp->material;
	rec->t = tmp->t;
	rec->front_face = tmp->front_face;
}

// bool compare(t_vec3 v, t_vec3 u)
// {
// 	if(v.v[0] == u.v[0] && v.v[1] == u.v[1] && v.v[2] == u.v[2])
// 		return TRUE;
// 	return FALSE;
// }

bool hit(t_ray r, t_world *world, double t_min, double t_max, t_hit_record* rec)
{
	size_t	i;
	t_hit_record temp_rec;
	bool hit_anything = FALSE;
	double closest_so_far;
	closest_so_far = t_max;

	i = 0;

	while (i < world->n_hittabels)
	{
		if(world->hittabels[i].hit(r, &world->hittabels[i], t_min, closest_so_far, &temp_rec))
		{
			hit_anything = TRUE;
			closest_so_far = temp_rec.t;
			transphere(rec, &temp_rec);
		}
		i++;
	}
	return hit_anything;
}

t_vec3 ray_color(t_ray r, t_world *world, int depth)
{
	t_hit_record rec;


	if (depth <= 0)
		return setvec(0,0,0);

	if(hit(r ,world, 0.001, INFINITY, &rec))
	{
		t_ray scattered;
		t_vec3 attenuation;

		if (rec.material->scatter(r, rec, &attenuation, &scattered))
		{
			return multiply_vec_vec(attenuation, ray_color(scattered, world, depth - 1));
		}
		return setvec(0,0,0);
	}

	t_vec3 unit_direction = unit_vector(r.dir);
	double t = 0.5 * (unit_direction.v[1] + 1.0);
	return plus_vec_vec(multiply_vec_doub(setvec(1.0,1.0,1.0),(1.0 - t)), multiply_vec_doub(setvec(0.5, 0.7, 1.0) , t));
}

void write_color(t_vec3 color, int samples_per_pixel)
{
	double scale = 1.0 / samples_per_pixel;
	color.v[0] = sqrt(scale * color.v[0]);
	color.v[1] = sqrt(scale * color.v[1]);
	color.v[2] = sqrt(scale * color.v[2]);

	printf("%d ", (int)(256 * clamp(color.v[0], 0.0, 0.999)));
	printf("%d ", (int)(256 * clamp(color.v[1], 0.0, 0.999)));
	printf("%d\n", (int)(256 * clamp(color.v[2], 0.0, 0.999)));
}

void ft_make_imige(t_world *world)
{
	size_t hight = 400;
	size_t width = 600;
	unsigned int samples_per_pixel = 10;
	const int max_depth = 5;

	printf("P3\n%zu %zu\n255\n", width, hight);
	for (int i = hight - 1; i>= 0; --i)
	{
		dprintf(2, "\rScanlines remaining: %d", i);
		for (size_t j = 0; j < width; j++)
		{

			t_vec3 color;
			color = setvec(0,0,0);

			for (size_t a = 0; a < samples_per_pixel; a++)
			{
				double u = (j + random_double()) / (width -1);
				double v = (i + random_double()) / (hight -1);
				t_ray r = get_ray(*world->cam, u, v);
				color = plus_vec_vec(color, ray_color(r, world, max_depth));
			}
			write_color(color, samples_per_pixel);
		}
	}
	printf("Done.\n");
}

int main ()
{
	sranddev();
	t_world world;
	ft_readinput(&world);
	ft_make_imige(&world);
	free(world.cam);
	free(world.hittabels);
	return 0;
}