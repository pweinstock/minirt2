#ifndef	 WORLD_H
# define	WORLD_H

#include <stdint.h>
#include <stdlib.h>
#include "libcam/cam.h"
// #include "libmat/material.h"
#include "libmath/my_math.h"
#include "libvec/t_vec3.h"
#include "shapes/shapes.h"

typedef struct s_world
{
    t_object *hittabels;
	size_t	n_hittabels;
    t_camera *cam;

}               t_world;

#endif

