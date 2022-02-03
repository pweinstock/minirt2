/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:44:09 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/03 21:09:02 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "parser.h"

double	ft_atof(char *str)
{
	double	d;
	double	dec;
	int	place;
	int	minus;

	dec = 0;
	place = 0;
	d = 0;
	minus = 0;
	d += ft_atoi(str);
	if (*str == '-')
	{
		minus = 1;
		str++;
	}
	while (ft_isdigit(*str))
		str++;
	if (!*str)
		return (d);
	if (*str == '.')
	{
		str++;
		dec += ft_atoi(str);
	}
	// else
	// 	error();
	while (ft_isdigit(*str))
	{
		place++;
		str++;
	}
	if (minus)
		return (d - dec / pow(10, place));
	else
		return (d + dec / pow(10, place));
}

t_vec3	strtovec(char *str)
{
	t_vec3	vec;
	char	**data;

	data = ft_split(str, ',');
	vec.v[0] = ft_atof(data[0]);
	vec.v[1] = ft_atof(data[1]);
	vec.v[2] = ft_atof(data[2]);
	return (vec);
}

int	ambient(char *line, t_world *world)
{
	char	**data;
	char	**color;

	data = ft_split(line, '	');
	world->lights[world->n_lights].intensity = ft_atof(data[1]);
	color = ft_split(data[2], ',');
	world->lights[world->n_lights].color.col.r = ft_atoi(color[0]);
	world->lights[world->n_lights].color.col.g = ft_atoi(color[1]);
	world->lights[world->n_lights].color.col.b = ft_atoi(color[2]);
	world->lights[world->n_lights].type = AMBIENT;
	// printf("diameter: %f\n", ambient.diameter);
	// printf("color: %f\n", ambient.color.v[2]);
	free(data);
	free(color);
	return (0);
}

int	camera(char *line, t_world *world)
{
	char	**data;
	t_camera* cam;

	cam = &world->cam[world->n_cam];

	data = ft_split(line, '	');
	cam->origin = strtovec(data[1]);
	cam->w = unit_vector(minus_vec_vec(cam->origin, strtovec(data[2])));
	// cam->w = strtovec(data[2]);
	cam->u = unit_vector(cross(setvec(0,1,0), cam->w));
	cam->v = cross(cam->w, cam->u);

	double theta = degrees_to_radians(ft_atoi(data[3]));
	double h = tan(theta/2);
	double viewport_height = 2 * h;
	double viewport_width = (double)WIDTH/HIGHT * viewport_height;

	double focus_dist = 1;
	double aperture = 2;
	cam->horizontal = multiply_vec_doub(cam->u, focus_dist * viewport_width);
	cam->vertical = multiply_vec_doub(cam->v, focus_dist * viewport_height);
	cam->lower_left_corner = minus_vec_vec(minus_vec_vec(minus_vec_vec(cam->origin, division(cam->horizontal, 2)), division(cam->vertical, 2)), multiply_vec_doub(cam->w, focus_dist));

	cam->lens_radius = aperture / 2;

		printf("%f %f %f", world->cam[world->n_cam].origin.v[0], world->cam[world->n_cam].origin.v[1], world->cam[world->n_cam].origin.v[2]);

	//camera.horizontal = ft_atoi(data[3]);					//problem
	//printf("center: %f, %f, %f\n", camera.lower_left_corner.v[0], camera.lower_left_corner.v[1], camera.lower_left_corner.v[2]);
	free(data);
	return (0);
}

int	light_l(char *line, t_world *world)
{
	char	**data;

	data = ft_split(line, '	');
	world->lights[world->n_lights].position = strtovec(data[1]);
	world->lights[world->n_lights].intensity = ft_atof(data[2]);
	world->lights[world->n_lights].color = strtovec(data[3]);
	world->lights[world->n_lights].type = POINT;
	// printf("center: %f, %f, %f\n", light.color.v[0], light.color.v[1], light.color.v[2]);
	// printf("diameter %f\n", light.diameter);
	free(data);
	return (0);
}

int	light_d(char *line, t_world *world)
{
	char	**data;

	data = ft_split(line, '	');
	world->lights[world->n_lights].direction = strtovec(data[1]);
	world->lights[world->n_lights].intensity = ft_atof(data[2]);
	world->lights[world->n_lights].color = strtovec(data[3]);
	world->lights[world->n_lights].type = DIRECTIONAL;
	// printf("center: %f, %f, %f\n", light.color.v[0], light.color.v[1], light.color.v[2]);
	// printf("diameter %f\n", light.diameter);
	free(data);
	return (0);
}

