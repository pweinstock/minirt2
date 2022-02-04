/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:58:49 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/03 13:07:39 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	create_scene()
{
	t_scene		scene;
	t_object	*objects;
	t_light		*lights;

	scene.backround.r = 255;
	scene.backround.g = 255;
	scene.backround.b = 255;

	objects = malloc(sizeof(t_object) * 8);

	objects[0].type = SPHERE;
	objects[0].center.x = 0;
	objects[0].center.y = 0.5;
	objects[0].center.z = 3;
	objects[0].radius = 0.5;
	objects[0].color.r = 255;
	objects[0].color.g = 0;
	objects[0].color.b = 0;
	objects[0].specular = 500;
	objects[0].reflective = 0.2;

	objects[1].type = SPHERE;
	objects[1].center.x = 2;
	objects[1].center.y = 0;
	objects[1].center.z = 4;
	objects[1].radius = 1;
	objects[1].color.r = 0;
	objects[1].color.g = 255;
	objects[1].color.b = 0;
	objects[1].specular = 500;
	objects[1].reflective = 0.2;

	objects[2].type = SPHERE;
	objects[2].center.x = -2;
	objects[2].center.y = 0;
	objects[2].center.z = 4;
	objects[2].radius = 1;
	objects[2].color.r = 0;
	objects[2].color.g = 0;
	objects[2].color.b = 255;
	objects[2].specular = 10;
	objects[2].reflective = 0.2;

	objects[3].type = CYLINDER;
	objects[3].center.x = -1.5;
	objects[3].center.y = -2.3;
	objects[3].center.z = 6;
	objects[3].radius = 0.5;
	objects[3].height = 3;
	objects[3].orientation.x = 1;
	objects[3].orientation.y = 0.0;
	objects[3].orientation.z = 0;
	objects[3].color.r = 255;
	objects[3].color.g = 255;
	objects[3].color.b = 0;
	objects[3].specular = 100;
	objects[3].reflective = 0.2;

	// objects[4].type = CAP;
	// objects[4].center.x = -1.5;
	// objects[4].center.y = -2.3;
	// objects[4].center.z = 6;
	// objects[4].radius = 0.5;
	// objects[4].height = 3;
	// objects[4].orientation.x = 1;
	// objects[4].orientation.y = 0.0;
	// objects[4].orientation.z = 0;
	// objects[4].color.r = 255;
	// objects[4].color.g = 255;
	// objects[4].color.b = 0;
	// objects[4].specular = 100;
	// objects[4].reflective = 0.2;

	// objects[5].type = CYLINDER;
	// objects[5].center.x = -1.5;
	// objects[5].center.y = -2.3;
	// objects[5].center.z = 6;
	// objects[5].radius = 0.5;
	// objects[5].height = 3;
	// objects[5].orientation.x = 1;
	// objects[5].orientation.y = 0.0;
	// objects[5].orientation.z = 0;
	// objects[5].color.r = 255;
	// objects[5].color.g = 255;
	// objects[5].color.b = 0;
	// objects[5].specular = 100;
	// objects[5].reflective = 0.2;

	objects[6].type = PLANE;
	objects[6].center.x = 0;
	objects[6].center.y = 0;
	objects[6].center.z = 10;
	objects[6].orientation.x = 0;
	objects[6].orientation.y = 0.0;
	objects[6].orientation.z = 1;
	objects[6].color.r = 255;
	objects[6].color.g = 0;
	objects[6].color.b = 255;
	objects[6].specular = 1;
	objects[6].reflective = 0.2;


	scene.objects = objects;

	lights = malloc(sizeof(t_light) * 3);

	lights[0].type = AMBIENT;
	lights[0].intensity = 0.2;
	
	lights[1].type = POINT;
	lights[1].intensity = 0.6;
	lights[1].position.x = 2;
	lights[1].position.y = -1;
	lights[1].position.z = 0;

	lights[2].type = DIRECTIONAL;
	lights[2].intensity = 0.2;
	lights[2].direction.x = 1;
	lights[2].direction.y = -4;
	lights[2].direction.z = 4;

	scene.lights = lights;

	return (scene);
}