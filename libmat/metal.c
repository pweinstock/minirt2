/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:55:48 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 14:44:17 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"

t_vec3	t_reflect(t_vec3 v, t_vec3 n)
{
	return (minus_vec_vec(v,
			multiply_vec_doub(multiply_vec_doub(n, dot(v, n)), 2)));
}

t_bool	scatter_metal(t_ray in, struct s_hit_record rec,
					t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	reflected;
	t_vec3	scatt_tmp;

	reflected = t_reflect(unit_vector(in.dir), rec.normal);
	scatt_tmp = plus_vec_vec(reflected, multiply_vec_doub(
				random_in_unit_sphere(), 1 - rec.material->reflective));
	transmitted(&scattered->dir, &scatt_tmp);
	transmitted(&scattered->origin, &rec.p);
	transmitted(attenuation, &rec.material->color1);
	return (dot(scattered->dir, rec.normal) > 0);
}
