/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:54:53 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/09 17:10:54 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 WORLD_H
# define	WORLD_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include "libcam/cam.h"
# include "libmath/mymath.h"
# include "libvec/t_vec3.h"
# include "shapes/shapes.h"
# include <fcntl.h>
# include ".minilibx_macos/mlx.h"
# include <pthread.h>

# ifndef WIDTH
#  define WIDTH 2560
# endif

# ifndef HIGHT
#  define HIGHT 1440
# endif

# ifndef MLX_HIGHT
#  define MLX_HIGHT 288
//#  define MLX_HIGHT (HIGHT/4)
# endif

# ifndef MLX_WIDTH
#  define MLX_WIDTH 512
//#  define MLX_WIDTH (WIDTH/4)
# endif

# ifndef SAMPLES_PER_PIXEL
#  define SAMPLES_PER_PIXEL 1
# endif

# ifndef MLX_SAMPLES_PER_PIXEL
#  define MLX_SAMPLES_PER_PIXEL 1
# endif

# ifndef MAX_DEPTH
#  define MAX_DEPTH 3
# endif

# ifndef MLX_MAX_DEPTH
#  define MLX_MAX_DEPTH 2
# endif

# ifndef MLX_THREADS
#  define MLX_THREADS 11
# endif

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_P 35
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124

enum e_light_typ
{
	AMBIENT,
	POINT,
	DIRECTIONAL
};

typedef struct s_from_to
{
	int	from;
	int	to;
	int	current;
}	t_from_to;

typedef struct s_picture_part
{
	t_from_to	x;
	t_from_to	y;
	t_from_to	ges_y;
}	t_picture_part;

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
	t_object		*hittabels;
	size_t			n_hittabels;
	t_camera		cam;
	t_light			*lights;
	size_t			n_lights;
	void			*mlx;
	void			*mlx_win;
	t_color			backround;
	char			*name;
	pthread_mutex_t	hight_mutex;
	int				picture_part_hight;
	t_bool			A_flag;
	t_bool			L_flag;
	t_bool			C_flag;
	double			r;
	double			g;
	double			b;
}		t_world;

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color);
int		create_trgb(int t, t_color color);
t_bool	hit(t_ray r, t_world *world, double t_max, t_hit_record *rec);
t_color	ray_average_color(t_world *world, t_picture_part *part,
			size_t samples_per_pixel, int max_depth);
t_color	ComputeLightning(t_world *world, t_hit_record *rec, t_ray *ray);
void	write_color(t_vec3 color, int fd);
void	ft_make_bmp(int *arr);
int		ft_inden(int key, int x, int y, t_world *world);
int		key_hook(int keycode, t_world *world);
int		ft_free_all(t_world *world);
void	count_pixel(t_world *w, t_picture_part *part,
			int *arr, t_data *img);
void	ft_make_mlx_imiges(t_world *world);

#endif