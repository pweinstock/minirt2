/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:44:09 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/05 17:58:18 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "parser.h"

int	ft_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

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
	if (ft_array_length(data) != 3)
	{
		printf("Error\nvec3: Wrong number of arguments");
		exit(0);
	}
	vec.v[0] = ft_atof(data[0]);
	vec.v[1] = ft_atof(data[1]);
	vec.v[2] = ft_atof(data[2]);
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
	world->r += world->lights[world->n_lights].color.col.r * world->lights[world->n_lights].intensity;
	world->g += world->lights[world->n_lights].color.col.g * world->lights[world->n_lights].intensity;
	world->b += world->lights[world->n_lights].color.col.b * world->lights[world->n_lights].intensity;
	if (world->r > 255 || world->g > 255 || world->b > 255)
	{
		printf("Error\nintensity: Values out of range\n");
		exit(0);
	}
	return ;
}

int	ambient(char *line, t_world *world)
{
	char	**data;
	char	**color;

	if (world->A_flag == TRUE)
	{
		printf("Error\nAmbient lighting already exists\n");
		exit(0);
	}
	data = ft_split_space(line);
	if (ft_array_length(data) != 3)
	{
		printf("Error\n%s: A: Wrong number of information", world->name);
		exit(0);
	}
	world->lights[world->n_lights].intensity = ft_atof(data[1]);
	color = ft_split(data[2], ',');
	world->lights[world->n_lights].color.col.r = ft_atoi(color[0]);
	world->lights[world->n_lights].color.col.g = ft_atoi(color[1]);
	world->lights[world->n_lights].color.col.b = ft_atoi(color[2]);
	world->lights[world->n_lights].type = AMBIENT;
	//color_check(world->lights[world->n_lights].color);
	light_intensity_ceck(world);
	free(data);
	free(color);
	world->A_flag = TRUE;
	return (0);
}

int	camera(char *line, t_world *world)
{
	char	**data;
	t_camera* cam;

	if (world->C_flag == TRUE)
	{
		printf("Error\nCamera already exists\n");
		exit(0);
	}
	cam = &world->cam[world->n_cam];
	data = ft_split_space(line);
	if (ft_array_length(data) != 4)
	{
		printf("Error\n%s: C: Wrong number of information", world->name);
		exit(0);
	}
	set_cam(cam, strtovec(data[1]), strtovec(data[2]), (double)ft_atoi(data[3]));
	// cam->origin = strtovec(data[1]);
	// cam->w = unit_vector(minus_vec_vec(cam->origin, strtovec(data[2])));
	// // cam->w = strtovec(data[2]);
	// cam->u = unit_vector(cross(setvec(0,1,0), cam->w));
	// cam->v = cross(cam->w, cam->u);

	// double theta = degrees_to_radians(ft_atoi(data[3]));
	// double h = tan(theta/2);
	// double viewport_height = 2 * h;
	// double viewport_width = (double)WIDTH/HIGHT * viewport_height;

	// double focus_dist = 1;
	// double aperture = 2;
	// cam->horizontal = multiply_vec_doub(cam->u, focus_dist * viewport_width);
	// cam->vertical = multiply_vec_doub(cam->v, focus_dist * viewport_height);
	// cam->lower_left_corner = minus_vec_vec(minus_vec_vec(minus_vec_vec(cam->origin, division(cam->horizontal, 2)), division(cam->vertical, 2)), multiply_vec_doub(cam->w, focus_dist));

	// cam->lens_radius = aperture / 2;

	// 	printf("%f %f %f", world->cam[world->n_cam].origin.v[0], world->cam[world->n_cam].origin.v[1], world->cam[world->n_cam].origin.v[2]);

	// //camera.horizontal = ft_atoi(data[3]);					//problem
	// //printf("center: %f, %f, %f\n", camera.lower_left_corner.v[0], camera.lower_left_corner.v[1], camera.lower_left_corner.v[2]);
	free(data);
	world->C_flag = TRUE;
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
	if (ft_array_length(data) != 4)
	{
		printf("Error\n%s: L: Wrong number of information", world->name);
		exit(0);
	}
	world->lights[world->n_lights].position = strtovec(data[1]);
	world->lights[world->n_lights].intensity = ft_atof(data[2]);
	world->lights[world->n_lights].color = strtovec(data[3]);
	world->lights[world->n_lights].type = POINT;
	// printf("center: %f, %f, %f\n", light.color.v[0], light.color.v[1], light.color.v[2]);
	// printf("diameter %f\n", light.diameter);
	light_intensity_ceck(world);
	free(data);
	world->L_flag = TRUE;
	return (0);
}

