#include "shapes.h"
#include "../libvec/t_vec3.h"
#include <math.h>
#include <stdio.h>

bool hit_cone(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec)
{
    double a;
    double b;
    double c;
	double R;
    double sqrt_ret;
    double x1;
    double x2;
    t_vec3 col;
    // dprintf(2, "r.dir %f r.dir %f\n", r.dir.v[0], r.dir.v[1]);
    r.dir = vec_to_local(object, &r.dir);
    // dprintf(2, "r.dir %f r.dir %f\n", r.dir.v[0], r.dir.v[1]);
    r.origin = vec_to_local(object, &r.origin);

	R = pow(object->radius/(object->hight/2), 2);
    a = pow(r.dir.v[0], 2) + pow(r.dir.v[1], 2) - pow(r.dir.v[2], 2) * R;
    // dprintf(2, "a %f r.dir %f r.dir %f\n", a, r.dir.v[0], r.dir.v[1]);

    b = 2 * (r.origin.v[0]*r.dir.v[0] + r.origin.v[1]*r.dir.v[1] - r.origin.v[2]*r.dir.v[2] * R);
    c = pow(r.origin.v[0],2) + pow(r.origin.v[1],2) - pow(r.origin.v[2],2) * R;

    sqrt_ret = sqrt(b * b - 4 * a * c);
    // dprintf(2, "sqrt_ret %f a %f b %f c %f\n", sqrt_ret, a, b, c);
    if(sqrt_ret != sqrt_ret || sqrt_ret == 0/* || b == 0 */|| a == 0)
        return FALSE;

    x1 = (-b + sqrt_ret) / (2 * a);
    x2 = (-b - sqrt_ret) / (2 * a);

    if(x1 < 0 && x2 < 0)
        return FALSE;

    if(at(r, x2).v[2] > (object->hight / 2) || at(r, x2).v[2] < 0)
    {
        x2 = t_max;
    }
    if(at(r, x1).v[2] > (object->hight / 2) || at(r, x1).v[2] < 0)
    {
        x1 = t_max;
    }
    if (x1 < x2)
        x2 = x1;
    if (hit_cone_plane(r, object, t_min, x2, rec))
    {
        return TRUE;
    }
    if(x2 >= t_max || x2 < t_min)
        return FALSE;
    col = at(r, x2);
    rec->t = x2;
	rec->p = vec_to_global(object, &col);
	t_vec3 outward_normal = division(setvec(col.v[0],col.v[1],(-pow(col.v[0],2)-pow(col.v[1],2))/col.v[2]), sqrt(pow(col.v[0],2) + pow(col.v[1],2)));
	// dprintf(2, "outward= %f %f %f\n",outward_normal.v[0], outward_normal.v[1], outward_normal.v[2]);
	set_face_normal(rec, r, outward_normal);
    rec->normal = vec_to_global(object, &rec->normal);
	rec->material = &object->mat;
	return TRUE;
}