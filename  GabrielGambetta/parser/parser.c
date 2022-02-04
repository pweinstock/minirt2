/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:44:09 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/04 12:36:06 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "../miniRT.h"

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

t_vec	strtovec(char *str)
{
	t_vec	vec;
	char	**data;

	data = ft_split(str, ',');
	vec.x = ft_atof(data[0]);
	vec.y = ft_atof(data[1]);
	vec.z = ft_atof(data[2]);
	return (vec);
}

int	ambient(t_scene *scene, char *line)
{
	char	**data;
	char	**color;

	scene->lights[scene->light].type = AMBIENT;
	data = ft_split(line, '	');
	scene->lights[scene->light].intensity = ft_atof(data[1]);
	color = ft_split(data[2], ',');
	scene->lights[scene->light].color.r = ft_atoi(color[0]);
	scene->lights[scene->light].color.g = ft_atoi(color[1]);
	scene->lights[scene->light].color.b = ft_atoi(color[2]);
	// printf("diameter: %f\n", ambient.diameter);
	// printf("color: %f\n", ambient.color.v[2]);
	scene->light += 1;
	return (1);
}

int	camera(t_scene *scene, char *line)
{
	char	**data;

	data = ft_split(line, '	');
	scene->cameras[scene->camera].center = strtovec(data[1]);
	scene->cameras[scene->camera].orientation = strtovec(data[2]);
	scene->cameras[scene->camera].view = ft_atoi(data[3]);					//problem
	//printf("center: %f, %f, %f\n", camera.lower_left_corner.v[0], camera.lower_left_corner.v[1], camera.lower_left_corner.v[2]);
	scene->camera += 1;
	return (1);
}

int	directional(t_scene *scene, char *line)
{
	char	**data;
	char	**color;

	scene->lights[scene->light].type = DIRECTIONAL;
	data = ft_split(line, '	');
	scene->lights[scene->light].direction = strtovec(data[1]);
	scene->lights[scene->light].intensity = ft_atof(data[2]);
	color = ft_split(data[3], ',');
	scene->lights[scene->light].color.r = ft_atoi(color[0]);
	scene->lights[scene->light].color.g = ft_atoi(color[1]);
	scene->lights[scene->light].color.b = ft_atoi(color[2]);
	// printf("center: %f, %f, %f\n", light.color.v[0], light.color.v[1], light.color.v[2]);
	// printf("diameter %f\n", light.diameter);
	scene->light += 1;
	return (1);
}

int	light(t_scene *scene, char *line)
{
	char	**data;
	char	**color;

	scene->lights[scene->light].type = POINT;
	data = ft_split(line, '	');
	scene->lights[scene->light].position = strtovec(data[1]);
	scene->lights[scene->light].intensity = ft_atof(data[2]);
	color = ft_split(data[3], ',');
	scene->lights[scene->light].color.r = ft_atoi(color[0]);
	scene->lights[scene->light].color.g = ft_atoi(color[1]);
	scene->lights[scene->light].color.b = ft_atoi(color[2]);
	// printf("center: %f, %f, %f\n", light.color.v[0], light.color.v[1], light.color.v[2]);
	// printf("diameter %f\n", light.diameter);
	scene->light += 1;
	return (1);
}

int	sphere(t_scene *scene, char *line)
{
	char	**data;
	char	**color;

	scene->objects[scene->object].type = SPHERE;
	data = ft_split(line, '	');
	scene->objects[scene->object].center = strtovec(data[1]);
	scene->objects[scene->object].radius = ft_atof(data[2]);
	color = ft_split(data[3], ',');
	scene->objects[scene->object].color.r = ft_atoi(color[0]);
	scene->objects[scene->object].color.g = ft_atoi(color[1]);
	scene->objects[scene->object].color.b = ft_atoi(color[2]);
	// printf("center: %f, %f, %f\n", sphere.color.v[0], sphere.color.v[1], sphere.color.v[2]);
	// printf("diameter %f\n", sphere.diameter);
	scene->objects[scene->object].specular = 500;
	scene->objects[scene->object].reflective = 0.2;
	scene->object += 1;
	return (1);
}

int	plane(t_scene *scene, char *line)
{
	char	**data;
	char	**color;

	
	scene->objects[scene->object].type = PLANE; 
	data = ft_split(line, '	');
	scene->objects[scene->object].center = strtovec(data[1]);
	scene->objects[scene->object].orientation = strtovec(data[2]);
	color = ft_split(data[3], ',');
	scene->objects[scene->object].color.r = ft_atoi(color[0]);
	scene->objects[scene->object].color.g = ft_atoi(color[1]);
	scene->objects[scene->object].color.b = ft_atoi(color[2]);
	//printf("center: %f, %f, %f\n", plane.orientation.v[0], plane.orientation.v[1], plane.orientation.v[2]);
	scene->objects[scene->object].specular = 0;
	scene->objects[scene->object].reflective = 0.0;
	scene->object += 1;
	return (1);
}