int	light_d(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	if (ft_array_length(data) != 5)
	{
		printf("Error\n%s: D: Wrong number of information", world->name);
		exit(0);
	}
	world->lights[world->n_lights].direction = strtovec(data[1]);
	world->lights[world->n_lights].intensity = ft_atof(data[2]);
	world->lights[world->n_lights].color = strtovec(data[3]);
	world->lights[world->n_lights].type = DIRECTIONAL;
	// printf("center: %f, %f, %f\n", light.color.v[0], light.color.v[1], light.color.v[2]);
	// printf("diameter %f\n", light.diameter);
	light_intensity_ceck(world);
	free(data);
	return (0);
}

int	sphere(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	if (ft_array_length(data) != 4)
	{
		printf("Error\n%s: sp: Wrong number of information", world->name);
		exit(0);
	}
	world->hittabels[world->n_hittabels].center = strtovec(data[1]);
	world->hittabels[world->n_hittabels].radius = ft_atof(data[2]) / 2;
	world->hittabels[world->n_hittabels].mat.color = division(strtovec(data[3]), 255);
	world->hittabels[world->n_hittabels].hit = hit_sphere;
	world->hittabels[world->n_hittabels].mat.scatter = scatter_lambertian;
	world->hittabels[world->n_hittabels].mat.specular = -1;
	world->hittabels[world->n_hittabels].mat.reflective = 0.5;
	world->hittabels[world->n_hittabels].mat.ir = 1.5;
	// printf("center: %f, %f, %f\n", sphere.color.v[0], sphere.color.v[1], sphere.color.v[2]);
	// printf("diameter %f\n", sphere.diameter);
	free(data);
	return (1);
}

int	plane(char *line, t_world *world)
{
	char	**data;

	data = ft_split_space(line);
	if (ft_array_length(data) != 4)
	{
		printf("Error\n%s: pl: Wrong number of information", world->name);
		exit(0);
	}
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

	data = ft_split_space(line);
	if (ft_array_length(data) != 6)
	{
		printf("Error\n%s: cy: Wrong number of information", world->name);
		exit(0);
	}
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
	if (line[0] == '\n')
		return (1);
	else if (line[0] == 'A' && ((line[1] >= 9 && line[1] <= 13) || (line[1] == 32)))
		ambient(line, world);
	else if (line[0] == 'C' && ((line[1] >= 9 && line[1] <= 13) || (line[1] == 32)))
		camera(line, world);
	else if (line[0] == 'L' && ((line[1] >= 9 && line[1] <= 13) || (line[1] == 32)))
		light_l(line, world);
	else if (line[0] == 'D' && ((line[1] >= 9 && line[1] <= 13) || (line[1] == 32)))
		light_d(line, world);
	else if (line[0] == 's' && line[1] == 'p' && ((line[2] >= 9 && line[2] <= 13) || (line[2] == 32)))
		sphere(line, world);
	else if (line[0] == 'p' && line[1] == 'l' && ((line[2] >= 9 && line[2] <= 13) || (line[2] == 32)))
		plane(line, world);
	else if (line[0] == 'c' && (line[1] == 'y' || line[1] == 'o') && ((line[2] >= 9 && line[2] <= 13) || (line[2] == 32)))
		cylinder(line, world);
	else
		{
			printf("Error\n%s: %s: No such identifier", world->name, ft_split_space(line)[0]);
			exit(0);
		}
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
		perror("Error\nopen");
		return (0);
	}
	count_objects(world, fd);
	close(fd);
	world->hittabels = (t_object *)malloc(sizeof(t_object) * world->n_hittabels);
	if (!world->hittabels)
	{
		perror("Error\nmalloc");
		return (0);
	}
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
	return (1);
}
