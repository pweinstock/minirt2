/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:56:03 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 20:56:33 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 MAT_H
# define	MAT_H

# include "../libvec/t_vec3.h"
# include "../shapes/shapes.h"
# include <math.h>

double	reflectance(double cosine, double ref_idx);
t_vec3	reflect(t_vec3 v, t_vec3 n);
t_vec3	refract(t_vec3 uv, t_vec3 n, double etai_over_etat);
bool	near_zero(t_vec3 v);

#endif