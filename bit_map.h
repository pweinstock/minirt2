/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 19:50:02 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 20:06:12 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIT_MAP_H
# define BIT_MAP_H

# include "world.h"
# include <unistd.h>
# include <stdio.h>

struct s_bitmap_header
{
	unsigned int	bfSize;
	unsigned int	bfReserved;
	unsigned int	bfOffBits;
};

struct s_bitmap_inf
{
	unsigned int	biSize;
	unsigned int	biWidth;
	unsigned int	biHeight;
	uint16_t		biPlanes;
	uint16_t		biBitCount;
	unsigned int	biCompression;
	unsigned int	biSizeImage;
	unsigned int	biXPelsPerMeter;
	unsigned int	biYPelsPerMeter;
	unsigned int	biClrUsed;
	unsigned int	biClrImportant;
};

#endif