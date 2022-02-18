/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:08:55 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 14:44:02 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "../libvec/t_vec3.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

t_vec3	at(t_ray p, double t);
t_ray	set_ray(t_vec3 origin, t_vec3 dir);

#endif