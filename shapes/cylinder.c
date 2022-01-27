#include "shapes.h"
#include "../libvec/t_vec3.h"
#include <math.h>
#include <stdio.h>

bool hit_cylinder(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
    double a;
    double b;
    double c;
    double sqrt_ret;
    double x1;
    double x2;
    t_vec3 col;
    // dprintf(2, "r.dir %f r.dir %f\n", r.dir.v[0], r.dir.v[1]);
    r.dir = unit_vector(vec_to_local(object, &r.dir));
    // dprintf(2, "r.dir %f r.dir %f\n", r.dir.v[0], r.dir.v[1]);
    r.origin = vec_to_local(object, &r.origin);

    a = r.dir.v[0] * r.dir.v[0] + r.dir.v[1] * r.dir.v[1];
    b = 2 * (r.origin.v[0]*r.dir.v[0] + r.origin.v[1]*r.dir.v[1]);
    c = r.origin.v[0] * r.origin.v[0] + r.origin.v[1] * r.origin.v[1] - object->radius * object->radius;

    sqrt_ret = sqrt(b * b - 4 * a * c);
	// dprintf(2, "%f %f\n", sqrt_ret, a);
    if(sqrt_ret != sqrt_ret || sqrt_ret == 0 || a == 0)
        return FALSE;
    // dprintf(2, "sqrt_ret %f a %f b %f c %f\n", sqrt_ret, a, b, c);

    x1 = (-b + sqrt_ret) / (2 * a);
    x2 = (-b - sqrt_ret) / (2 * a);

    if((x1 < 0 || x1 != x1) && (x2 < 0 || x2 != x2))
        return FALSE;

    if(fabs(at(r, x2).v[2]) > (object->hight / 2))
    {
        x2 = t_max;
    }
    if(fabs(at(r, x1).v[2]) > (object->hight / 2))
    {
        x1 = t_max;
    }
    if (x1 < x2)
        x2 = x1;
    if (hit_zylinder_planes(r, object, t_min, x2, rec))
    {
        return TRUE;
    }
    if(x2 >= t_max -0.001 || x2 < t_min)
        return FALSE;
    col = at(r, x2);
    rec->t = x2;
	rec->p = vec_to_global(object, &col);
	t_vec3 outward_normal = division(setvec(col.v[0],col.v[1],0), object->radius);
	set_face_normal(rec, r, outward_normal);
    rec->normal = vec_to_global(object, &rec->normal);
	rec->normal =  unit_vector(rec->normal);
		// dprintf(2, "%f %f %f\n",rec->normal.v[0],rec->normal.v[1] , rec->normal.v[2]);
	rec->material = &object->mat;
	return TRUE;
}
