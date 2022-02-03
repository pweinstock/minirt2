/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/03 20:32:44 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

void	write_color(t_vec3 color, int fd)
{
	dprintf(fd, "%d ", (int)(256 * clamp(color.v[0], 0.0, 0.999)));
	dprintf(fd, "%d ", (int)(256 * clamp(color.v[1], 0.0, 0.999)));
	dprintf(fd, "%d\n", (int)(256 * clamp(color.v[2], 0.0, 0.999)));
}

void	count_pixel(t_world *world, size_t c)
{
	size_t	x;
	int		y;

	y = HIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		printf("\rScanlines remaining: %d", y);
		while (x < WIDTH)
		{
			ray_average_color(world, &world->cam[c], x, y);
			x++;
		}
		y--;
	}
}

void	ft_make_imige(t_world *world)
{
	size_t	c;
	int		fd;
	int		fd1;
	char	*file;
	char	*file1;

	file = "dat.ppm";
	file1 = "da1t.ppm";
	c = 0;
	while (c < world->n_cam)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dprintf(fd, "P3\n%d %d\n255\n", WIDTH, HIGHT);
		fd1 = open(file1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dprintf(fd1, "P3\n%d %d\n255\n", WIDTH, HIGHT);
		world->cam[c].fd = fd;
		world->cam[c].fd1 = fd1;
		// world->cam[c].img.img = mlx_new_image(world->mlx, WIDTH, HIGHT); //		world->cam[c].img.img = mlx_new_image(&world->cam[c].mlx_img, WIDTH, HIGHT);
		// world->cam[c].img.addr = mlx_get_data_addr(world->cam[c].img.img, &world->cam[c].img.bits_per_pixel, &world->cam[c].img.line_length, &world->cam[c].img.endian);
		count_pixel(world, c);
		printf("Done.\n");
		close(fd);
		c++;
	}
}

int	ft_free_all(t_world *world)
{
	free(world->cam);
	free(world->hittabels);
	free(world->lights);
	// mlx_destroy_window(world->mlx, world->mlx_win);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_world	world;

	if (argc != 2)
	{
		printf("wrong input");
		return (1);
	}
	world.name = argv[1];
	// world.mlx = mlx_init();
	// world.mlx_win = mlx_new_window(world.mlx, WIDTH, HIGHT, "miniRT");
	parser(argv[1], &world);
	ft_make_imige(&world);
	// mlx_put_image_to_window(world.mlx, world.mlx_win, world.cam[0].img.img, 0, 0);
	// mlx_hook(world.mlx_win, 17, 0, ft_free_all, &world);
	// mlx_loop(world.mlx);
	free(world.cam);
	free(world.hittabels);
	free(world.lights);
	return (0);
}
