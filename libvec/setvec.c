/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:12:55 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/08 18:33:40 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	setvec(double x, double y, double z)
{
	t_vec3	point;

	point.v[0] = x;
	point.v[1] = y;
	point.v[2] = z;
	return (point);
}
