#include "mat.h"

bool scatter_lambertian(t_ray in, struct s_hit_record rec, t_vec3 *attenuation, t_ray *scattered)
{
	// t_vec3 scatter_direction = plus_vec_vec(rec.normal, random_unit_vector());
	t_vec3 scatter_direction = rec.normal;



	if(near_zero(scatter_direction))
		scatter_direction = rec.normal;
	transmitted(&scattered->origin, &rec.p);
	transmitted(&scattered->dir, &scatter_direction);
	transmitted(attenuation, &rec.material->albedo);
	return TRUE;
	(void)in;
}

// t_vec   ReflectRay(t_vec R, t_vec N) // N=normierte von center vum schnitt punkt R invertierte strhlen richtung
// {
//     return (vec_sub(vec_mult(vec_mult(N, 2), dot(N, R)), R));
// }