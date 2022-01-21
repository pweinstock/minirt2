#include "t_vec3.h"

t_vec3 unit_vector(t_vec3 v)
{
	return division(v, length(&v));
}