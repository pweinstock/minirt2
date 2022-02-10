/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_picture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:44:02 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/10 10:14:01 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	make_pictur(t_world *world)
{
	t_picture_part	part;
	int				*arr;

	arr = (int *)malloc(sizeof(int) * HIGHT * WIDTH);
	if (arr != NULL)
	{
		part.x.from = 0;
		part.x.to = WIDTH;
		part.x.current = 0;
		part.y.from = 0;
		part.y.to = HIGHT;
		part.y.current = HIGHT;
		part.ges_y.from = 0;
		part.ges_y.to = HIGHT;
		part.ges_y.current = HIGHT;
		count_pixel(world, &part, arr, NULL);
		ft_make_bmp(arr);
		free(arr);
	}
	free(world->hittabels);
	free(world->lights);
	pthread_mutex_destroy(&world->hight_mutex);
	exit(EXIT_SUCCESS);
}
