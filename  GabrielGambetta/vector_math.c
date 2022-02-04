/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:14:51 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/01 10:15:39 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	dot(t_vec a, t_vec b)
{
	double	product;

	product = a.x * b.x + a.y * b.y + a.z * b.z;
	return (product);
}

t_vec  vec_cross(t_vec first, t_vec second)
{
	t_vec  result;
	result.x = first.y * second.z - first.z * second.y;
	result.y = first.z * second.x - first.x * second.z;
	result.z = first.x * second.y - first.y * second.x;
	return (result);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vec	vec_mult(t_vec a, double b)
{
	t_vec	c;

	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
	return (c);
}

t_vec	vec_divide(t_vec a, double b)
{
	t_vec	c;

	c.x = a.x / b;
	c.y = a.y / b;
	c.z = a.z / b;
	return (c);
}

double length(t_vec a)
{
	double	length;

	length = dot(a,a);
	length = sqrt(length);
	return (length);
}