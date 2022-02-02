#include "mat.h"

t_vec3 t_reflect(t_vec3 v, t_vec3 n)
{
	return (minus_vec_vec(v, multiply_vec_doub(multiply_vec_doub(n, dot(v, n)), 2)));
}

bool	scatter_dielectric(t_ray in, struct s_hit_record rec, t_vec3 *attenuation, t_ray *scattered)
{
	double	refraction_ratio;
	double	cos_theta;
	double	sin_theta;
	t_vec3	unit_direction;
	t_vec3	direction;
	bool	cannot_retract;

	attenuation->v[0] = 1.0;
	attenuation->v[1] = 1.0;
	attenuation->v[2] = 1.0;
	if (rec.front_face)
		refraction_ratio = (1.0 / rec.material->ir);
	else
		refraction_ratio = rec.material->ir;
	unit_direction = unit_vector(in.dir);
	cos_theta = fmin(dot(invert(unit_direction), rec.normal), 1.0);
	sin_theta = sqrt(1.0 - pow(cos_theta, 2));
	cannot_retract = refraction_ratio * sin_theta > 1.0;
	if (cannot_retract || reflectance(cos_theta, refraction_ratio) > random_double())
		direction = t_reflect(unit_direction, rec.normal);
	else
		direction = refract(unit_direction, rec.normal, refraction_ratio);
	transmitted(&scattered->origin, &rec.p);
	transmitted(&scattered->dir, &direction);
	return (TRUE);
}
