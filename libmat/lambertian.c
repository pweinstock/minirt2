/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:58:26 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/02 14:23:41 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"
#include <stdio.h>

	// dprintf(2, "normal    %f %f %f \n ",rec.normal.v[0],rec.normal.v[1],rec.normal.v[2]);
	// dprintf(2, "direction %f %f %f \n ",scatter_direction.v[0],scatter_direction.v[1],scatter_direction.v[2]);
	// t_vec3 scatter_direction = rec.normal;

bool	scatter_lambertian(t_ray in, struct s_hit_record rec, t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	scatter_direction;

	t_vec3 inv_strahl = unit_vector(invert(in.dir));//invert(in.dir); //R
	t_vec3 fl_ri = rec.normal;			//N
	scatter_direction = minus_vec_vec(multiply_vec_doub(multiply_vec_doub(fl_ri, 2), dot(fl_ri, inv_strahl)), inv_strahl);

	// scatter_direction = plus_vec_vec(rec.normal, random_unit_vector());
	if (near_zero(scatter_direction))
	{
		scatter_direction = rec.normal;
	}
	transmitted(&scattered->origin, &rec.p);
	transmitted(&scattered->dir, &scatter_direction);
	transmitted(attenuation, &rec.material->color);
	(void)in;
	return (TRUE);
}
