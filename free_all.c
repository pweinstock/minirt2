/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:48:50 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/09 14:14:45 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

int	ft_free_all(t_world *world)
{
	int	pid;

	pid = 0;
	free(world->hittabels);
	free(world->lights);
	while (pid != -1)
		pid = wait(NULL);
	mlx_destroy_window(world->mlx, world->mlx_win);
	pthread_mutex_destroy(&world->hight_mutex);
	exit(EXIT_SUCCESS);
}
