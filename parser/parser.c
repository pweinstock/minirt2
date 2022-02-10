/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:44:09 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/10 14:44:18 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	identifier(char *line, t_world *world)
{
	if (line[0] == '\n')
		return (1);
	else if (line[0] == 'A' && is_whitespace(line[1]))
		ambient(line, world);
	else if (line[0] == 'C' && is_whitespace(line[1]))
		camera(line, world);
	else if (line[0] == 'L' && is_whitespace(line[1]))
		light_l(line, world);
	else if (line[0] == 'D' && is_whitespace(line[1]))
		light_d(line, world);
	else if (line[0] == 's' && line[1] == 'p' && is_whitespace(line[2]))
		sphere(line, world);
	else if (line[0] == 'p' && line[1] == 'l' && is_whitespace(line[2]))
		plane(line, world);
	else if (line[0] == 'c' && (line[1] == 'y' || line[1] == 'o') \
	&& is_whitespace(line[2]))
		cylinder(line, world);
	else
	{
		printf("Error\n%c: No such identifier", line[0]);
		exit(0);
	}
	count_object(world, line);
	return (1);
}

int	parser(char *file, t_world *world)
{
	int	fd;

	world->n_hittabels = 0;
	world->n_lights = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nopen");
		exit(0);
	}
	count_objects(world, fd);
	close(fd);
	init_array(world);
	world->n_hittabels = 0;
	world->n_lights = 0;
	fd = open(file, O_RDONLY);
	fil_world(world, fd);
	close(fd);
	world->backround = setvec(1, 1, 1);
	return (1);
}
