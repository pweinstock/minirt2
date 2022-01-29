/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RotationMatrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:07:39 by pweinsto          #+#    #+#             */
/*   Updated: 2022/01/29 17:40:34 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// double	*initmatrix(t_vec D, t_vec center)
// {
// 	double matrix[3][4];
// 	double cos_a;
// 	double cos_b;
// 	double sin_a;
// 	double sin_b;

// 	//ratio_number(object, &cos_a, &cos_b, &sin_a, &sin_b);
// 	sin_a = -D.x/sqrt(D.x * D.x + D.z * D.z);
// 	sin_b = D.y/length(D);
// 	cos_a = -D.z/sqrt(D.x * D.x + D.z * D.z);
// 	cos_b = sqrt(D.x * D.x + D.z * D.z) / length(D);


// 	matrix[0][0] = cos_a;
// 	matrix[0][1] = sin_a * sin_b;
// 	matrix[0][2] = sin_a * cos_b;

// 	matrix[1][0] = 0;
// 	matrix[1][1] = cos_b;
// 	matrix[1][2] = -sin_b;

// 	matrix[2][0] = -sin_a;
// 	matrix[2][1] = sin_b * cos_a;
// 	matrix[2][2] = cos_a * cos_b;

// 	return (&matrix);
// }

t_vec vec_to_local(t_vec center, t_vec orientation, t_vec vec)
{
	//double	***matrix;
	t_vec ret;
	t_vec P;
	double cos_a;
	double cos_b;
	double sin_a;
	double sin_b;


	sin_a = -orientation.x/sqrt(orientation.x * orientation.x + orientation.z * orientation.z);
	sin_b = orientation.y/length(orientation);
	cos_a = -orientation.z/sqrt(orientation.x * orientation.x + orientation.z * orientation.z);
	cos_b = sqrt(orientation.x * orientation.x + orientation.z * orientation.z) / length(orientation);

	//matrix = initmatrix(vec, center);
	P.x = vec.x - center.x;
	P.y = vec.y - center.y;
	P.z = vec.z - center.y;
	// dprintf(2, "p.v %f tmp %f obj %f\n", p.v[0], tmp->v[0], object->matrix_to_local[0][3]);



	ret.x = cos_a * P.x +  sin_a * sin_b * P.y +  sin_a * cos_b * P.z;

	ret.y = 0 * P.x +  cos_b * P.y +  -sin_b * P.z;

	ret.z = -sin_a * P.x +  sin_b * cos_a * P.y +  cos_a * cos_b * P.z;

	return ret;
}

t_vec		rotation_x(t_vec vec, double a)
{
	t_vec	new_vec;

	a = a * PI / 180;
	new_vec.x = vec.x;
	new_vec.y = vec.y * cos(a) - vec.z * sin(a);
	new_vec.z = vec.y * sin(a) + vec.z * cos(a);
	return (new_vec);
}

t_vec		rotation_y(t_vec vec, double b)
{
	t_vec	new_vec;

	b = b * PI / 180;
	new_vec.x = vec.x * cos(b) + vec.z * sin(b);
	new_vec.y = vec.y;
	new_vec.z = vec.x * -sin(b) + vec.z * cos(b);
	return (new_vec);
}

t_vec		rotation_z(t_vec vec, double c)
{
	t_vec	new_vec;

	c = c * PI / 180;
	new_vec.x = vec.x * cos(c) - vec.y * sin(c);
	new_vec.y = vec.x * sin(c) + vec.y * cos(c);
	new_vec.z = vec.z;
	return (new_vec);
}

t_vec		rotation(t_vec vec, double a, double b, double c)
{
	t_vec new_vec;

	new_vec = rotation_x(vec, a);
	new_vec = rotation_y(new_vec, b);
	new_vec = rotation_z(new_vec, c);
	return (new_vec);
}

