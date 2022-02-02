/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:14:54 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:16:02 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	while (TRUE)
	{
		p = random_vec3(-1, 1);
		if (length_squared(&p) >= 1)
			continue ;
		return (p);
	}
}

t_vec3	random_in_hemispere(const t_vec3 normal)
{
	t_vec3	in_unit_sphere;

	in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0)
		return (in_unit_sphere);
	else
		return (invert(in_unit_sphere));
}

t_vec3	random_unit_vector(void)
{
	return (unit_vector(random_in_unit_sphere()));
}
