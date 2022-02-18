/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:36:53 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/18 14:58:41 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	camera(char *line, t_world *world)
{
	char		**data;
	t_camera	*cam;

	cam = &world->cam;
	data = ft_split_space(line);
	ft_array_length(data, 4, "C");
	set_cam(cam, strtovec(data[1]), strtovec(data[2]), \
	(double)ft_atoi(data[3]));
	ft_free_arr(data);
	return (0);
}
