#include "ray.h"

t_vec3 at(t_ray p, double t)
{
	return plus_vec_vec(multiply_vec_doub(p.dir, t), p.origin);
}