#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "minilibx_macos/mlx.h"

# define AMBIENT 1
# define POINT 2
# define DIRECTIONAL 3
# define SPHERE 4
# define CYLINDER 5

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

typedef struct s_sphere
{
	int		type;
	t_vec	center;
	double		radius;
	double	height;
	t_vec	orientation;
	t_color	color;
	double	specular;
	double	reflective;
}				t_sphere;

typedef struct s_light
{
	int		type;
	double	intensity;
	t_vec	position;
	t_vec	direction;
}				t_light;

typedef struct s_scene
{
	t_sphere	*spheres;
	t_light		*lights;
	t_color		backround;
}				t_scene;

typedef struct s_intersection
{
	double	closest_t;
	t_sphere	closest_sphere;
	int	flag;
}			t_intersection;

//scene
t_scene	create_scene();

t_intersection	ClosestIntersection(t_scene scene, t_vec O, t_vec D, double t_min, double t_max);
double	ComputeLightning(t_scene scene, t_vec P, t_vec N, t_vec V, double s);
double	IntersectRaySphere(t_vec O, t_vec D, t_sphere sphere);
double	IntersectRayCylinder(t_vec O, t_vec D, t_sphere cylinder);
t_color	TraceRay(t_vec O, t_vec D, t_scene scene, double t_min, double t_max, int recursion_depth);

//plot_scene
void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);

//RotationMatrix
t_vec vec_to_local(t_vec center, t_vec orientation, t_vec vec);

//math
double length(t_vec a);

# endif