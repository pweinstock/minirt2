#include "ray.h"

t_ray set_ray(t_vec3 origin, t_vec3 dir)
{
	t_ray ret;
	ret.origin = origin;
	ret.dir = dir;
	return ret;
}