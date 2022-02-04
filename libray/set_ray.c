/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:08:19 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:08:23 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	set_ray(t_vec3 origin, t_vec3 dir)
{
	t_ray	ret;

	ret.origin = origin;
	ret.dir = dir;
	return (ret);
}
