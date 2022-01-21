#include "mat.h"

bool scatter_dielectric(t_ray in, struct s_hit_record rec, t_vec3 *attenuation, t_ray *scattered)
{
	attenuation->v[0] = 1.0;
	attenuation->v[1] = 1.0;
	attenuation->v[2] = 1.0;
	double refraction_ratio;
	if (rec.front_face)
		refraction_ratio = (1.0/rec.material->ir);
	else
		refraction_ratio = rec.material->ir;

	t_vec3 unit_direction;
	unit_direction = unit_vector(in.dir);
	double cos_theta;
	cos_theta = fmin(dot(invert(unit_direction), rec.normal), 1.0);
	double sin_theta;
	sin_theta = sqrt(1.0 -  cos_theta*cos_theta);

	bool cannot_retract = refraction_ratio * sin_theta > 1.0;
	t_vec3 direction;
	if(cannot_retract || reflectance(cos_theta, refraction_ratio) > random_double())
		direction = reflect(unit_direction, rec.normal);
	else
		direction = refract(unit_direction, rec.normal, refraction_ratio);
	transmitted(&scattered->origin, &rec.p);
	transmitted(&scattered->dir, &direction);
	return TRUE;
}