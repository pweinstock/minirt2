/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:02:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:02:47 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"

double	reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (minus_vec_vec(multiply_vec_doub(multiply_vec_doub(n, 2), dot(v, n)), v));
}

t_vec3	refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double	cos_theta;
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;

	cos_theta = fmin(dot(invert(uv), n), 1.0);
	r_out_perp = multiply_vec_doub(plus_vec_vec(uv, multiply_vec_doub(n, cos_theta)), etai_over_etat);
	r_out_parallel = multiply_vec_doub(n, -sqrt(fabs(1.0 - length_squared(&r_out_perp))));
	return (plus_vec_vec(r_out_perp, r_out_parallel));
}

bool	near_zero(t_vec3 v)
{
	double	s;

	s = 1e-8;
	return ((fabs(v.v[0]) < s) && (fabs(v.v[1]) < s) && (fabs(v.v[2]) < s));
}
