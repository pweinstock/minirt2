#ifndef	 WORLD_H
# define	WORLD_H

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "libcam/cam.h"
// #include "libmat/material.h"
#include "libmath/mymath.h"
#include "libvec/t_vec3.h"
#include "shapes/shapes.h"
#include <fcntl.h>
#include ".minilibx_macos/mlx.h"

#ifndef WIDTH
#define WIDTH 800
#endif

#ifndef HIGHT
#define HIGHT 1200
#endif

#ifndef MLX_HIGHT
#define MLX_HIGHT (HIGHT / 3)
#endif

#ifndef MLX_WIDTH
#define MLX_WIDTH (WIDTH / 3)
#endif

#ifndef SAMPLES_PER_PIXEL
#define SAMPLES_PER_PIXEL 1
#endif

#ifndef MAX_DEPTH
#define MAX_DEPTH 2
#endif

#ifndef BONUS
#define BONUS 0
#endif

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_ESC 53
#define KEY_P 35

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
	size_t current_cam;
	t_light		*lights;
	size_t		n_lights;
	void	*mlx;
	void	*mlx_win;
	t_color backround;
	char	*name;
	int		picture[HIGHT][WIDTH];
	t_bool		A_flag;
	t_bool		L_flag;
	t_bool		C_flag;
	double	r;
	double	g;
	double	b;
}               t_world;

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);
int	create_trgb(int t, t_color color);
t_bool hit(t_ray r, t_world *world, double t_max, t_hit_record* rec);
t_color	ray_average_color(t_world *world, t_camera *cam, double u, double v);
double ComputeLightning(t_world *world, t_hit_record* rec, t_ray* ray);
void write_color(t_vec3 color, int fd);
void	ft_make_bmp(int (*arr)[HIGHT][WIDTH]);
int	ft_inden(int	key, int x, int y, t_world *world);
int key_hook(int keycode, t_world *world);
int	ft_free_all(t_world *world);
void	count_pixel(t_world *world, int hight, int width, int (*arr)[HIGHT][WIDTH]);
void ft_make_mlx_imige(t_world *world);





#endif

