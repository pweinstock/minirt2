#ifndef	 WORLD_H
# define	WORLD_H

#include <stdint.h>
#include <stdlib.h>
#include "libcam/cam.h"
// #include "libmat/material.h"
#include "libmath/mymath.h"
#include "libvec/t_vec3.h"
#include "shapes/shapes.h"
#include <fcntl.h>
#include "minilibx_macos/mlx.h"

#ifndef WIDTH
#define WIDTH 200
#endif

#ifndef HIGHT
#define HIGHT 200
#endif

#ifndef SAMPLES_PER_PIXEL
#define SAMPLES_PER_PIXEL 10
#endif

#ifndef MAX_DEPTH
#define MAX_DEPTH 2
#endif

enum light_typ
{
	AMBIENT,
	POINT,
	DIRECTIONAL
};

typedef struct s_light
{
	int		type;
	double	intensity;
	t_vec3	position;
	t_vec3	direction;
	t_color	color;
}				t_light;

typedef struct s_world
{
    t_object *hittabels;
	size_t	n_hittabels;
    t_camera *cam;
	size_t n_cam;
	t_light		*lights;
	size_t		n_lights;
	void	*mlx;
	void	*mlx_win;
	t_color backround;
	char	*name;
}               t_world;

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);
int	create_trgb(int t, t_color color);
t_bool hit(t_ray r, t_world *world, double t_max, t_hit_record* rec);
void ray_average_color(t_world* world, t_camera* cam ,int x, int y);
double ComputeLightning(t_world *world, t_hit_record* rec, t_ray* ray);
void write_color(t_vec3 color, int fd);



#endif

