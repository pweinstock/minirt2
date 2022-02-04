#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "minilibx_macos/mlx.h"

# define AMBIENT 1
# define POINT 2
# define DIRECTIONAL 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6
# define CAP 7
# define TERM 8
# define PI 3.141592653589793

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_canvas
{
	double	width;
	double	height;
}				t_canvas;

typedef struct s_viewport
{
	double	width;
	double	height;
}				t_viewport;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}				t_vec;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}				t_ray;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct s_object
{
	int		type;
	t_vec	center;
	double	radius;
	double	height;
	t_vec	orientation;
	t_color	color;
	double	specular;
	double	reflective;
}				t_object;

typedef struct s_light
{
	int		type;
	double	intensity;
	t_color	color;
	t_vec	position;
	t_vec	direction;
}				t_light;

typedef struct s_camera
{
	t_vec	center;
	t_vec	orientation;
	double	view;

}				t_camera;

typedef struct s_count
{
	int	objects;
	int	lights;
	int	cameras;
}				t_count;

typedef struct s_scene
{
	t_object	*objects;
	t_light		*lights;
	t_camera	*cameras;
	int			object;
	int			light;
	int			camera;
	t_color		backround;
}				t_scene;

typedef struct s_intersection
{
	double	closest_t;
	t_object	closest_object;
	int	flag;
}			t_intersection;

//scene
t_scene	create_scene();

t_intersection	ClosestIntersection(t_scene scene, t_vec O, t_vec D, double t_min, double t_max);
double	ComputeLightning(t_scene scene, t_vec P, t_vec N, t_vec V, double s);
double	IntersectRaySphere(t_vec O, t_vec D, t_object sphere);
double	IntersectRayCylinder(t_vec O, t_vec D, t_object cylinder);
double	IntersectRayPlane(t_vec orig, t_vec dir, t_object sphere);
double	IntersectRayCap(t_vec orig, t_vec dir, t_object cap);
t_color	TraceRay(t_vec O, t_vec D, t_scene scene, double t_min, double t_max, int recursion_depth);

//plot_scene
void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);

//RotationMatrix
t_vec vec_to_local(t_vec center, t_vec orientation, t_vec vec);
t_vec		rotation_x(t_vec vec, double a);
t_vec		rotation_y(t_vec vec, double b);
t_vec		rotation_z(t_vec vec, double c);
t_vec		rotation(t_vec vec, double a, double b, double c);

//vec-math
double length(t_vec a);
double	dot(t_vec a, t_vec b);
t_vec  vec_cross(t_vec first, t_vec second);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_mult(t_vec a, double b);
t_vec	vec_divide(t_vec a, double b);

//color_math
t_color	color_multi(t_color color_old, double light);
t_color	color_add(t_color a, t_color b);

//init_scene
int	scene_init(char *file, t_scene *scene);

# endif