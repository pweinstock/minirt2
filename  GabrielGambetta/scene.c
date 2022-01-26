/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:58:49 by pweinsto          #+#    #+#             */
/*   Updated: 2022/01/26 18:51:24 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	create_scene()
{
	t_scene		scene;
	t_sphere	*spheres;
	t_light		*lights;

	scene.backround.r = 255;
	scene.backround.g = 255;
	scene.backround.b = 255;

	spheres = malloc(sizeof(t_sphere) * 4);

	spheres[0].type = SPHERE;
	spheres[0].center.x = 0;
	spheres[0].center.y = 0.5;
	spheres[0].center.z = 3;
	spheres[0].radius = 0.5;
	spheres[0].color.r = 255;
	spheres[0].color.g = 0;
	spheres[0].color.b = 0;
	spheres[0].specular = 500;
	spheres[0].reflective = 0.2;

	spheres[1].type = SPHERE;
	spheres[1].center.x = 2;
	spheres[1].center.y = 0;
	spheres[1].center.z = 4;
	spheres[1].radius = 1;
	spheres[1].color.r = 0;
	spheres[1].color.g = 255;
	spheres[1].color.b = 0;
	spheres[1].specular = 500;
	spheres[1].reflective = 0.2;

	spheres[2].type = SPHERE;
	spheres[2].center.x = -2;
	spheres[2].center.y = 0;
	spheres[2].center.z = 4;
	spheres[2].radius = 1;
	spheres[2].color.r = 0;
	spheres[2].color.g = 0;
	spheres[2].color.b = 255;
	spheres[2].specular = 10;
	spheres[2].reflective = 0.2;

	// spheres[3].type = SPHERE;
	// spheres[3].center.x = 0;
	// spheres[3].center.y = 5001;
	// spheres[3].center.z = 0;
	// spheres[3].radius = 5000;
	// spheres[3].color.r = 255;
	// spheres[3].color.g = 255;
	// spheres[3].color.b = 0;
	// spheres[3].specular = 1000;
	// spheres[3].reflective = 0.0;

	spheres[3].type = CYLINDER;
	spheres[3].center.x = 0;
	spheres[3].center.y = -1;
	spheres[3].center.z = 10;
	spheres[3].radius = 1;
	spheres[3].height = 3;
	spheres[3].orientation.x = 1;
	spheres[3].orientation.y = 0.0;
	spheres[3].orientation.z = 2;
	spheres[3].color.r = 255;
	spheres[3].color.g = 255;
	spheres[3].color.b = 0;
	spheres[3].specular = 100;
	spheres[3].reflective = 0.0;

	scene.spheres = spheres;

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