int	create_bottom_cap(t_scene *scene)
{
	scene->objects[scene->object].type = CAP;
	scene->objects[scene->object].center = vec_sub(scene->objects[scene->object - 1].center, vec_mult(vec_divide(scene->objects[scene->object - 1].orientation, length(scene->objects[scene->object - 1].orientation)), scene->objects[scene->object - 1].height / 10));
	scene->objects[scene->object].orientation = vec_mult(scene->objects[scene->object - 1].orientation, -1);
	scene->objects[scene->object].radius = scene->objects[scene->object - 1].radius;
	scene->objects[scene->object].color.r = 255 - scene->objects[scene->object - 1].color.r;
	scene->objects[scene->object].color.g = 255 - scene->objects[scene->object - 1].color.g;
	scene->objects[scene->object].color.b = 255 - scene->objects[scene->object - 1].color.b;
	scene->objects[scene->object].specular = scene->objects[scene->object - 1].specular;
	scene->objects[scene->object].reflective = scene->objects[scene->object - 1].reflective;
	scene->object += 1;
	return (1);
}

int	create_top_cap(t_scene *scene)
{
	scene->objects[scene->object].type = CAP;
	scene->objects[scene->object].center = vec_add(scene->objects[scene->object - 2].center, vec_mult(vec_divide(scene->objects[scene->object - 2].orientation, length(scene->objects[scene->object - 2].orientation)), scene->objects[scene->object - 2].height / 2));
	scene->objects[scene->object].orientation = scene->objects[scene->object - 2].orientation;
	scene->objects[scene->object].radius = scene->objects[scene->object - 2].radius;
	scene->objects[scene->object].color.r = 200;//scene->objects[scene->object - 2].color.r;
	scene->objects[scene->object].color.g = 200;//scene->objects[scene->object - 2].color.g;
	scene->objects[scene->object].color.b = 200;//scene->objects[scene->object - 2].color.b;
	scene->objects[scene->object].specular = scene->objects[scene->object - 2].specular;
	scene->objects[scene->object].reflective = scene->objects[scene->object - 2].reflective;
	scene->object += 1;
	return (1);
}

int	cylinder(t_scene *scene, char *line)
{
	char	**data;
	char	**color;

	scene->objects[scene->object].type = CYLINDER;
	data = ft_split(line, '	');
	scene->objects[scene->object].center = strtovec(data[1]);
	scene->objects[scene->object].orientation = strtovec(data[2]);
	scene->objects[scene->object].radius = ft_atof(data[3]);
	scene->objects[scene->object].height = ft_atof(data[4]);
	color = ft_split(data[5], ',');
	scene->objects[scene->object].color.r = ft_atoi(color[0]);
	scene->objects[scene->object].color.g = ft_atoi(color[1]);
	scene->objects[scene->object].color.b = ft_atoi(color[2]);
	scene->objects[scene->object].specular = 500;
	scene->objects[scene->object].reflective = 0.0;
	//printf("center: %f, %f, %f\n", cylinder.color.v[0], cylinder.color.v[1], cylinder.color.v[2]);
	scene->object += 1;
	create_bottom_cap(scene);
	create_top_cap(scene);
	return (1);
}

int	identifier(t_scene *scene, char *line)
{
	if (line[0] == 'A')
		ambient(scene, line);
	else if (line[0] == 'C')
		camera(scene, line);
	else if (line[0] == 'L')
		light(scene, line);
	else if (line[0] == 'D')
		directional(scene, line);
	else if (line[0] == 's' && line[1] == 'p')
		sphere(scene, line);
	else if (line[0] == 'p' && line[1] == 'l')
		plane(scene, line);
	else if (line[0] == 'c' && line[1] == 'y')
		cylinder(scene, line);
	// else
	// 	error();
	return (1);
}

int	is_object(char *line)
{
	if (line[0] == 's' && line[1] == 'p')
		return (1);
	if (line[0] == 'p' && line[1] == 'l')
		return (1);
	if (line[0] == 'c' && line[1] == 'y')
		return (3);
	return (0);
}

int	is_light(char *line)
{
	if (line[0] == 'A')
		return (1);
	if (line[0] == 'L')
		return (1);
	return (0);
}

int	is_camera (char *line)
{
	if (line[0] == 'C')
		return (1);
	return (0);
}


t_count	counter(char *file)
{
	int	fd;
	char *line;
	t_count	count;

	count.objects = 0;
	count.lights = 0;
	count.cameras = 0;
	fd = open(file, O_RDONLY);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_object(line))
			count.objects += is_object(line);
		else if (is_light(line))
			count.lights += 1;
		else if (is_camera(line))
			count.cameras += 1;
		// else
		// 	error;
	}
	close(fd);
	return (count);
}

void	parser(char *file, t_scene *scene)
{
	int	fd;
	char	*line;

	//printf("objects: %d\nlights: %d\n cameras: %d\n", count.objects, count.lights, count.cameras);

	
	fd = open(file, O_RDONLY);
	//printf("count: %d\n", count);
	//printf("data: %s\n", data);
	while (42)
	{
		
		line = get_next_line(fd);
		if (!line)
			break ;
		identifier(scene, line);
	}
	scene->objects[scene->object + 1].type = TERM;
	scene->lights[scene->light + 1].type = TERM;
	//scene->cameras[scene->camera + 1].type = NULL;
	close(fd);
	return ;
}

int	scene_init(char *file, t_scene *scene)
{
	t_count	count;

	count = counter(file);
	scene->objects = malloc(sizeof(t_object) * (count.objects + 1));
	scene->lights = malloc(sizeof(t_light) * (count.lights + 1));
	scene->cameras = malloc(sizeof(t_camera) * (count.cameras + 1));
	scene->object = 0;
	scene->light = 0;
	scene->camera = 0;
	scene->backround.r = 255;
	scene->backround.g = 255;
	scene->backround.b = 255;
	parser(file, scene);
	//printf("intensity: %d\n", scene->objects[2].type);
	return (1);
}