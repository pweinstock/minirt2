#ifndef	 WORLD_H
# define	WORLD_H

#include <stdint.h>
#include <stdlib.h>
#include "libcam/cam.h"
#include "shapes/shapes.h"
#include "libmath/my_math.h"

typedef struct s_world
{
    t_object *hittabels;
	size_t	n_hittabels;
    t_camera *cam;

}               t_world;

#endif

