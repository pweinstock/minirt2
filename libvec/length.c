
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:13:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/14 12:13:37 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "math.h"

double length_squared(t_vec3 *point)
{
	return point->v[0]*point->v[0] + point->v[1]*point->v[1] + point->v[2]*point->v[2];
}

double length(t_vec3 *point)
{
	return sqrt(length_squared(point));
}