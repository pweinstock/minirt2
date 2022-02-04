/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:03:28 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/02 13:29:49 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "../libvec/t_vec3.h"
#include <math.h>
#include <stdio.h>

t_vec3	uni_vec_to_global(t_object *object, t_vec3 *p)
{
	t_vec3	r;
	double	(*m)[3][4];

	m = &object->matrix_to_global;
	r.v[0] = (*m)[0][0] * p->v[0] + (*m)[0][1] * p->v[1] + (*m)[0][2] * p->v[2];
	r.v[1] = (*m)[1][0] * p->v[0] + (*m)[1][1] * p->v[1] + (*m)[1][2] * p->v[2];
	r.v[2] = (*m)[2][0] * p->v[0] + (*m)[2][1] * p->v[1] + (*m)[2][2] * p->v[2];
	return (r);
}

t_vec3	uni_vec_to_local(t_object *object, t_vec3 *p)
{
	t_vec3	r;
	double	(*m)[3][4];

	m = &object->matrix_to_local;
	r.v[0] = (*m)[0][0] * p->v[0] + (*m)[0][1] * p->v[1] + (*m)[0][2] * p->v[2];
	r.v[1] = (*m)[1][0] * p->v[0] + (*m)[1][1] * p->v[1] + (*m)[1][2] * p->v[2];
	r.v[2] = (*m)[2][0] * p->v[0] + (*m)[2][1] * p->v[1] + (*m)[2][2] * p->v[2];
	return (r);
}

t_vec3	vec_to_global(t_object *object, t_vec3 *p)
{
	t_vec3	r;
	double	(*m)[3][4];

	m = &object->matrix_to_local;
	r = uni_vec_to_global(object, p);
	r.v[0] += (*m)[0][3];
	r.v[1] += (*m)[1][3];
	r.v[2] += (*m)[2][3];
	return (r);
}

t_vec3	vec_to_local(t_object *object, t_vec3 *tmp)
{
	t_vec3	p;
	double	(*m)[3][4];

	m = &object->matrix_to_local;
	p.v[0] = tmp->v[0] - (*m)[0][3];
	p.v[1] = tmp->v[1] - (*m)[1][3];
	p.v[2] = tmp->v[2] - (*m)[2][3];
	return (uni_vec_to_local(object, &p));
}
