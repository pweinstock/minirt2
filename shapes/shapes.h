/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:32:52 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/09 11:42:22 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 SHAPES_H
# define	SHAPES_H

# include "../libray/ray.h"
# include "../libmat/material.h"

# ifndef T_MIN
#  define T_MIN 0.001
# endif

typedef struct s_hit_record
{
	t_vec3		p;
	t_vec3		normal;
	t_material	*material;
	double		t;
	t_bool		front_face;
}	t_hit_record;

typedef struct s_object
{
	t_bool (*hit)(t_ray r, struct s_object * object,
		double t_max, t_hit_record * rec);
	t_material	mat;
	t_vec3		center;
	double		radius;
	double		hight;
	t_vec3		orientation;
	double		matrix_to_global[3][4];
	double		matrix_to_local[3][4];
}			t_object;

void	set_face_normal( t_hit_record *rec, t_ray r, t_vec3 outward_nornal);
t_bool	hit_plane(t_ray r, t_object *object, double t_max, t_hit_record *rec);
t_bool	hit_sphere(t_ray r, t_object *object, double t_max, t_hit_record *rec);
t_bool	hit_cylinder(t_ray r, t_object *object,
			double t_max, t_hit_record *rec);
void	initmatrix(t_object *object);
void	matrix_transponieren(t_object *object);
void	transphere(t_hit_record *rec, t_hit_record *tmp);
t_bool	hit_zylinder_planes(t_ray r, t_object *object,
			double t_max, t_hit_record *rec);
t_vec3	vec_to_global(t_object *object, t_vec3 *p);
t_vec3	vec_to_local(t_object *object, t_vec3 *tmp);
t_bool	hit_cone(t_ray r, t_object *object, double t_max, t_hit_record *rec);
t_bool	hit_cone_plane(t_ray r, t_object *object,
			double t_max, t_hit_record *rec);
void	fill_t_p(t_hit_record *rec, double t, t_ray r);
t_vec3	uni_vec_to_global(t_object *object, t_vec3 *p);
t_vec3	uni_vec_to_local(t_object *object, t_vec3 *p);
void	checkerboard(t_hit_record *p, t_object *object);

#endif
