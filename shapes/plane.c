#include "shapes.h"
#include <math.h>
#include <stdio.h>

bool hit_plane(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
	float denom = dot(object->orientation, r.dir);
	if (denom > 1e-6)
	{

		t_vec3 p = minus_vec_vec(object->center, r.origin);
		double root = dot(p, object->orientation);

		// dprintf(2,"%f %f %f %f\n", root, rec->t, t_min, t_max);
		if(root > rec->t || t_min > root || t_max < root)
		{
			return FALSE;
		}

		rec->t = root;
		rec->p = at(r, rec->t);
		// t_vec3 outward_normal = division(minus_vec_vec(rec->p, object->center), object->radius);
		// set_face_normal(rec, r, outward_normal);
		rec->front_face = 0;
		rec->material = &object->mat;
		return TRUE;
	}
	return FALSE;
}
