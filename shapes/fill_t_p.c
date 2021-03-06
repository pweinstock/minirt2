/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_t_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:04:28 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/01 18:04:10 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

void	fill_t_p(t_hit_record *rec, double t, t_ray r)
{
	rec->t = t;
	rec->p = at(r, t);
}
