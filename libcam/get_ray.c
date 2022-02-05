/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:43:33 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 17:58:56 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cam.h"

t_ray	get_ray(t_camera cam, double s, double t)
{
	return (set_ray(cam.origin,
			minus_vec_vec(plus_vec_vec(plus_vec_vec(cam.lower_left_corner,
						multiply_vec_doub(cam.horizontal, s)),
					multiply_vec_doub(cam.vertical, t)), cam.origin)));
}
