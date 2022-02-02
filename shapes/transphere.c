/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:17:17 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/01 12:17:19 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

void	transphere(t_hit_record *rec, t_hit_record *tmp)
{
	rec->p = tmp->p;
	rec->normal = tmp->normal;
	rec->material = tmp->material;
	rec->t = tmp->t;
	rec->front_face = tmp->front_face;
}
