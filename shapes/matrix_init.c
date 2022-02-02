/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:03:28 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/02 13:33:01 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "../libvec/t_vec3.h"
#include <math.h>
#include <stdio.h>

void	y_achses(t_object *object, double *cos_a, double *sin_a)
{
	t_vec3	*or;

	or = &object->orientation;
	*sin_a = -or->v[0] / sqrt(or->v[0] * or->v[0] + or->v[2] * or->v[2]);
	*cos_a = -or->v[2] / sqrt(or->v[0] * or->v[0] + or->v[2] * or->v[2]);
	if (*sin_a != *sin_a)
		*sin_a = 0;
	if (*cos_a != *cos_a)
		*cos_a = 1;
}

void	x_achses(t_object *object, double *cos_b, double *sin_b)
{
	t_vec3	*or;

	or = &object->orientation;
	*sin_b = or->v[1] / length(or);
	*cos_b = sqrt(or->v[0] * or->v[0] + or->v[2] * or->v[2]) / length(or);
	if (*sin_b != *sin_b)
		*sin_b = 0;
	if (*cos_b != *cos_b)
		*cos_b = 1;
}

void	initmatrix(t_object *object)
{
	double	cos_a;
	double	cos_b;
	double	sin_a;
	double	sin_b;

	x_achses(object, &cos_b, &sin_b);
	y_achses(object, &cos_a, &sin_a);
	object->matrix_to_global[0][0] = cos_a;
	object->matrix_to_global[0][1] = sin_a * sin_b;
	object->matrix_to_global[0][2] = sin_a * cos_b;
	object->matrix_to_global[1][0] = 0;
	object->matrix_to_global[1][1] = cos_b;
	object->matrix_to_global[1][2] = -sin_b;
	object->matrix_to_global[2][0] = -sin_a;
	object->matrix_to_global[2][1] = sin_b * cos_a;
	object->matrix_to_global[2][2] = cos_a * cos_b;
	object->matrix_to_global[0][3] = object->center.v[0];
	object->matrix_to_global[1][3] = object->center.v[1];
	object->matrix_to_global[2][3] = object->center.v[2];
}

void	matrix_transponieren(t_object *object)
{
	object->matrix_to_local[0][0] = object->matrix_to_global[0][0];
	object->matrix_to_local[0][1] = object->matrix_to_global[1][0];
	object->matrix_to_local[0][2] = object->matrix_to_global[2][0];
	object->matrix_to_local[1][0] = object->matrix_to_global[0][1];
	object->matrix_to_local[1][1] = object->matrix_to_global[1][1];
	object->matrix_to_local[1][2] = object->matrix_to_global[2][1];
	object->matrix_to_local[2][0] = object->matrix_to_global[0][2];
	object->matrix_to_local[2][1] = object->matrix_to_global[1][2];
	object->matrix_to_local[2][2] = object->matrix_to_global[2][2];
	object->matrix_to_local[0][3] = object->matrix_to_global[0][3];
	object->matrix_to_local[1][3] = object->matrix_to_global[1][3];
	object->matrix_to_local[2][3] = object->matrix_to_global[2][3];
}
