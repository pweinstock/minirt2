/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:44:51 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/07 21:52:15 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "world.h"

static void	make_pictur(t_world *world)
{
	int				arr[HIGHT][WIDTH];
	t_picture_part	part;

	part.x.from = 0;
	part.x.to = WIDTH;
	part.x.current = 0;
	part.y.from = 0;
	part.y.to = HIGHT;
	part.y.current = HIGHT;
	part.ges_y.from = 0;
	part.ges_y.to = HIGHT;
	part.ges_y.current = HIGHT;
	count_pixel(world, &part, &arr, NULL);
	ft_make_bmp(&arr);
	ft_free_all(world);
}

int	key_hook(int keycode, t_world *world)
{
	int			pid;
	t_camera	*ca;

	ca = &world->cam;
	if (keycode == KEY_W)
		ca->origin = plus_vec_vec(ca->origin, multiply_vec_doub(ca->v, 0.5));
	else if (keycode == KEY_S)
		ca->origin = minus_vec_vec(ca->origin, multiply_vec_doub(ca->v, 0.5));
	else if (keycode == KEY_A)
		ca->origin = minus_vec_vec(ca->origin, multiply_vec_doub(ca->u, 0.5));
	else if (keycode == KEY_D)
		ca->origin = plus_vec_vec(ca->origin, multiply_vec_doub(ca->u, 0.5));
	else if (keycode == KEY_ESC)
		ft_free_all(world);
	set_cam(ca, ca->origin, ca->orientation, ca->degrees);
	if (keycode == KEY_P)
	{
		pid = fork();
		if (pid == 0)
			make_pictur(world);
	}
	else
		ft_make_mlx_imiges(world);
	return (0);
}

static t_vec3	ft_rx(t_vec3 in, double deg)
{
	t_vec3	ret;

	ret.vec.x = in.vec.x;
	ret.vec.y = in.vec.y * cos(deg) - in.vec.z * sin(deg);
	ret.vec.z = in.vec.y * sin(deg) + in.vec.z * cos(deg);
	return (ret);
}

static t_vec3	ft_ry(t_vec3 in, double deg)
{
	t_vec3	ret;

	ret.vec.x = in.vec.x * cos(deg) + in.vec.z * sin(deg);
	ret.vec.y = in.vec.y;
	ret.vec.z = -in.vec.x * sin(deg) + in.vec.z * cos(deg);
	return (ret);
}

int	ft_inden(int	key, int x, int y, t_world *world)
{
	t_camera	*cam;
	int			vor;

	cam = &world->cam;
	if (key == 5)
		cam->origin = minus_vec_vec(cam->origin,
				multiply_vec_doub(cam->orientation, 0.5));
	else if (key == 4)
		cam->origin = plus_vec_vec(cam->origin,
				multiply_vec_doub(cam->orientation, 0.5));
	else if (key == 1)
	{
		vor = cam->orientation.vec.z / fabs(cam->orientation.vec.z);
		cam->orientation = ft_rx(cam->orientation,
				vor * (double)(y - MLX_HIGHT / 2) / MLX_HIGHT / 2);
		cam->orientation = ft_ry(cam->orientation,
				-(double)(x - MLX_WIDTH / 2) / MLX_WIDTH / 2);
	}
	set_cam(cam, cam->origin, cam->orientation, cam->degrees);
	ft_make_mlx_imiges(world);
	return (0);
}
