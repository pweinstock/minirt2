/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:48:50 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 20:48:52 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

int	ft_free_all(t_world *world)
{
	int	pid;

	pid = 0;
	free(world->hittabels);
	free(world->cam);
	free(world->lights);
	while (pid != -1)
		pid = wait(NULL);
	mlx_destroy_window(world->mlx, world->mlx_win);
	exit(EXIT_SUCCESS);
}
