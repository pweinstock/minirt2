
#include "shapes.h"
#include "../libvec/t_vec3.h"
#include <math.h>
#include <stdio.h>

void ratio_number(t_object *object, double *cos_a, double *cos_b, double *sin_a, double *sin_b)
{
    //a = Y-achse b= x-achse

        *sin_a = -object->orientation.v[0]/sqrt(object->orientation.v[0] * object->orientation.v[0] + object->orientation.v[2] * object->orientation.v[2]);

        // *sin_b = object->orientation.v[1]/sqrt(object->orientation.v[1] * object->orientation.v[1] + object->orientation.v[2] * object->orientation.v[2]);
        *sin_b = object->orientation.v[1]/length(&object->orientation);
        *cos_a = -object->orientation.v[2]/sqrt(object->orientation.v[0] * object->orientation.v[0] + object->orientation.v[2] * object->orientation.v[2]);
        // *cos_b = object->orientation.v[2]/sqrt(object->orientation.v[1] * object->orientation.v[1] + object->orientation.v[2] * object->orientation.v[2]);
        *cos_b = sqrt(object->orientation.v[0] * object->orientation.v[0] + object->orientation.v[2] * object->orientation.v[2]) / length(&object->orientation);
    dprintf(2, "cos_b %f cos_a %f sin_b %f sin_a %f\n", *cos_b, *cos_a, *sin_b, *sin_a);


    if (*sin_a != *sin_a)
        *sin_a = 0;
    if (*sin_b != *sin_b)
        *sin_b = 0;
    if (*cos_a != *cos_a)
        *cos_a = 1;
    if (*cos_b != *cos_b)
        *cos_b = 1;
    dprintf(2, "cos_b %f cos_a %f sin_b %f sin_a %f\n", *cos_b, *cos_a, *sin_b, *sin_a);
}

void initmatrix(t_object *object)
{
    double cos_a;
    double cos_b;
    double sin_a;
    double sin_b;

    ratio_number(object, &cos_a, &cos_b, &sin_a, &sin_b);

    object->matrix_to_global[0][0] = cos_a;
    object->matrix_to_global[0][1] = sin_a * sin_b;
    object->matrix_to_global[0][2] = sin_a * cos_b;

    object->matrix_to_global[1][0] = 0;
    object->matrix_to_global[1][1] = cos_b;
    object->matrix_to_global[1][2] = -sin_b;

    object->matrix_to_global[2][0] = -sin_a;
    object->matrix_to_global[2][1] = sin_b * cos_a;
    object->matrix_to_global[2][2] = cos_a * cos_b;

    object->matrix_to_global[0][3] = object->center.v[0];
    object->matrix_to_global[1][3] = object->center.v[1];
    object->matrix_to_global[2][3] = object->center.v[2];
}

void   matrix_transponieren(t_object *object)
{

    object->matrix_to_local[0][0] = object->matrix_to_global[0][0];
    object->matrix_to_local[0][1] = object->matrix_to_global[1][0];
    object->matrix_to_local[0][2] = object->matrix_to_global[2][0];

    object->matrix_to_local[1][0] = object->matrix_to_global[0][1];
    object->matrix_to_local[1][1] = object->matrix_to_global[1][1];
    object->matrix_to_local[1][2] = object->matrix_to_global[2][1];

    object->matrix_to_local[2][0] = object->matrix_to_global[0][2];
    object->matrix_to_local[2][1] = object->matrix_to_global[1][2];
    object->matrix_to_local[2][2] = object->matrix_to_global[2][2];

    object->matrix_to_local[0][3] = object->matrix_to_global[0][3];
    object->matrix_to_local[1][3] = object->matrix_to_global[1][3];
    object->matrix_to_local[2][3] = object->matrix_to_global[2][3];

}

t_vec3 vec_to_global(t_object* object, t_vec3 *p)
{
    t_vec3 ret;

    ret.v[0] = object->matrix_to_global[0][0] * p->v[0] +  object->matrix_to_global[0][1] * p->v[1] +  object->matrix_to_global[0][2] * p->v[2] + object->matrix_to_global[0][3];

    ret.v[1] = object->matrix_to_global[1][0] * p->v[0] +  object->matrix_to_global[1][1] * p->v[1] +  object->matrix_to_global[1][2] * p->v[2] + object->matrix_to_global[1][3];

    ret.v[2] = object->matrix_to_global[2][0] * p->v[0] +  object->matrix_to_global[2][1] * p->v[1] +  object->matrix_to_global[2][2] * p->v[2] + object->matrix_to_global[2][3];

    return ret;
}

t_vec3 vec_to_local(t_object* object, t_vec3 *tmp)
{
    t_vec3 ret;
    t_vec3 p;
    p.v[0] = tmp->v[0] - object->matrix_to_local[0][3];
    p.v[1] = tmp->v[1] - object->matrix_to_local[1][3];
    p.v[2] = tmp->v[2] - object->matrix_to_local[2][3];
    // dprintf(2, "p.v %f tmp %f obj %f\n", p.v[0], tmp->v[0], object->matrix_to_local[0][3]);



    ret.v[0] = object->matrix_to_local[0][0] * p.v[0] +  object->matrix_to_local[0][1] * p.v[1] +  object->matrix_to_local[0][2] * p.v[2];

    ret.v[1] = object->matrix_to_local[1][0] * p.v[0] +  object->matrix_to_local[1][1] * p.v[1] +  object->matrix_to_local[1][2] * p.v[2];

    ret.v[2] = object->matrix_to_local[2][0] * p.v[0] +  object->matrix_to_local[2][1] * p.v[1] +  object->matrix_to_local[2][2] * p.v[2];

    return ret;
}


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
    r.dir = vec_to_local(object, &r.dir);
    // dprintf(2, "r.dir %f r.dir %f\n", r.dir.v[0], r.dir.v[1]);
    r.origin = vec_to_local(object, &r.origin);

    a = r.dir.v[0] * r.dir.v[0] + r.dir.v[1] * r.dir.v[1];
    // dprintf(2, "a %f r.dir %f r.dir %f\n", a, r.dir.v[0], r.dir.v[1]);

    b = 2 * (r.origin.v[0]*r.dir.v[0] + r.origin.v[1]*r.dir.v[1]);
    c = r.origin.v[0] * r.origin.v[0] + r.origin.v[1] * r.origin.v[1] - object->radius * object->radius;

    sqrt_ret = sqrt(b * b - 4 * a * c);
    // dprintf(2, "sqrt_ret %f a %f b %f c %f\n", sqrt_ret, a, b, c);
    if(sqrt_ret != sqrt_ret)
        return FALSE;

    x1 = (-b + sqrt_ret) / (2 * a);
    x2 = (-b - sqrt_ret) / (2 * a);

    if(x1 < 0 && x2 < 0)
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
    if (hit_circular_plane(r, object, t_min, x2, rec))
    {
        return TRUE;
    }
    if(x2 >= t_max || x2 < t_min)
        return FALSE;
    col = at(r, x2);
    rec->t = x2;
	rec->p = vec_to_global(object, &col);
	t_vec3 outward_normal = division(col, object->radius);
	set_face_normal(rec, r, outward_normal);
    rec->normal = vec_to_global(object, &rec->normal);
	rec->material = &object->mat;
	return TRUE;
}
