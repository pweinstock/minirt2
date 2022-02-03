/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:13:08 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/03 12:07:47 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 T_VEC3_H
# define	T_VEC3_H

# include <stdint.h>
# include <stdlib.h>

typedef enum bol
{
	FALSE,
	TRUE
}	t_bool;

struct s_color
{
	double	r;
	double	g;
	double	b;
};

struct s_vec
{
	double	x;
	double	y;
	double	z;
};

typedef union s_vec3
{
	double			v[3];
	struct s_vec	vec;
	struct s_color	col;
} t_vec3,	t_color;

t_vec3	cross(t_vec3 u, t_vec3 v);
t_vec3	division(t_vec3 v, double t);
double	dot(t_vec3 u, t_vec3 v);
t_vec3	invert(t_vec3 v);
double	length_squared(t_vec3 *point);
double	length(t_vec3 *point);
t_vec3	minus_vec_vec(t_vec3 u, t_vec3 v);
t_vec3	minus_vec_doub(t_vec3 u, double t);
t_vec3	multiply_vec_doub(t_vec3 v, double t);
t_vec3	multiply_vec_vec(t_vec3 v, t_vec3 u);
t_vec3	plus_vec_vec(t_vec3 u, t_vec3 v);
t_vec3	plus_vec_doub(t_vec3 u, double v);
t_vec3	plus_vec_int(t_vec3 u, int value);
double	random_double(void);
double	random_doublem(double min, double max);
t_vec3	random_vec3(double min, double max);
t_vec3	random_in_unit_sphere(void);
t_vec3	random_in_hemispere(const t_vec3 normal);
t_vec3	random_unit_vector(void);
t_vec3	setvec(double x, double y, double z);
void	transmitted(t_vec3 *u, t_vec3 *v);
t_vec3	unit_vector(t_vec3 v);

#endif