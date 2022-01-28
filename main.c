/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/27 21:47:40 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"
/*
void ft_readinput(t_world* world)
{
	// int i;
	// int	j;
	// int ball;
	// double choose_mat;
	// t_vec3 center;
	ball = 0;

	world->hittabels = (t_object *)malloc(sizeof(t_object) * 6);
	world->lights = (t_light *)malloc(sizeof(t_light) * 6);
	world->lights->type = AMBIENT;
	world->lights->intensity = 0.9;
	world->n_lights = 1;
	world->n_cam = 1;
	// i = -11;
	// j = -11;
	world->hittabels[ball].mat.scatter = scatter_lambertian;
	world->hittabels[ball].mat.color = setvec(0.5, 0.5, 0.9);
	world->hittabels[ball].hit = hit_cylinder;
	world->hittabels[ball].center = setvec(0, 0, 0);
	world->hittabels[ball].orientation = setvec(1,1,1);
	initmatrix(&world->hittabels[ball]);
	matrix_transponieren(&world->hittabels[ball]);
	world->hittabels[ball].hight = 2;
	world->hittabels[ball].radius = 1;
	ball++;

	// world->hittabels[ball].mat.scatter = scatter_lambertian;
	// world->hittabels[ball].mat.albedo = setvec(0.5, 0.5, 0.5);
	// world->hittabels[ball].hit = hit_plane;
	// world->hittabels[ball].center = setvec(0, 0, -10);
	// world->hittabels[ball].orientation = setvec(0,0,1);
	// ball++;


	// world->hittabels[ball].radius = 1.1;
	// world->hittabels[ball].hit = hit_sphere;
	// world->hittabels[ball].mat.scatter = scatter_lambertian;
	// world->hittabels[ball].mat.color = setvec(0.2, 0.2, 0.5);
	// world->hittabels[ball].center = setvec(0, 0, 0);
	// ball++;


	// world->hittabels[ball].mat.scatter = scatter_lambertian;
	// world->hittabels[ball].mat.albedo = setvec(0.2, 0.6, 0.2);
	// world->hittabels[ball].hit = hit_cylinder;
	// world->hittabels[ball].center = setvec(0, 0, 0);
	// world->hittabels[ball].orientation = setvec(1,0,0);
	// world->hittabels[ball].hight = 4;
	// world->hittabels[ball].radius = 0.5;
	// initmatrix(&world->hittabels[ball]);
	// matrix_transponieren(&world->hittabels[ball]);
	// ball++;

	// world->hittabels[ball].mat.scatter = scatter_metal;
	// world->hittabels[ball].mat.color = setvec(0.8, 0.1, 0.1);
	// world->hittabels[ball].mat.fuzz = 0.9;
	// world->hittabels[ball].hit = hit_cone;
	// world->hittabels[ball].center = setvec(0, 0, 0); //problem 0.0, 0.0, 1
	// world->hittabels[ball].orientation = setvec(1,0,1);
	// world->hittabels[ball].hight = 10;
	// initmatrix(&world->hittabels[ball]);
	// matrix_transponieren(&world->hittabels[ball]);
	// world->hittabels[ball].radius = 4;
	// ball++;

	// world->hittabels[ball].mat.scatter = scatter_lambertian;
	// world->hittabels[ball].mat.color = setvec(0.8, 0.5, 0.5);
	// world->hittabels[ball].hit = hit_cylinder;
	// world->hittabels[ball].center = setvec(1, 0, 0.9);
	// world->hittabels[ball].orientation = setvec(1,-1,-2);
	// world->hittabels[ball].hight = 3;
	// initmatrix(&world->hittabels[ball]);
	// matrix_transponieren(&world->hittabels[ball]);
	// world->hittabels[ball].radius = 1;
	// ball++;

	// world->hittabels[ball - 2].orientation = world->hittabels[ball - 1].orientation;
	// initmatrix(&world->hittabels[ball - 2]);
	// matrix_transponieren(&world->hittabels[ball - 2]);

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
	// world->hittabels[ball].center = setvec(-4, 1, 0);
	// ball++;
	// world->hittabels[ball].radius = 1;
	// world->hittabels[ball].hit = hit_sphere;
	// world->hittabels[ball].mat.scatter = scatter_metal;
	// world->hittabels[ball].mat.albedo = random_vec3(0.5, 1);
	// world->hittabels[ball].mat.fuzz = 0.1;
	// world->hittabels[ball].center = setvec(4, 1, 0);
	// ball++;

	world->n_hittabels = ball;
	world->n_cam = 1;
	world->cam = set_cam(setvec(0, 0, 12),setvec(0, 0,-1) , 40);
	world->backround = setvec(0.5,0.5,0.5);
}
*/



