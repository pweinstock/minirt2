#ifndef	 CAM_H
# define	CAM_H

# include "../libray/ray.h"

typedef struct s_camera
{
    t_vec3 origin;
    t_vec3 lower_left_corner;
    t_vec3 horizontal;
    t_vec3 vertical;
    t_vec3 u, v, w;
    double lens_radius;
}               t_camera;

t_ray get_ray(t_camera cam, double s, double t);
t_camera *set_cam(t_vec3 origin, t_vec3 orientation, int degrees);

#endif