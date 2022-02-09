/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:52:11 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/09 14:30:02 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	 MATERIAL_H
# define	MATERIAL_H

# include "../libray/ray.h"
# include "../shapes/shapes.h"

struct	s_hit_record;

typedef struct s_material
{
	t_color	color1;
	t_color	color2;
	double	ir;
	double	specular;
	double	reflective;
	t_color (*emitted)(struct s_hit_record * rec);
	t_bool (*scatter)(t_ray in, struct s_hit_record rec,
		t_vec3 * attenuation, t_ray * scattered);
}				t_material;

t_bool	scatter_dielectric(t_ray in, struct s_hit_record rec,
			t_vec3 *attenuation, t_ray *scattered);
t_bool	scatter_lambertian(t_ray in, struct s_hit_record rec,
			t_vec3 *attenuation, t_ray *scattered);
t_bool	scatter_metal(t_ray in, struct s_hit_record rec,
			t_vec3 *attenuation, t_ray *scattered);
t_bool	scatter_light(t_ray in, struct s_hit_record rec,
			t_vec3 *attenuation, t_ray *scattered);
t_vec3	reflect(t_vec3 v, t_vec3 n);
t_color	emitted_color(struct s_hit_record *rec);
t_color	emitted_checkerboard(struct s_hit_record *rec);

#endif