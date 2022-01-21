#include "ray.h"
#include <stdio.h>

int main()
{

    t_vec3 a;

    a = setvec(2, 1, 1);
    a = multiply_vec_vec(a, a);
    printf("%f", a.v[0]);

}