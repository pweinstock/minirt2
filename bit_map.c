/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:47:35 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/05 20:47:39 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_map.h"

void	ft_make_bmp(int (*arr)[HIGHT][WIDTH])
{
	struct s_bitmap_header	header;
	struct s_bitmap_inf		info;
	FILE					*out;
	const unsigned int		imagesize = WIDTH * 32 * HIGHT;

	header.bfSize = 54 + imagesize;
	header.bfReserved = 0;
	header.bfOffBits = 54;
	info.biSize = 40;
	info.biWidth = WIDTH;
	info.biHeight = HIGHT;
	info.biPlanes = 1;
	info.biBitCount = 32;
	info.biCompression = 0;
	info.biSizeImage = imagesize;
	info.biXPelsPerMeter = 0;
	info.biYPelsPerMeter = 0;
	info.biClrUsed = 0;
	info.biClrImportant = 0;
	out = fopen("test.bmp", "wb");
	fwrite("BM", 2, 1, out);
	fwrite(&header, sizeof(header), 1, out);
	fwrite(&info, sizeof(info), 1, out);
	fwrite((char *)(arr), 1, imagesize, out);
	fclose(out);
}
