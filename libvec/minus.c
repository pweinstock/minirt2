/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:13:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:20:14 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	minus_vec_vec(t_vec3 u, t_vec3 v)
{
	return (setvec(u.v[0] - v.v[0], u.v[1] - v.v[1], u.v[2] - v.v[2]));
}

t_vec3	minus_vec_doub(t_vec3 u, double t)
{
	return (setvec(u.v[0] - t, u.v[1] - t, u.v[2] - t));
}
