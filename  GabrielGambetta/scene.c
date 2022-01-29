/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:58:49 by pweinsto          #+#    #+#             */
/*   Updated: 2022/01/29 13:11:38 by pweinsto         ###   ########.fr       */
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

	spheres = malloc(sizeof(t_sphere) * 8);

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

	spheres[3].type = CYLINDER;
	spheres[3].center.x = -1.5;
	spheres[3].center.y = -2.3;
	spheres[3].center.z = 6;
	spheres[3].radius = 0.5;
	spheres[3].height = 3;
	spheres[3].orientation.x = 1;
	spheres[3].orientation.y = 0.0;
	spheres[3].orientation.z = 0;
	spheres[3].color.r = 255;
	spheres[3].color.g = 255;
	spheres[3].color.b = 0;
	spheres[3].specular = 100;
	spheres[3].reflective = 0.2;

	spheres[4].type = CAP;
	spheres[4].center.x = -1.5;
	spheres[4].center.y = -2.3;
	spheres[4].center.z = 6;
	spheres[4].radius = 0.5;
	spheres[4].height = 3;
	spheres[4].orientation.x = 1;
	spheres[4].orientation.y = 0.0;
	spheres[4].orientation.z = 0;
	spheres[4].color.r = 255;
	spheres[4].color.g = 255;
	spheres[4].color.b = 0;
	spheres[4].specular = 100;
	spheres[4].reflective = 0.2;

	spheres[5].type = CYLINDER;
	spheres[5].center.x = -1.5;
	spheres[5].center.y = -2.3;
	spheres[5].center.z = 6;
	spheres[5].radius = 0.5;
	spheres[5].height = 3;
	spheres[5].orientation.x = 1;
	spheres[5].orientation.y = 0.0;
	spheres[5].orientation.z = 0;
	spheres[5].color.r = 255;
	spheres[5].color.g = 255;
	spheres[5].color.b = 0;
	spheres[5].specular = 100;
	spheres[5].reflective = 0.2;
	
	spheres[6].type = PLANE;
	spheres[6].center.x = 0;
	spheres[6].center.y = 0;
	spheres[6].center.z = 10;
	spheres[6].orientation.x = 0;
	spheres[6].orientation.y = 0.0;
	spheres[6].orientation.z = 1;
	spheres[6].color.r = 255;
	spheres[6].color.g = 0;
	spheres[6].color.b = 255;
	spheres[6].specular = 1;
	spheres[6].reflective = 0.2;


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