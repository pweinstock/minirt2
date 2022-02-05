/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 18:02:59 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

// void	write_color(t_vec3 color, int fd)
// {
// 	dprintf(fd, "%d ", (int)(256 * clamp(color.v[0], 0.0, 0.999)));
// 	dprintf(fd, "%d ", (int)(256 * clamp(color.v[1], 0.0, 0.999)));
// 	dprintf(fd, "%d\n", (int)(256 * clamp(color.v[2], 0.0, 0.999)));
// }

int	main(int argc, char *argv[])
{
	t_world	world;

	if (argc != 2)
	{
		printf("wrong input");
		return (1);
	}
	printf("%d, %d", MLX_WIDTH, MLX_HIGHT);
	world.current_cam = 0;
	world.name = argv[1];
	world.mlx = mlx_init();
	world.mlx_win = mlx_new_window(world.mlx, MLX_WIDTH, MLX_HIGHT, "miniRT");
	parser(argv[1], &world);

	ft_make_mlx_imige(&world);
	world.current_cam = 0;
	mlx_hook(world.mlx_win, 17, 0, ft_free_all, &world);
	mlx_hook(world.mlx_win, 04, 0, ft_inden, &world);
	mlx_key_hook(world.mlx_win, key_hook, &world);
	mlx_loop(world.mlx);
	ft_free_all(&world);
	return (1);
}
