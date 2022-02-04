/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:13:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:21:38 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"
#include "math.h"

double	length_squared(t_vec3 *p)
{
	return (p->v[0] * p->v[0] + p->v[1] * p->v[1] + p->v[2] * p->v[2]);
}

double	length(t_vec3 *point)
{
	return (sqrt(length_squared(point)));
}
