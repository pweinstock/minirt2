/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 12:16:15 by shackbei         ###   ########.fr       */
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

void	count_pixel(t_world *world, int hight, int width, int (*arr)[HIGHT][WIDTH])
{
	t_color average_color;
	int	x;
	int	y;

	y = hight - 1;
	while (y >= 0)
	{
		x = 0;
		printf("\rScanlines remaining: %d", y);
		while (x < width)
		{
			average_color = ray_average_color(world, &world->cam[world->current_cam], x, y);
			if (arr == NULL)
				my_mlx_pixel_put(&world->cam[world->current_cam].img, x, MLX_HIGHT - y - 1, average_color);
			else
				(*arr)[y][x] = create_trgb(0, average_color);
			x++;
		}
		y--;
	}
}

void ft_make_mlx_imige(t_world *world)
{
		world->current_cam = 0;

	world->cam[world->current_cam].img.img = mlx_new_image(world->mlx, MLX_WIDTH, MLX_HIGHT);
	world->cam[world->current_cam].img.addr = mlx_get_data_addr(world->cam[world->current_cam].img.img, &world->cam[world->current_cam].img.bits_per_pixel, &world->cam[world->current_cam].img.line_length, &world->cam[world->current_cam].img.endian);
	printf(" bits per %d  line length%d  endina %d\n", world->cam[world->current_cam].img.bits_per_pixel, world->cam[world->current_cam].img.line_length, world->cam[world->current_cam].img.endian);
	count_pixel(world, MLX_HIGHT, MLX_WIDTH, NULL);
	mlx_put_image_to_window(world->mlx, world->mlx_win, world->cam[world->current_cam].img.img, 0, 0);
	mlx_destroy_image(world->mlx, world->cam[world->current_cam].img.img);
}

void	ft_make_mlx_imiges(t_world *world)
{
	int		fd;
	int		fd1;
	char	*file;
	char	*file1;

	file = "dat.ppm";
	file1 = "dat1.bmp";
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
		ft_make_mlx_imige(world);
		if (BONUS)
			close(fd);
		world->current_cam++;
	}
	world->current_cam = 0;
}

int	ft_free_all(t_world *world)
{
	free(world->hittabels);
	free(world->cam);
	free(world->lights);
	mlx_destroy_window(world->mlx, world->mlx_win);
	exit(EXIT_SUCCESS);
}

t_vec3	ft_rx(t_vec3 in, double deg)
{
	t_vec3 ret;
	printf("deg = %f\n", deg);
	ret.vec.x = in.vec.x;
	ret.vec.y = in.vec.y * cos(deg) - in.vec.z * sin(deg);
	ret.vec.z = in.vec.y * sin(deg) + in.vec.z * cos(deg);
	return ret;
}

t_vec3	ft_ry(t_vec3 in, double deg)
{
	t_vec3 ret;

	ret.vec.x = in.vec.x * cos(deg) + in.vec.z * sin(deg);
	ret.vec.y = in.vec.y;
	ret.vec.z = -in.vec.x * sin(deg) + in.vec.z * cos(deg);
	return ret;

}

int	ft_inden(int	key, int x, int y, t_world *world)
{
	t_camera* cam;
	int		vor;
	cam = &world->cam[world->current_cam];
	if (key == 5)
		cam->origin = minus_vec_vec(cam->origin, multiply_vec_doub(cam->orientation, 0.5));
	else if (key == 4)
		cam->origin = plus_vec_vec(cam->origin, multiply_vec_doub(cam->orientation, 0.5));
	else if (key == 1)
	{
		vor = cam->orientation.vec.z / fabs(cam->orientation.vec.z);
		cam->orientation = ft_rx(cam->orientation, vor * (double)(y - MLX_HIGHT/2) / MLX_HIGHT/2);
		cam->orientation = ft_ry(cam->orientation, -(double)(x - MLX_WIDTH/2) / MLX_WIDTH/2);
	}
	set_cam(cam, cam->origin, cam->orientation, cam->degrees);
	ft_make_mlx_imige(world);
	// printf("%d %d %d %f\n", x, y, key, -(double)(y - HIGHT/2) / (double)90);
	return (0);
}

void make_pictur(t_world *world)
{
	int arr[HIGHT][WIDTH];
	count_pixel(world, HIGHT, WIDTH, &arr);
	ft_make_bmp(&arr);
}


int key_hook(int keycode, t_world *world)
{
	t_camera* cam;
	cam = &world->cam[world->current_cam];
	if(keycode == KEY_W)
		cam->origin = plus_vec_vec(cam->origin, multiply_vec_doub(cam->v , 0.5));
	else if(keycode == KEY_S)
		cam->origin = minus_vec_vec(cam->origin, multiply_vec_doub(cam->v, 0.5));
	else if(keycode == KEY_A)
		cam->origin = minus_vec_vec(cam->origin, multiply_vec_doub(cam->u, 0.5));
	else if(keycode == KEY_D)
		cam->origin = plus_vec_vec(cam->origin, multiply_vec_doub(cam->u, 0.5));
	else if(keycode == KEY_ESC)
		ft_free_all(world);
	set_cam(cam, cam->origin, cam->orientation, cam->degrees);
	if(keycode == KEY_P)
	{
		make_pictur(world);
	}
	else
		ft_make_mlx_imige(world);
	// printf("test %d \n", keycode);
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
	printf("%d, %d", MLX_WIDTH, MLX_HIGHT);
	world.current_cam = 0;
	world.name = argv[1];
	world.mlx = mlx_init();
	world.mlx_win = mlx_new_window(world.mlx, MLX_WIDTH, MLX_HIGHT, "miniRT");
	parser(argv[1], &world);

	ft_make_mlx_imiges(&world);
	world.current_cam = 0;
	mlx_hook(world.mlx_win, 17, 0, ft_free_all, &world);
	mlx_hook(world.mlx_win, 04, 0, ft_inden, &world);
	mlx_key_hook(world.mlx_win, key_hook, &world);
	mlx_loop(world.mlx);
	free(world.hittabels);
	return (0);
}
