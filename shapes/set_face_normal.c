#include "shapes.h"

void set_face_normal( t_hit_record *rec, t_ray r, t_vec3 outward_nornal)
{
	rec->front_face = dot(r.dir, outward_nornal) < 0;
	if (rec->front_face)
	{
		rec->normal = outward_nornal;
	}
	else
	{
		rec->normal = invert(outward_nornal);
	}
}