int	sphere(char *line, t_world *world)
{
	char	**data;

	data = ft_split(line, '	');
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].radius = ft_atof(data[2]) / 2;
	world->hittabels[world->n_hittabels].mat.color = division(strtovec(data[3]), 255);
	world->hittabels[world->n_hittabels].hit = hit_sphere;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat.specular = -1;
	world->hittabels[world->n_hittabels].mat.reflective = 0;
	world->hittabels[world->n_hittabels].mat.ir = 1.5;
	// printf("center: %f, %f, %f\n", sphere.color.v[0], sphere.color.v[1], sphere.color.v[2]);
	// printf("diameter %f\n", sphere.diameter);
	free(data);
	return (1);
}

int	plane(char *line, t_world *world)
{
	char	**data;

	data = ft_split(line, '	');
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].orientation = strtovec(data[2]);
	world->hittabels[world->n_hittabels].mat.color = division(strtovec(data[3]), 255);
	world->hittabels[world->n_hittabels].hit = hit_plane;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat.specular = -1;
	world->hittabels[world->n_hittabels].mat.reflective = 0;
	//printf("center: %f, %f, %f\n", plane.orientation.v[0], plane.orientation.v[1], plane.orientation.v[2]);
	free(data);
	return (0);
}

int	cylinder(char *line, t_world *world)
{
	char	**data;

	data = ft_split(line, '	');
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].orientation = strtovec(data[2]);
	world->hittabels[world->n_hittabels].radius = ft_atof(data[3]) / 2;
	world->hittabels[world->n_hittabels].hight = ft_atof(data[4]);
	world->hittabels[world->n_hittabels].mat.color = division(strtovec(data[5]), 255);
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
	// printf("%f %f %f", world->hittabels[world->n_hittabels].center.v[0], world->hittabels[world->n_hittabels].center.v[1], world->hittabels[world->n_hittabels].center.v[2]);
	free(data);
	return (0);
}

void	count_object(t_world *world, char *line)
{
	if (line[0] == 'A' || line[0] == 'L' || line[0] == 'D')
		world->n_lights++;
	else if (line[0] == 'C')
		world->n_cam++;
	else if ((line[1] && line[0] == 's' && line[1] == 'p')
		|| (line[0] == 'p' && line[1] == 'l')
		|| (line[0] == 'c' &&( line[1] == 'y'
			|| line[1] == 'o')))
		world->n_hittabels++;
}

int	identifier(char *line, t_world *world)
{
	if (line[0] == 'A')
		ambient(line, world);
	else if (line[0] == 'C')
		camera(line, world);
	else if (line[0] == 'L')
		light_l(line, world);
	else if (line[0] == 'D')
		light_d(line, world);
	else if (line[1] && line[0] == 's' && line[1] == 'p')
		sphere(line, world);
	else if (line[1] && line[0] == 'p' && line[1] == 'l')
		plane(line, world);
	else if (line[1] && line[0] == 'c' && (line[1] == 'y' || line[1] == 'o'))
		cylinder(line, world);
	count_object(world, line);
	return (1);
}

void	count_objects(t_world *world, int fd)
{
	char	*line;

	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return ;
		count_object(world, line);
		free(line);
	}
}

t_bool	fil_world(t_world *world, int fd)
{
	char*	line;

	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		identifier(line, world);
		free(line);
	}
	return (TRUE);
}

int	parser(char *file, t_world *world)
{
	int	fd;

	world->n_hittabels = 0;
	world->n_cam = 0;
	world->n_lights = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("file can't open\n");
		return (1);
	}
	count_objects(world, fd);
	close(fd);
	world->hittabels = (t_object *)malloc(sizeof(t_object) * world->n_hittabels);
	world->cam = (t_camera *)malloc(sizeof(t_camera) * world->n_cam);
	world->lights = (t_light *)malloc(sizeof(t_light) * world->n_lights);
	world->n_hittabels = 0;
	world->n_cam = 0;
	world->n_lights = 0;
	fd = open(file, O_RDONLY);
	fil_world(world, fd);
	close(fd);
	world->backround = setvec(1, 1, 1);
	printf("vertig %zu\n", world->n_hittabels);
	return (0);
}
