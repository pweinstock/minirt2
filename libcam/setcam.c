/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:53:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 14:51:04 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cam.h"
#include "../world.h"
#include <math.h>
#include <stdio.h>

	// cam->w = unit_vector(minus_vec_vec(cam->origin, orientation));
void	set_cam(t_camera *cam, t_vec3 origin,
			t_vec3 orientation, double degrees)
{
	double	theta;
	double	h;
	double	viewport_height;
	double	viewport_width;

	cam->origin = origin;
	cam->orientation = orientation;
	cam->degrees = degrees;
	theta = degrees_to_radians(cam->degrees);
	h = tan(theta / 2);
	viewport_height = 2 * h;
	viewport_width = (double)WIDTH / (double)HIGHT * viewport_height;
	cam->w = invert(orientation);
	cam->u = unit_vector(cross(setvec(0, 1, 0), cam->w));
	cam->v = cross(cam->w, cam->u);
	cam->horizontal = multiply_vec_doub(cam->u, viewport_width);
	cam->vertical = multiply_vec_doub(cam->v, viewport_height);
	cam->lower_left_corner = minus_vec_vec(minus_vec_vec(
				minus_vec_vec(cam->origin, division(cam->horizontal, 2)),
				division(cam->vertical, 2)), cam->w);
}
