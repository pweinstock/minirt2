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
	rec->material = &object->mat;
	return TRUE;

}

bool hit_circular_plane(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
	t_hit_record tmp_rec;
	t_object tmp_object;
	double abstand;
	t_vec3 local_col;
	bool ret;

	ret = FALSE;

	tmp_object.center = setvec(0,0,object->hight/2);
	tmp_object.orientation = setvec(0,0,1);
	tmp_object.mat = object->mat;

	if(hit_plane(r, &tmp_object, t_min, t_max, &tmp_rec))
	{
		abstand = sqrt( tmp_rec.p.v[0] * tmp_rec.p.v[0] + tmp_rec.p.v[1] * tmp_rec.p.v[1] );
	// dprintf(2, "abstand %f  = %f radius %f\n", length(&abstand), sqrt( tmp_rec.p.v[0] * tmp_rec.p.v[0] + tmp_rec.p.v[1] * tmp_rec.p.v[1]),  object->radius);
		if ( abstand <= object->radius && tmp_rec.t < t_max) //length(&abstand)
		{

			transphere(rec, &tmp_rec);
			local_col = at(r, tmp_rec.t);
			t_max = tmp_rec.t;
			rec->p = vec_to_global(object, &local_col);
			ret = TRUE;
		}
	}
	
	tmp_object.center = setvec(0,0,-object->hight/2);
	tmp_object.orientation = setvec(0,0,-1);

	if(hit_plane(r, &tmp_object, t_min, t_max, &tmp_rec))
	{
		abstand = sqrt( tmp_rec.p.v[0] * tmp_rec.p.v[0] + tmp_rec.p.v[1] * tmp_rec.p.v[1] );
		if ( abstand <= object->radius && tmp_rec.t < t_max)
		{
			transphere(rec, &tmp_rec);
			local_col = at(r, tmp_rec.t);
			rec->p = vec_to_global(object, &local_col);
			ret = TRUE;
		}
	}

	return ret;
}