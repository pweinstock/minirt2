/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:13:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:19:11 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	plus_vec_vec(t_vec3 u, t_vec3 v)
{
	return (setvec(u.v[0] + v.v[0], u.v[1] + v.v[1], u.v[2] + v.v[2]));
}

t_vec3	plus_vec_doub(t_vec3 u, double v)
{
	return (setvec(u.v[0] + v, u.v[1] + v, u.v[2] + v));
}

t_vec3	plus_vec_int(t_vec3 u, int value)
{
	return (setvec(u.v[0] + value, u.v[1] + value, u.v[2] + value));
}
