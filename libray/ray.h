#ifndef	 RAY_H
# define	RAY_H

#include "../libvec/t_vec3.h"

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 dir;
} t_ray;

t_vec3 at(t_ray p, double t);
t_ray set_ray(t_vec3 origin, t_vec3 dir);

#endif