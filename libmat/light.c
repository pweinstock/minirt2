/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:57:00 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 20:57:09 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat.h"
#include <stdio.h>

bool	scatter_light(t_ray in, struct s_hit_record rec,
			t_vec3 *attenuation, t_ray *scattered)
{
	(void)in;
	(void)rec;
	(void)attenuation;
	(void)scattered;
	return (FALSE);
}
