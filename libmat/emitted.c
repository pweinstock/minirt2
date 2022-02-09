#include "mat.h"

t_color emitted_color(struct s_hit_record *rec)
{
	return (rec->material->color1);
}

t_color emitted_checkerboard(struct s_hit_record *rec)
{
	long	test[3];
	int		XOR;

	test[0] = labs((long)floorl(rec->p.vec.x));
	test[1] = labs((long)floorl(rec->p.vec.y));
	test[2] = labs((long)floorl(rec->p.vec.z));

	XOR = (test[0]%2 ^ test[1]%2) ^ test[2]%2;
	if (XOR)
		return (rec->material->color1);
	else
		return (rec->material->color2);
}