/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degrees_to_radians.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:06:11 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:06:21 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	degrees_to_radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}
