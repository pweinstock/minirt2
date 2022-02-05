#include "world.h"
#include <unistd.h>
#include <stdio.h>

#pragma pack(push, 1)
struct bitmap_header
{
	char t[2];
	unsigned int bfSize;
	unsigned int bfReserved;
	unsigned int bfOffBits;
};

struct bitmap_inf
{
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};
#pragma pack(pop)

void	ft_make_bmp(int (*arr)[HIGHT][WIDTH])
{
	struct bitmap_header header;
	struct bitmap_inf info;
	FILE *out;

	const int bitcount = 32;
	// const int width_in_bytes = ((WIDTH * bitcount + 31) / 32) * 4;
	const int width_in_bytes = WIDTH * bitcount;
	const unsigned int imagesize = width_in_bytes * HIGHT;

	header.t[0] = 'B';
	header.t[1] = 'M';
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
	fwrite(&header, sizeof(header), 1, out);
	fwrite(&info, sizeof(info), 1, out);
	fwrite((char*)(arr), 1, imagesize, out);
	fclose(out);
}