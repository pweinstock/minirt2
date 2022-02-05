#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#pragma pack(push, 1)
struct my_BITMAPFILEHEADER {
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
};

struct my_BITMAPINFOHEADER {
	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};
#pragma pack(pop)

int main(void)
{
	if(sizeof(struct my_BITMAPFILEHEADER) != 14 &&
		sizeof(struct my_BITMAPINFOHEADER) != 40)
	{
		printf("bitmap structures not packed properly\n");
		return 0;
	}

	//only width and height can be changed in this code:
	int width = 24;
	int height = 24;

	int bitcount = 24;//<- 24-bit bitmap
	int width_in_bytes = ((width * bitcount + 31) / 32) * 4;	//for padding
	uint32_t imagesize = width_in_bytes * height;   //total image size

	struct my_BITMAPFILEHEADER filehdr = { 0 };
	struct my_BITMAPINFOHEADER infohdr = { 0 };

	memcpy(&filehdr, "BM", 2);//bitmap signature
	filehdr.bfSize = 54 + imagesize;//total file size
	filehdr.bfOffBits = 54; //sizeof(filehdr) + sizeof(infohdr)

	infohdr.biSize = 40; //sizeof(infohdr)
	infohdr.biPlanes = 1; //number of planes is usually 1
	infohdr.biWidth = width;
	infohdr.biHeight = height;
	infohdr.biBitCount = bitcount;
	infohdr.biSizeImage = imagesize;

	//prepare pixel data:
	unsigned char* buf = malloc(imagesize);
	for(int row = height - 1; row >= 0; row--)
	{
		for(int col = 0; col < width; col++)
		{
			buf[row * width_in_bytes + col * 3 + 0] = 255;//blue
			buf[row * width_in_bytes + col * 3 + 1] = 1;//red
			buf[row * width_in_bytes + col * 3 + 2] = 100;//green
		}
	}

	FILE *fout = fopen("test.bmp", "wb");
	fwrite(&filehdr, sizeof(filehdr), 1, fout);
	fwrite(&infohdr, sizeof(infohdr), 1, fout);
	fwrite((char*)buf, 1, imagesize, fout);
	fclose(fout);
	free(buf);

	return 0;
}