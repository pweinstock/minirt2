#include <unistd.h>

// #pragma pack( show )

// #pragma pack(push, 8)
struct test
{
	char hi;
	int my;
	char klsdj;
};

int main()
{
	// #pragma pack( show )
	// struct test t;
	char test[2][2] = {{49,50}, {51,52}};

	write(1, &test, 4);
	// printf("struct = %lu",sizeof(t));
	return (0);
}
// #pragma pack(pop)