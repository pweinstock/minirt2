#include "cam.h"

t_ray get_ray(t_camera cam, double s, double t)
{
	return set_ray(cam.origin, minus_vec_vec(plus_vec_vec(plus_vec_vec(cam.lower_left_corner, multiply_vec_doub(cam.horizontal, s)), multiply_vec_doub(cam.vertical, t)), cam.origin));
}