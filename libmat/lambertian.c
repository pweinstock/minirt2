#include "mat.h"

bool scatter_lambertian(t_ray in, struct s_hit_record rec, t_vec3 *attenuation, t_ray *scattered)
{
	// t_vec3 scatter_direction;

	// t_vec3 inv_strahl = invert(in.dir);
	// t_vec3 fl_ri = unit_vector(rec.normal);
	// scatter_direction = minus_vec_vec(multiply_vec_doub(multiply_vec_doub(fl_ri, 2.0), dot(fl_ri, inv_strahl)), inv_strahl);

	// scatter_direction = plus_vec_vec(rec.normal, random_unit_vector());
	t_vec3 scatter_direction = rec.normal;


	if(near_zero(scatter_direction))
		scatter_direction = rec.normal;
	transmitted(&scattered->origin, &rec.p);
	transmitted(&scattered->dir, &scatter_direction);
	transmitted(attenuation, &rec.material->albedo);
	(void)in;
	return TRUE;
}

// t_vec   ReflectRay(t_vec R, t_vec N) // N=normierte von center vum schnitt punkt R invertierte strhlen richtung
// {
//     return (vec_sub(vec_mult(vec_mult(N, 2), dot(N, R)), R));
// }
