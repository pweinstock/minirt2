/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:19:01 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/01 10:19:51 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	color_multi(t_color color_old, double light)
{
	t_color	color_new;

	color_new.r = color_old.r * light;
	color_new.g = color_old.g * light;
	color_new.b = color_old.b * light;
	return (color_new);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	c;

	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return (c);
}
