/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:41:28 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/07 12:48:32 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	count_object(t_world *world, char *line)
{
	if (line[0] == 'A' || line[0] == 'L' || line[0] == 'D')
		world->n_lights++;
	else if ((line[1] && line[0] == 's' && line[1] == 'p')
		|| (line[0] == 'p' && line[1] == 'l')
		|| (line[0] == 'c' && (line[1] == 'y' || line[1] == 'o')))
		world->n_hittabels++;
}

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
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
	char	*line;

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

void	init_array(t_world *world)
{
	world->hittabels = \
	(t_object *)malloc(sizeof(t_object) * world->n_hittabels);
	if (!world->hittabels)
	{
		perror("Error\nmalloc");
		exit(0);
	}
	world->lights = (t_light *)malloc(sizeof(t_light) * world->n_lights);
	if (!world->lights)
	{
		perror("Error\nmalloc");
		exit(0);
	}
	return ;
}
