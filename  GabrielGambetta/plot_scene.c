/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:03:27 by pweinsto          #+#    #+#             */
/*   Updated: 2022/01/26 14:23:22 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"


int	create_trgb(int t, t_color color)
{
	if (color.r > 255) /// in der specular berechnung ändern;
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	return (t << 24 | (int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	//*(unsigned int *)dst = color;
	*(unsigned int *)dst = create_trgb(0, color);
}