bool hit(t_ray r, t_world *world, double t_min, double t_max, t_hit_record* rec)
{
	size_t	i;
	t_hit_record temp_rec;
	temp_rec.material = NULL;
	bool hit_anything = FALSE;
	double closest_so_far;
	closest_so_far = t_max;
	rec->t = t_max;

	i = 0;


	while (i < world->n_hittabels)
	{
		// printf("0test %zu", i);
		if(world->hittabels[i].hit(r, &world->hittabels[i], t_min, closest_so_far, &temp_rec))
		{
			hit_anything = TRUE;
			closest_so_far = temp_rec.t;
			transphere(rec, &temp_rec);
					// printf("test %zu\n", i);
		}
		i++;
	}
	return hit_anything;
}

double ComputeLightning(t_world *world, t_ray* reflected_ray, t_ray* ray, double specular)
{
	size_t 	i;
	t_ray	L;
	double	intensity;
	t_hit_record record; //not necasery
	double	n_dot_l;
	// double	r_dot_v;
	(void)ray;
	(void)specular;

	i = 0;
	intensity = 0;
	while (i < world->n_lights)
	{
		if (world->lights[i].type == AMBIENT)
		{
			intensity += world->lights[i].intensity;
		}
		else
		{
			t_vec3 test = minus_vec_vec(world->lights[i].position, reflected_ray->origin);

			if (world->lights[i].type == POINT)
				L = set_ray(reflected_ray->origin, unit_vector(test));
			else
				L = set_ray(reflected_ray->origin, world->lights[i].direction);
			hit(L ,world, 0.001, INFINITY, &record);
			if ((record.t != INFINITY && world->lights[i].type == DIRECTIONAL) 
				|| (world->lights[i].type == POINT && record.t < length(&test)))
			{
				// printf("%d %f %f\n", world->lights[i].type, record.t, length(&test));
				i++;
				continue ;
			}
			n_dot_l = dot(reflected_ray->dir, test);
			if (n_dot_l > 0)
			{
				intensity += world->lights[i].intensity * n_dot_l / (length(&reflected_ray->dir) * length(&test));
			}
			// else
			// printf("%f reflect dir %f %f %f test %f %f %f\n", n_dot_l, reflected_ray->dir.v[0], reflected_ray->dir.v[1], reflected_ray->dir.v[2], test.v[0], test.v[1], test.v[2]);
			// if (specular != -1)
			// {
			// 	//R = vec_sub(vec_mult(vec_mult(N, 2), dot(N, L)), L);
			// 	R = ReflectRay(L, N);
			// 	r_dot_v = dot(R, V);
			// 	if (r_dot_v > 0)
			// 		intensity += scene.lights[i].intensity * pow(r_dot_v / (length(R) * length(V)), s);
			// }
		}
		i++;
	}
	return (intensity);
}

