/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 10:35:24 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

int	main(int argc, char *argv[])
{
	t_world	world;

	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (1);
	}
	world.name = argv[1];
	world.mlx = mlx_init();
	world.mlx_win = mlx_new_window(world.mlx, MLX_WIDTH, MLX_HIGHT, "miniRT");
	parser(argv[1], &world);
	pthread_mutex_init(&world.hight_mutex, NULL);
	ft_make_mlx_imiges(&world);
	mlx_hook(world.mlx_win, 17, 0, ft_free_all, &world);
	mlx_hook(world.mlx_win, 04, 0, ft_inden, &world);
	mlx_hook(world.mlx_win, 2, 0, key_hook, &world);
	mlx_loop(world.mlx);
	ft_free_all(&world);
	return (1);
}
