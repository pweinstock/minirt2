/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmitted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:13:09 by shackbei          #+#    #+#             */
/*   Updated: 2022/01/31 21:09:45 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_vec3.h"

void	transmitted(t_vec3 *u, t_vec3 *v)
{
	u->v[0] = v->v[0];
	u->v[1] = v->v[1];
	u->v[2] = v->v[2];
}
