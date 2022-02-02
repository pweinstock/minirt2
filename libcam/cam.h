/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:48:54 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 20:48:56 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 CAM_H
# define	CAM_H

# include "../libray/ray.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	lower_left_corner;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_data	img;
	double	lens_radius;
	int		fd;
}	t_camera;

t_ray		get_ray(t_camera cam, double s, double t);
t_camera	*set_cam(t_vec3 origin, t_vec3 orientation, int degrees);

#endif