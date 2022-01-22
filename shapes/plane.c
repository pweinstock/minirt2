#include "shapes.h"
#include <math.h>
#include <stdio.h>

bool hit_plane(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{


	double d = dot(object->center,object->orientation); //abstand urspring flaeche

	double oben = d - dot(object->orientation, r.origin);
	// if (oben == 0.0) // unendlich 
	// 	return FALSE;
	double unten = dot(r.dir, object->orientation);

	if (unten == 0.00)
		return FALSE;

	double ret = oben / unten;


	// dprintf(2, "%f min %f max %f rec.t %f strahl %f %f %f\n", ret ,t_min, t_max, rec->t, r.origin.v[0], r.origin.v[1], r.origin.v[2]);
	if(ret < t_min || ret > t_max)
	{
		// dprintf(2, "False\n");
		return FALSE;
	}
	rec->t = ret;
	rec->p = at(r, rec->t);
	// dprintf(2, "kolisions point %f %f %f", rec->p.v[0], rec->p.v[1], rec->p.v[2]);
	t_vec3 outward_normal = minus_vec_vec(object->orientation, object->center);
	set_face_normal(rec, r, outward_normal);
	// rec->front_face = FALSE;
	rec->material = &object->mat;
	// dprintf(2, "true");
	return TRUE;

}
