/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/04 01:22:26 by shackbei         ###   ########.fr       */
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

void ft_make_imige(t_world *world)
{
	world->cam[world->current_cam].img.img = mlx_new_image(world->mlx, WIDTH, HIGHT);
	world->cam[world->current_cam].img.addr = mlx_get_data_addr(world->cam[world->current_cam].img.img, &world->cam[world->current_cam].img.bits_per_pixel, &world->cam[world->current_cam].img.line_length, &world->cam[world->current_cam].img.endian);
	count_pixel(world, world->current_cam);
	mlx_put_image_to_window(world->mlx, world->mlx_win, world->cam[world->current_cam].img.img, 0, 0);
	mlx_destroy_image(world->mlx, world->cam[world->current_cam].img.img);
}

void	ft_make_imiges(t_world *world)
{
	int		fd;
	int		fd1;
	char	*file;
	char	*file1;

	file = "dat.ppm";
	file1 = "dat1.ppm";
	while (world->current_cam < world->n_cam)
	{
		if (BONUS)
		{
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dprintf(fd, "P3\n%d %d\n255\n", WIDTH, HIGHT);
			fd1 = open(file1, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dprintf(fd1, "P3\n%d %d\n255\n", WIDTH, HIGHT);
			world->cam[world->current_cam].fd = fd;
			world->cam[world->current_cam].fd1 = fd1;
		}
		ft_make_imige(world);
		if (BONUS)
			close(fd);
		world->current_cam++;
	}
}

int	ft_free_all(t_world *world)
{
	free(world->cam);
	free(world->hittabels);
	free(world->lights);
	mlx_destroy_window(world->mlx, world->mlx_win);
	exit(EXIT_SUCCESS);
}

int	ft_free_all_esc(int keycode, t_world *world)
{
	keycode = 0;
	free(world->cam);
	free(world->hittabels);
	free(world->lights);
	mlx_destroy_window(world->mlx, world->mlx_win);
	exit(EXIT_SUCCESS);
}



t_vec3	ft_rx(t_vec3 in, double deg)
{
	t_vec3 ret;

	ret.vec.x = in.vec.x;
	ret.vec.y = in.vec.y * cos(deg) - in.vec.z * sin(deg);
	ret.vec.z = in.vec.y * sin(deg) + in.vec.z * cos(deg);
	return ret;
}

t_vec3	ft_ry(t_vec3 in, double deg)
{
	t_vec3 ret;

	ret.vec.y = in.vec.y;
	ret.vec.x = in.vec.x * cos(deg) + in.vec.z * sin(deg);
	ret.vec.z = -in.vec.x * sin(deg) + in.vec.z * cos(deg);
	return ret;

}

int	ft_inden(int	key, int x, int y, t_world *world)
{
	t_camera* cam;
	t_vec3		new_orientation;
	world->current_cam = 0;
	cam = &world->cam[world->current_cam];
	if (key == 5)
		set_cam(cam, cam->origin, cam->orientation, cam->degrees * 0.9);
	else if (key == 4)
		set_cam(cam, cam->origin, cam->orientation, cam->degrees * 1.1);
	else if (key == 1)
	{
		new_orientation = ft_rx(cam->orientation, (x - HIGHT + HIGHT/2)* 0.1);
		new_orientation = ft_ry(cam->orientation, (y - WIDTH + WIDTH/2)*0.1);
		set_cam(cam, cam->origin, new_orientation, cam->degrees);
	}
	// else if (key == 3)
	// {
	// 	area->axis.xe = x;
	// 	area->axis.ye = y;
	// }
	ft_make_imige(world);
	printf("%d %d %d %f\n", x, y, key, cam->degrees);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_world	world;

	if (argc != 2)
	{
		printf("wrong input");
		return (1);
	}
	world.current_cam = 0;
	world.name = argv[1];
	world.mlx = mlx_init();
	world.mlx_win = mlx_new_window(world.mlx, WIDTH, HIGHT, "miniRT");
	parser(argv[1], &world);
	ft_make_imiges(&world);
	world.current_cam = 0;
	mlx_hook(world.mlx_win, 17, 0, ft_free_all, &world);
	mlx_key_hook(world.mlx_win, ft_free_all_esc, &world);
	mlx_hook(world.mlx_win, 04, 0, ft_inden, &world);
	mlx_loop(world.mlx);
	free(world.cam);
	free(world.hittabels);
	free(world.lights);
	return (0);
}
