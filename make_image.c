/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 22:19:58 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/08 15:45:04 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	*ft_make_mlx_imige(void *tmp_world)
{
	t_world			*world;
	t_picture_part	part;

	world = (t_world *)tmp_world;
	part.ges_y.from = 0;
	part.ges_y.to = MLX_HIGHT;
	part.ges_y.current = MLX_HIGHT;
	part.x.from = 0;
	part.x.to = MLX_WIDTH;
	part.x.current = 0;
	pthread_mutex_lock(&world->hight_mutex);
	part.y.to = world->picture_part_hight;
	part.y.current = world->picture_part_hight;
	world->picture_part_hight -= (MLX_HIGHT / MLX_THREADS) + 1;
	if (world->picture_part_hight < 0)
		world->picture_part_hight = 0;
	part.y.from = world->picture_part_hight;
	pthread_mutex_unlock(&world->hight_mutex);
	count_pixel(world, &part, NULL, &world->cam.img);
	return (0);
}

void	ft_start_threads(t_world *world)
{
	pthread_t	thread[MLX_THREADS];
	int			i;

	i = 0;
	world->picture_part_hight = MLX_HIGHT;
	while (i < MLX_THREADS)
	{
		if (pthread_create(&thread[MLX_THREADS - 1 - i], NULL,
				ft_make_mlx_imige, world) != 0)
			break ;
		i++;
	}
	i--;
	while (i > 0)
	{
		pthread_join(thread[i], NULL);
		i--;
	}
}

void	ft_make_mlx_imiges(t_world *world)
{
	world->cam.img.img = mlx_new_image(world->mlx, MLX_WIDTH, MLX_HIGHT);
	world->cam.img.addr = mlx_get_data_addr(world->cam.img.img,
			&world->cam.img.bits_per_pixel, &world->cam.img.line_length,
			&world->cam.img.endian);
	pthread_mutex_init(&world->hight_mutex, NULL);
	ft_start_threads(world);
	mlx_put_image_to_window(world->mlx, world->mlx_win,
		world->cam.img.img, 0, 0);
	pthread_mutex_destroy(&world->hight_mutex);
	mlx_destroy_image(world->mlx, world->cam.img.img);
}
