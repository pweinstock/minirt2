#ifndef	 SHAPES_H
# define	SHAPES_H

#include "../libray/ray.h"
struct s_hit_record;
#include "../libmat/material.h"

typedef struct s_hit_record
{
    t_vec3 p;
    t_vec3 normal;
    t_material* material;
    double t;
    bool front_face;
}      t_hit_record;


typedef struct s_object
{
    bool (*hit)(t_ray r, struct s_object* object, double t_min, double t_max, t_hit_record* rec);
    t_material  mat;
    t_vec3      center;
    double      radius;
    double      hight;
    t_vec3      orientation;
    double      matrix_to_global[3][4];
    double      matrix_to_local[3][4];
}               t_object;



void set_face_normal( t_hit_record *rec, t_ray r, t_vec3 outward_nornal);
bool hit_plane(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec);
bool hit_sphere(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec);
bool hit_cylinder(t_ray r, t_object* object, double t_min, double t_max, t_hit_record* rec);
void initmatrix(t_object *object);
void matrix_transponieren(t_object *object);

#endif
