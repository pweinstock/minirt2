/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:42:24 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/03 11:41:28 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "../libvec/t_vec3.h"
#include <math.h>
#include <stdio.h>

double	hit_cone_coat(t_ray r, t_object *object, double t_max)
{
	double	a_b_c[3];
	double	R;
	double	sqrt_ret;
	double	x[2];

	R = pow(object->radius / (object->hight / 2), 2);
	a_b_c[0] = pow(r.dir.v[0], 2) + pow(r.dir.v[1], 2) - pow(r.dir.v[2], 2) * R;
	a_b_c[1] = 2 * (r.origin.v[0] * r.dir.v[0] + r.origin.v[1] * r.dir.v[1]);
	a_b_c[1] -= 2 * r.origin.v[2] * r.dir.v[2] * R;
	a_b_c[2] = pow(r.origin.v[0], 2) + pow(r.origin.v[1], 2);
	a_b_c[2] -= pow(r.origin.v[2], 2) * R;
	sqrt_ret = sqrt(a_b_c[1] * a_b_c[1] - 4 * a_b_c[0] * a_b_c[2]);
	if (sqrt_ret != sqrt_ret || sqrt_ret == 0 || a_b_c[0] == 0)
		return (t_max);
	x[0] = (-a_b_c[1] + sqrt_ret) / (2 * a_b_c[0]);
	x[1] = (-a_b_c[1] - sqrt_ret) / (2 * a_b_c[0]);
	if (at(r, x[1]).v[2] > (object->hight / 2) || at(r, x[1]).v[2] < 0
		|| (x[1] < 0 || x[1] != x[1]))
		x[1] = t_max;
	if (at(r, x[0]).v[2] > (object->hight / 2) || at(r, x[0]).v[2] < 0
		|| (x[0] < 0 || x[0] != x[0]))
		x[0] = t_max;
	if (x[0] < x[1])
		x[1] = x[0];
	return (x[1]);
}

t_bool	hit_cone(t_ray r, t_object *object, double t_max, t_hit_record *rec)
{
	double	x;
	t_vec3	outward_normal;

	r.dir = uni_vec_to_local(object, &r.dir);
	r.origin = vec_to_local(object, &r.origin);
	x = hit_cone_coat(r, object, t_max);
	if (hit_cone_plane(r, object, x, rec))
	{
		rec->p = vec_to_global(object, &rec->p);
		rec->normal = uni_vec_to_global(object, &rec->normal);
		return (TRUE);
	}
	if (x >= t_max || x < T_MIN)
		return (FALSE);
	fill_t_p(rec, x, r);
	outward_normal = division(setvec(rec->p.v[0], rec->p.v[1],
				(-pow(rec->p.v[0], 2) - pow(rec->p.v[1], 2)) / rec->p.v[2]),
			sqrt(pow(rec->p.v[0], 2) + pow(rec->p.v[1], 2)));
	rec->p = vec_to_global(object, &rec->p);
	set_face_normal(rec, r, outward_normal);
	rec->normal = uni_vec_to_global(object, &rec->normal);
	rec->material = &object->mat;
	return (TRUE);
}
