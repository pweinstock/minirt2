#include "shapes.h"

void transphere(t_hit_record* rec, t_hit_record* tmp)
{
	rec->p = tmp->p;
	rec->normal = tmp->normal;
	rec->material = tmp->material;
	rec->t = tmp->t;
	rec->front_face = tmp->front_face;
}