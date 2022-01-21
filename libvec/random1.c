#include "t_vec3.h"

t_vec3 random_in_unit_sphere()
{
    while (TRUE)
    {
        t_vec3 p = random_vec3(-1,1);
        if (length_squared(&p) >= 1)
			continue;
        return p;
    }
}

t_vec3 random_in_hemispere(const t_vec3 normal)
{
    t_vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0)
        return in_unit_sphere;
    else
        return invert(in_unit_sphere);
}

t_vec3 random_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}