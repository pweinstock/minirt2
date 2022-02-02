#include "cam.h"
#include <math.h>
#include "../libmath/my_math.h"
#include "../libvec/t_vec3.h"
#include<stdio.h>

t_camera *set_cam(t_vec3 origin, t_vec3 orientation, int degrees)
{
	t_camera *cam;
	cam = (t_camera *)malloc(sizeof(t_camera));
	cam->origin = origin;
	(void)orientation;
	t_vec3 lookat = setvec(0, 0, 0);
	double theta = degrees_to_radians(degrees);
	double h = tan(theta/2);
	double viewport_height = 2 * h;
	double viewport_width = 3.0/2.0 * viewport_height;

	cam->w = unit_vector(minus_vec_vec(cam->origin, lookat));
	cam->u = unit_vector(cross(setvec(0,1,0), cam->w));
	cam->v = cross(cam->w, cam->u);

	double focus_dist = 10;
	double aperture = 2;
	cam->horizontal = multiply_vec_doub(cam->u, focus_dist * viewport_width);
	cam->vertical = multiply_vec_doub(cam->v, focus_dist * viewport_height);
	cam->lower_left_corner = minus_vec_vec(minus_vec_vec(minus_vec_vec(cam->origin, division(cam->horizontal, 2)), division(cam->vertical, 2)), multiply_vec_doub(cam->w, focus_dist));

	cam->lens_radius = aperture / 2;
	return cam;
}