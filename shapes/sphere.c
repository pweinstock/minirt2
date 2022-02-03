/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:17:31 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/03 11:41:28 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include <math.h>

t_bool	hit_sphere(t_ray r, t_object *object, double t_max, t_hit_record *rec)
{
	t_vec3	oc;
	double	discriminant_sqrtd;
	double	a_hb_c[3];
	double	root;

	oc = minus_vec_vec(r.origin, object->center);
	a_hb_c[0] = length_squared(&r.dir);
	a_hb_c[1] = dot(oc, r.dir);
	a_hb_c[2] = length_squared(&oc) - ((object->radius) * (object->radius));
	discriminant_sqrtd = pow(a_hb_c[1], 2) - a_hb_c[0] * a_hb_c[2];
	if (discriminant_sqrtd < 0)
		return (FALSE);
	discriminant_sqrtd = sqrt(discriminant_sqrtd);
	root = (-(a_hb_c[1] + discriminant_sqrtd)) / a_hb_c[0];
	if (root < T_MIN || t_max < root)
	{
		root = (-a_hb_c[1] + discriminant_sqrtd) / a_hb_c[0];
		if (root < T_MIN || t_max < root)
			return (FALSE);
	}
	fill_t_p(rec, root, r);
	set_face_normal(rec, r,
		division(minus_vec_vec(rec->p, object->center), object->radius));
	rec->material = &object->mat;
	return (TRUE);
}
