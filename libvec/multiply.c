/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:13:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/08 15:40:14 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	multiply_vec_doub(t_vec3 v, double t)
{
	return (setvec(v.v[0] * t, v.v[1] * t, v.v[2] * t));
}

t_vec3	multiply_vec_vec(t_vec3 v, t_vec3 u)
{
	return (setvec(v.v[0] * u.v[0], v.v[1] * u.v[1], v.v[2] * u.v[2]));
}