t_vec3 ray_color(t_ray r, t_world *world, int depth)
{
	t_hit_record rec;
	t_color local_color;
	t_vec3		R;
	t_color		reflected_color;
	double l;


	// if (depth <= 0)
	// {
	// 	dprintf(2, "fehler");
	// 	return setvec(0,0,0);
	// }

    // dprintf(2, "r.dir %f r.dir %f\n", r.dir.v[0], r.dir.v[1]);

	if(!hit(r ,world, 0.001, INFINITY, &rec))
		return (world->backround);

	t_ray scattered;
	t_vec3 attenuation;

	if (!rec.material->scatter(r, rec, &attenuation, &scattered))
		return setvec(0,0,0);
	local_color = multiply_vec_doub(rec.material->color, ComputeLightning(world, &scattered, &r, rec.material->specular));
	l = rec.material->reflective;
	if(depth <= 0 || l <= 0)
		return(local_color);
	R = reflect(invert(r.dir), scattered.dir);
	reflected_color = ray_color(set_ray(scattered.origin, R), world, depth - 1);
			// dprintf(2, "farbe %f %f %f \n", attenuation.v[0], attenuation.v[1], attenuation.v[2]);
	return plus_vec_vec( multiply_vec_doub(local_color, 1 - l), multiply_vec_doub (reflected_color, l));


}

void write_color(t_vec3 color, int fd)
{
	dprintf(fd, "%d ", (int)(256 * clamp(color.v[0], 0.0, 0.999)));
	dprintf(fd, "%d ", (int)(256 * clamp(color.v[1], 0.0, 0.999)));
	dprintf(fd, "%d\n", (int)(256 * clamp(color.v[2], 0.0, 0.999)));
}

void ray_average_color(t_world* world, t_camera* cam ,int x, int y)
{
	t_color color;
	size_t i;
	double u;
	double v;
	t_ray r;

	i = 0;
	color = setvec(0,0,0);

	while (i < SAMPLES_PER_PIXEL)
	{
		u = (double)(x + random_double())  / (WIDTH -1);
		v = (double)(y + random_double())  / (HIGHT -1);
		r = get_ray(*world->cam, u, v);
		// printf("%f %f %f\n", r.dir.v[0], r.dir.v[1], r.dir.v[2]);
		color = plus_vec_vec(color, ray_color(r, world, MAX_DEPTH));
		i++;
	}
	double scale = 1.0 / SAMPLES_PER_PIXEL;
	color.v[0] = sqrt(scale * color.v[0]);
	color.v[1] = sqrt(scale * color.v[1]);
	color.v[2] = sqrt(scale * color.v[2]);
	write_color(color, cam->fd);
	my_mlx_pixel_put(&cam->img, x, HIGHT - y, color);
}


void ft_make_imige(t_world *world)
{
	size_t x;
	int y;
	size_t c;
	int	fd;
	char *file;
	file = "dat.ppm";
	c = 0;

	while(c < world->n_cam)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dprintf(fd, "P3\n%d %d\n255\n", WIDTH, HIGHT);
		world->cam[c].fd = fd;
		world->cam[c].img.img = mlx_new_image(world->mlx, WIDTH, HIGHT); //		world->cam[c].img.img = mlx_new_image(&world->cam[c].mlx_img, WIDTH, HIGHT);
		world->cam[c].img.addr = mlx_get_data_addr(world->cam[c].img.img, &world->cam[c].img.bits_per_pixel, &world->cam[c].img.line_length, &world->cam[c].img.endian);
		y = HIGHT - 1;
		while (y >= 0)
		{
			x = 0;
			// printf("\rScanlines remaining: %zu", y);
			while (x < WIDTH)
			{
				ray_average_color(world, &world->cam[c], x, y);
				x++;
			}
			y--;
		}
		// printf("Done.\n");
		close(fd);
		c++;
	}
}

int	ft_free_all(t_world *world)
{
	free(world->cam);
	free(world->hittabels);
	free(world->lights);
	mlx_destroy_window(world->mlx, world->mlx_win);
	exit(EXIT_SUCCESS);
}

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("wrong input");
		return (1);
	}
	t_world world;
	world.name = argv[1];
	world.mlx = mlx_init();
	world.mlx_win = mlx_new_window(world.mlx, WIDTH, HIGHT, "miniRT");
	parser(argv[1], &world);
	ft_make_imige(&world);
	mlx_put_image_to_window(world.mlx, world.mlx_win, world.cam[0].img.img, 0, 0);
	mlx_hook(world.mlx_win, 17, 0, ft_free_all, &world);
	mlx_loop(world.mlx);
	free(world.cam);
	free(world.hittabels);
	free(world.lights);
	return 0;
}