/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shackbei <shackbei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 20:47:35 by shackbei          #+#    #+#             */
/*   Updated: 2022/02/18 13:49:27 by shackbei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_map.h"

void	set_values(struct s_bitmap_header *header, struct s_bitmap_inf *info)
{
	header->bfreserved = 0;
	header->bfoffbits = 54;
	info->bisize = 40;
	info->biwidth = WIDTH;
	info->biheight = HIGHT;
	info->biplanes = 1;
	info->bibitcount = 32;
	info->bicompression = 0;
	info->bixpelspermeter = 0;
	info->biypelspermeter = 0;
	info->biclrused = 0;
	info->biclrimportant = 0;
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
	const unsigned int		imagesize = WIDTH * HIGHT * 4;

	out = NULL;
	chdir("./pictures");
	ft_set_name(file, &out);
	header.bfsize = 54 + imagesize;
	info.bisizeimage = imagesize;
	set_values(&header, &info);
	fwrite("BM", 2, 1, out);
	fwrite(&header, sizeof(header), 1, out);
	fwrite(&info, sizeof(info), 1, out);
	fwrite((char *)(arr), 1, imagesize, out);
	fclose(out);
}
