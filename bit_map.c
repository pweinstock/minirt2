/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:47:35 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/08 17:31:30 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_map.h"

void	set_values(struct s_bitmap_header *header, struct s_bitmap_inf *info)
{
	header->bfReserved = 0;
	header->bfOffBits = 54;
	info->biSize = 40;
	info->biWidth = WIDTH;
	info->biHeight = HIGHT;
	info->biPlanes = 1;
	info->biBitCount = 32;
	info->biCompression = 0;
	info->biXPelsPerMeter = 0;
	info->biYPelsPerMeter = 0;
	info->biClrUsed = 0;
	info->biClrImportant = 0;
}

void	ft_set_name(char *file, FILE **out)
{
	file[0] = '.';
	file[1] = '/';
	file[2] = 'A';
	file[3] = 'A' - 1;
	file[4] = '.';
	file[5] = 'b';
	file[6] = 'm';
	file[7] = 'p';
	file[8] = '\0';
	while (*out == NULL)
	{
		file[3]++;
		if (file[3] == 'Z' && file[2] != 'Z')
		{
			file[2]++;
			file[3] = 'A';
		}
		if (file[2] == 'Z' && file[3] == 'Z')
			*out = fopen(file, "wb");
		else
			*out = fopen(file, "wx");
	}
}

void	ft_make_bmp(int *arr)
{
	struct s_bitmap_header	header;
	struct s_bitmap_inf		info;
	FILE					*out;
	char					file[9];
	const unsigned int		imagesize = WIDTH * HIGHT * 4; //auf geheis von tim

	out = NULL;
	chdir("./pictures");
	ft_set_name(file, &out);
	header.bfSize = 54 + imagesize;
	info.biSizeImage = imagesize;
	set_values(&header, &info);
	fwrite("BM", 2, 1, out);
	fwrite(&header, sizeof(header), 1, out);
	fwrite(&info, sizeof(info), 1, out);
	fwrite((char *)(arr), 1, imagesize, out);
	fclose(out);
}
