/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:50:02 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 13:48:18 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIT_MAP_H
# define BIT_MAP_H

# include "world.h"
# include <unistd.h>
# include <stdio.h>

struct s_bitmap_header
{
	unsigned int	bfsize;
	unsigned int	bfreserved;
	unsigned int	bfoffbits;
};

struct s_bitmap_inf
{
	unsigned int	bisize;
	unsigned int	biwidth;
	unsigned int	biheight;
	uint16_t		biplanes;
	uint16_t		bibitcount;
	unsigned int	bicompression;
	unsigned int	bisizeimage;
	unsigned int	bixpelspermeter;
	unsigned int	biypelspermeter;
	unsigned int	biclrused;
	unsigned int	biclrimportant;
};

#endif