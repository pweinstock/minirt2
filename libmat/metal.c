#include "mat.h"

bool scatter_metal(t_ray in, struct s_hit_record rec, t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3 reflected;
	reflected = reflect(unit_vector(in.dir), rec.normal);
	transmitted(&scattered->origin, &rec.p);
	t_vec3 scatt_tmp;
	scatt_tmp = plus_vec_vec(reflected, multiply_vec_doub(random_in_unit_sphere(), rec.material->fuzz));
	transmitted(&scattered->dir, &scatt_tmp);
	transmitted(attenuation, &rec.material->albedo);
	return(dot(scattered->dir, rec.normal) > 0);
}