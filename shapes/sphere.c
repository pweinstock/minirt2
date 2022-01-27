
#include "shapes.h"
#include <math.h>

bool hit_sphere(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
	t_vec3 oc = minus_vec_vec(r.origin, object->center);
	double a = length_squared(&r.dir);
	double half_b = dot(oc, r.dir);
	double c = length_squared(&oc) - ((object->radius) * (object->radius));

	double discriminant = half_b * half_b - a * c;
	if(discriminant < 0 )// || a == 0
	{
		return FALSE;
	}
	double sqrtd = sqrt(discriminant);

	double root = (-half_b -sqrtd) / a;
	if(root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if(root < t_min || t_max < root)
		{
			return FALSE;
		}
	}
	rec->t = root;
	rec->p = at(r, rec->t - 0.001);
	t_vec3 outward_normal = division( minus_vec_vec(rec->p, object->center), object->radius);
	set_face_normal(rec, r, outward_normal);
	rec->material = &object->mat;
	return TRUE;
}
