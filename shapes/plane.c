#include "shapes.h"
#include <math.h>
#include <stdio.h>


bool hit_plane(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
	// t_vec3 test = multiply_vec_vec(object->center,object->orientation);
	double d = dot(object->center,object->orientation); //abstand urspring flaeche
	// double d = length(&object->center) * length(&object->orientation);
	// if(s != d)

	double oben = d - dot(object->orientation, r.origin);
	if (oben == 0.0) // unendlich
		return FALSE;
	double unten = dot(object->orientation, r.dir);
	if (unten == 0.0)
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
	t_vec3 outward_normal = object->orientation;
	set_face_normal(rec, r, outward_normal);
	rec->material = &object->mat;
	return TRUE;

}

bool hit_circular_plane(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
	double abstand;
	(void)rec;
	bool ret;

	ret = FALSE;
	if(hit_plane(r, object, t_min, t_max, rec))
	{
		abstand = sqrt( rec->p.v[0] * rec->p.v[0] + rec->p.v[1] * rec->p.v[1] );
		if ( abstand <= object->radius && rec->t < t_max)
			return (TRUE);
	}
	return (FALSE);
}

bool hit_cone_plane(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
	t_hit_record tmp_rec;
	t_object tmp_object;
	t_vec3 local_col;
	bool ret;

	ret = FALSE;

	tmp_object.center = setvec(0,0,object->hight/2);
	tmp_object.orientation = setvec(0,0,1);
	tmp_object.radius = object->radius;
	tmp_object.mat = object->mat;

	if(hit_circular_plane(r, &tmp_object, t_min, t_max, &tmp_rec))
	{
		transphere(rec, &tmp_rec);
		local_col = at(r, rec->t);
		rec->p = vec_to_global(object, &rec->p);
		rec->normal = vec_to_global(object, &rec->normal);
		t_max = rec->t;
		rec->material = &object->mat;
		ret = TRUE;
	}

	// tmp_object.center = setvec(0,0,-object->hight/2);
	// tmp_object.orientation = setvec(0,0,-1);

	// if(hit_circular_plane(r, &tmp_object, t_min, t_max, &tmp_rec))
	// {
	// 	transphere(rec, &tmp_rec);
	// 	local_col = at(r, tmp_rec.t);
	// 	rec->p = vec_to_global(object, &local_col);
	// 	rec->normal = vec_to_global(object, &rec->normal);
	// 	t_max = rec->t;
	// 	rec->material = &object->mat;
	// 	ret = TRUE;
	// }

	return ret;
}

bool hit_zylinder_planes(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
	t_hit_record tmp_rec;
	t_object tmp_object;
	t_vec3 local_col;
	bool ret;

	ret = FALSE;

	tmp_object.center = setvec(0,0,object->hight/2);
	tmp_object.orientation = setvec(0,0,1);
	tmp_object.radius = object->radius;
	tmp_object.mat = object->mat;

	if(hit_circular_plane(r, &tmp_object, t_min, t_max, &tmp_rec))
	{
		transphere(rec, &tmp_rec);
		local_col = at(r, rec->t);
		rec->p = vec_to_global(object, &local_col);
		rec->normal = vec_to_global(object, &rec->normal);
		rec->normal = division(rec->normal, object->radius);
		t_max = rec->t;
		rec->material = &object->mat;
		ret = TRUE;
	}

	tmp_object.center = setvec(0,0,-object->hight/2);
	tmp_object.orientation = setvec(0,0,-1);

	if(hit_circular_plane(r, &tmp_object, t_min, t_max, &tmp_rec))
	{
		transphere(rec, &tmp_rec);
		local_col = at(r, rec->t);
		rec->p = vec_to_global(object, &local_col);
		rec->normal = vec_to_global(object, &rec->normal);
		rec->normal = division(rec->normal, object->radius);
		rec->material = &object->mat;
		ret = TRUE;
	}

	return ret;
}