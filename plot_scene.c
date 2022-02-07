/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:03:27 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/07 22:03:03 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

int	create_trgb(int t, t_color color)
{
	double	r;
	double	g;
	double	b;

	r = (int)(256 * clamp(color.v[0], 0.0, 0.999));
	g = (int)(256 * clamp(color.v[1], 0.0, 0.999));
	b = (int)(256 * clamp(color.v[2], 0.0, 0.999));
	if (color.col.r > 255)
		color.col.r = 255;
	if (color.col.g > 255)
		color.col.g = 255;
	if (color.col.b > 255)
		color.col.b = 255;
	return (t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = create_trgb(0, color);
}
