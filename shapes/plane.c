/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:38:44 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/08 19:15:56 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include <math.h>
#include <stdio.h>

void	checkerboard(t_hit_record *p)
{
	t_vec3	coords;
	t_vec3	val;
	int		XOR;

	coords.vec.x = abs((int)floor(p->p.vec.x));
	coords.vec.y = abs((int)floor(p->p.vec.y));
	coords.vec.z = abs((int)floor(p->p.vec.z));
	
	val.vec.x = (int)coords.vec.x % 2;
	val.vec.y = (int)coords.vec.y % 2;
	val.vec.z = (int)coords.vec.z % 2;
	
	XOR = ((int)val.vec.x ^ (int)val.vec.y) ^ (int)val.vec.z;
	if (XOR)
		p->material->color = setvec(0, 0, 0);
	else
		p->material->color = setvec(1, 1, 1);
	return ;
}

t_bool	hit_plane(t_ray r, t_object *object, double t_max, t_hit_record *rec)
{
	double	d;
	double	oben;
	double	unten;
	double	ret;
	t_vec3	outward_normal;

	d = dot(object->center, object->orientation);
	oben = d - dot(object->orientation, r.origin);
	if (oben == 0.0)
		return (FALSE);
	unten = dot(object->orientation, r.dir);
	if (unten == 0.0)
		return (FALSE);
	ret = oben / unten;
	if (ret < T_MIN || ret > t_max)
		return (FALSE);
	fill_t_p(rec, ret, r);
	outward_normal = object->orientation;
	set_face_normal(rec, r, outward_normal);
	rec->material = &object->mat;
	checkerboard(rec);
	return (TRUE);
}

t_bool	hit_circular_plane(t_ray r, t_object *object,
			double t_max, t_hit_record *rec)
{
	double			abstand;
	t_bool			ret;
	t_hit_record	tmp_rec;

	ret = FALSE;
	if (hit_plane(r, object, t_max, &tmp_rec))
	{
		abstand = sqrt(pow(tmp_rec.p.v[0], 2) + pow(tmp_rec.p.v[1], 2));
		if (abstand <= object->radius && tmp_rec.t < t_max)
		{
			transphere(rec, &tmp_rec);
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	hit_cone_plane(t_ray r, t_object *object,
			double t_max, t_hit_record *rec)
{
	t_object	tmp_object;
	t_bool		ret;

	ret = FALSE;
	tmp_object.center = setvec(0, 0, object->hight / 2);
	tmp_object.orientation = setvec(0, 0, 1);
	tmp_object.radius = object->radius;
	tmp_object.mat = object->mat;
	if (hit_circular_plane(r, &tmp_object, t_max, rec))
	{
		rec->material = &object->mat;
		ret = TRUE;
	}
	return (ret);
}

t_bool	hit_zylinder_planes(t_ray r, t_object *object,
			double t_max, t_hit_record *rec)
{
	t_object	tmp_object;
	t_bool		ret;
	int			i;

	i = 2;
	ret = FALSE;
	tmp_object.center = setvec(0, 0, object->hight / 2);
	tmp_object.orientation = setvec(0, 0, 1);
	tmp_object.radius = object->radius;
	tmp_object.mat = object->mat;
	while (i > 0)
	{
		if (hit_circular_plane(r, &tmp_object, t_max, rec))
		{
			t_max = rec->t;
			rec->material = &object->mat;
			ret = TRUE;
		}
		tmp_object.center = setvec(0, 0, -object->hight / 2);
		tmp_object.orientation = setvec(0, 0, -1);
		i--;
	}
	return (ret);
}
