/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:13:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:18:43 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double	random_doublem(double min, double max)
{
	return (min + (max - min) * random_double());
}

t_vec3	random_vec3(double min, double max)
{
	return (setvec(random_doublem(min, max),
		random_doublem(min, max), random_doublem(min, max)));
}
