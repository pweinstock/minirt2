/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:05:42 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/03 20:33:58 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "./world.h"
#include "parser/parser.h"

t_bool hit(t_ray r, t_world *world, double t_max, t_hit_record* rec)
{
	size_t	i;
	t_hit_record temp_rec;
	temp_rec.material = NULL;
	t_bool hit_anything = FALSE;
	double closest_so_far;
	closest_so_far = t_max;
	rec->t = t_max;

	i = 0;
	while (i < world->n_hittabels)
	{
		if(world->hittabels[i].hit(r, &world->hittabels[i], closest_so_far, &temp_rec))
		{
			hit_anything = TRUE;
			closest_so_far = temp_rec.t;
			transphere(rec, &temp_rec);
			rec->p = plus_vec_vec(rec->p, multiply_vec_doub(rec->normal, 0.0));
			rec->material = &world->hittabels[i].mat;
		}
		i++;
	}
	return hit_anything;
}
