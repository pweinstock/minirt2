#include "cam.h"
#include "../world.h"
#include <math.h>

void set_cam(t_camera *cam, t_vec3 origin, t_vec3 orientation, double degrees)
{
	cam->origin = origin;
	cam->degrees = degrees;
	cam->orientation = orientation;

	double theta = degrees_to_radians(cam->degrees);
	double h = tan(theta/2);
	double viewport_height = 2 * h;
	double viewport_width = (double)WIDTH/HIGHT * viewport_height;

	cam->w = unit_vector(minus_vec_vec(cam->origin, orientation));
	cam->u = unit_vector(cross(setvec(0,1,0), cam->w));
	cam->v = cross(cam->w, cam->u);

	double focus_dist = 1;
	double aperture = 2;
	cam->horizontal = multiply_vec_doub(cam->u, focus_dist * viewport_width);
	cam->vertical = multiply_vec_doub(cam->v, focus_dist * viewport_height);
	cam->lower_left_corner = minus_vec_vec(minus_vec_vec(minus_vec_vec(cam->origin, division(cam->horizontal, 2)), division(cam->vertical, 2)), multiply_vec_doub(cam->w, focus_dist));

	cam->lens_radius = aperture / 2;
}