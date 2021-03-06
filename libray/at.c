/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   at.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:07:55 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/10 09:30:10 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vec3	at(t_ray p, double t)
{
	return (plus_vec_vec(multiply_vec_doub(p.dir, t), p.origin));
}
