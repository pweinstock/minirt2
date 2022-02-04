/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_face_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:33:07 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/01 13:33:15 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

void	set_face_normal( t_hit_record *rec, t_ray r, t_vec3 outward_nornal)
{
	rec->front_face = dot(r.dir, outward_nornal) < 0;
	if (rec->front_face)
	{
		rec->normal = outward_nornal;
	}
	else
	{
		rec->normal = invert(outward_nornal);
	}
}
