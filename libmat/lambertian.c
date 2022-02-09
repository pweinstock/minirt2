/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:58:26 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/09 11:40:35 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"
#include <stdio.h>

	// scatter_direction = plus_vec_vec(rec.normal, random_unit_vector());
t_bool	scatter_lambertian(t_ray in, struct s_hit_record rec,
			t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	scatter_direction;
	t_vec3	inv_str;
	t_vec3	fl_ri;

	inv_str = invert(in.dir);
	fl_ri = rec.normal;
	scatter_direction = minus_vec_vec(multiply_vec_doub(
				multiply_vec_doub(fl_ri, 2), dot(fl_ri, inv_str)), inv_str);
	if (near_zero(scatter_direction))
		scatter_direction = rec.normal;
	transmitted(&scattered->origin, &rec.p);
	transmitted(&scattered->dir, &scatter_direction);
	transmitted(attenuation, &rec.material->color1);
	(void)in;
	return (TRUE);
}
