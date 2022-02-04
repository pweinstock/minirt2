/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pweinsto <pweinsto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:52:04 by pweinsto          #+#    #+#             */
/*   Updated: 2022/02/04 12:55:34 by pweinsto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// t_vec	CanvasToViewport(x, y)
// {
// 	t_vec	vec;
// 	int		d;
// 	vec.x = w * viewport.width / canvas.width;
// 	vec.y = h * viewport.height / canvas.height;
// 	vec.z = d;
// 	return (vec);
// }

t_vec	ReflectRay(t_vec R, t_vec N)
{
	return (vec_sub(vec_mult(vec_mult(N, 2), dot(N, R)), R));
}

t_intersection	ClosestIntersection(t_scene scene, t_vec O, t_vec D, double t_min, double t_max)
{
	double	closest_t;
	double	t1;
	int	i;
	int	flag;
	t_object	closest_object;
	t_intersection	intersection;


	//(void)t_max;
	//(void)t_min;
	closest_t = 2147483647;
	flag = 0;
	i = 0;
	while (i < 7)
	{
		// t1 = IntersectRaySphere(O, D, scene.spheres[i]);
		//printf("i: %d\n", i);
		//if (scene.objects[i].type == TERM)
		//	break ;
		if (scene.objects[i].type == SPHERE)
			t1 = IntersectRaySphere(O, D, scene.objects[i]);
		else if (scene.objects[i].type == PLANE)
			t1 = IntersectRayPlane(O, D, scene.objects[i]);
		else if (scene.objects[i].type == CYLINDER)
			t1 = IntersectRayCylinder(O, D, scene.objects[i]);
		else if (scene.objects[i].type == CAP)
			t1 = IntersectRayCap(O, D, scene.objects[i]);
		if (t1 > t_min && t1 < t_max && t1 < closest_t)
		{
			closest_t = t1;
			closest_object = scene.objects[i];
			flag = 1;
		}
		i++;
	}
	intersection.flag = flag;
	intersection.closest_t = closest_t;
	intersection.closest_object = closest_object;
	return (intersection);
}

double	ComputeLightning(t_scene scene, t_vec P, t_vec N, t_vec V, double s)
{
	int	i;
	double	intensity;
	t_vec	L;
	t_vec	R;
	double	n_dot_l;
	double	r_dot_v;
	t_intersection	intersection;

	(void)P;
	(void)N;
	i = 0;
	intensity = 0;
	while (i < 2)
	{
		//if (scene.lights[i].type == TERM)
		//	break ;
		if (scene.lights[i].type == AMBIENT)
			intensity += scene.lights[i].intensity;
		else
		{
			if (scene.lights[i].type == POINT)
				L = vec_sub(scene.lights[i].position, P);
			else
				L = scene.lights[i].direction;
			intersection = ClosestIntersection(scene, P, L, 0.001, 2147483647);
			if (intersection.flag)
			{
				i++;
				continue ;
			}
			n_dot_l = dot(N, L);
			if (n_dot_l > 0)
				intensity += scene.lights[i].intensity * n_dot_l / (length(N) * length(L));
			if (s != -1)
			{
				//R = vec_sub(vec_mult(vec_mult(N, 2), dot(N, L)), L);
				R = ReflectRay(L, N);
				r_dot_v = dot(R, V);
				if (r_dot_v > 0)
					intensity += scene.lights[i].intensity * pow(r_dot_v / (length(R) * length(V)), s);
			}
		}
		i++;
	}
	return (intensity);
}

double	IntersectRaySphere(t_vec O, t_vec D, t_object sphere)
{
	t_vec	CO;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;

	CO = vec_sub(O, sphere.center);
	a = dot(D, D);
	b = 2 * dot(CO, D);
	c = dot(CO, CO) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (2147483647);
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	if (t1 <= t2)
		return (t1);
	else
		return (t2);
}

double	IntersectRayPlane(t_vec orig, t_vec dir, t_object plane)
{
	double	denom;
	double	numer;
	double	t;

	denom = dot(plane.orientation, dir);
	numer = dot(vec_sub(orig, plane.center), plane.orientation);
	t = -numer / denom;
	if (t >= 0)
		return (t);
	else
		return (2147483647);
}

double	IntersectRayCap(t_vec orig, t_vec dir, t_object cap)
{
	double	t;
	t_vec	P;
	t_vec	N;

	t = IntersectRayPlane(orig, dir, cap);

	if (t >= 2147483647)
		return (2147483647);
	else
	{
		P = vec_add(orig, vec_mult(dir, t));
		N = vec_sub(P, cap.center);
		if (length(N) <= cap.radius / 2)
			return (t);
		else
			return (2147483647);
	}
}

double IntersectRayCylinder(t_vec orig, t_vec dir, t_object cylinder)
{
	t_vec	cross1;
	t_vec	cross2;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	double	d1;
	double	d2;

	cross1 = vec_cross(dir, cylinder.orientation);
	cross2 = vec_cross(vec_sub(orig, cylinder.center), cylinder.orientation);
	a = dot(cross1, cross1);
	b = 2 * dot(cross1, cross2);
	c = dot(cross2, cross2) - pow(cylinder.radius / 2, 2) * dot(cylinder.orientation, cylinder.orientation);
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		return (2147483647);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	d1 = dot(cylinder.orientation, vec_sub(vec_mult(dir, t1), vec_sub(cylinder.center, orig)));
	d2 = dot(cylinder.orientation, vec_sub(vec_mult(dir, t2), vec_sub(cylinder.center, orig)));
	if ((d1 < 0 || d1 > cylinder.height) && (d2 < 0 || d2 > cylinder.height))
			return (2147483647);
	if (t1 <= t2)
		return (t1);
	else
		return (t2);
}

t_vec	SphereReflection(t_vec P, t_vec center)
{
	t_vec	N;

	N = vec_sub(P, center);
	N = vec_divide(N, length(N));
	return (N);
}

t_vec	CylinderReflection(t_vec P, t_vec center, t_vec orientation)
{
	t_vec	N;
	t_vec	axe;

	N = vec_sub(P, center);
	N = vec_sub(P, center);
	axe = vec_mult(orientation, fabs(dot(N, orientation)));
	if (dot(N, orientation) < 0)
		axe = vec_mult(axe, -1);
	N = vec_sub(N, axe);
	N = vec_divide(N, length(N));
	return (N);
}

t_color	TraceRay(t_vec O, t_vec D, t_scene scene, double t_min, double t_max, int recursion_depth)
{
	t_intersection	intersection;
	t_vec		P;
	t_vec		N;
	t_color		local_color;
	t_color		reflected_color;
	double		r;
	t_vec		R;

	intersection = ClosestIntersection(scene, O, D, t_min, t_max);
	if (intersection.flag == 0)
		return(scene.backround);
	P = vec_add(O, vec_mult(D, intersection.closest_t));
	// N = vec_sub(P, intersection.closest_sphere.center);
	// N = vec_divide(N, length(N));
	if (intersection.closest_object.type == SPHERE)
		N = SphereReflection(P, intersection.closest_object.center);
	else if (intersection.closest_object.type == CYLINDER)
		N = CylinderReflection(P, intersection.closest_object.center, intersection.closest_object.orientation);
	else
		N = intersection.closest_object.orientation;
	//return (color_multi(intersection.closest_sphere.color, ComputeLightning(scene, P, N, vec_mult(ray.direction, -1), intersection.closest_sphere.specular)));
	local_color = color_multi(intersection.closest_object.color, ComputeLightning(scene, P, N, vec_mult(D, -1), intersection.closest_object.specular));
	r = intersection.closest_object.reflective;
	if (recursion_depth <= 0 || r <= 0)
		return (local_color);
	R = ReflectRay(vec_mult(D, -1), N);
	reflected_color = TraceRay(P, R, scene, 0.001, 2147483647, recursion_depth - 1);
	return (color_add(color_multi(local_color, 1 - r), color_multi(reflected_color, r)));
}

void	write_color(t_color color)
{
	printf("%f %f %f\n", color.r, color.g, color.b);
}

int	main(int argc, char **argv)
{
	t_canvas	canvas;
	t_viewport	viewport;
	t_vec		D;
	t_vec		camera;
	t_scene		scene;
	t_color		color;
	double	w;
	double	h;
	double	d;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	(void)argc;
	//(void)argv;
	camera.x = 0;
	camera.y = 0;
	camera.z = -5;
	
	canvas.height = 1200;
	canvas.width = 1200;

	viewport.height = 1;
	viewport.width = 1;

	d = 1;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, canvas.width, canvas.height, "miniRT");
	img.img = mlx_new_image(mlx, canvas.width, canvas.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	//scene = create_scene();

	scene_init(argv[1], &scene);
	//printf("P3\n%f %f\n255\n", canvas.width, canvas.height);
	h = (canvas.height/ 2) * (-1);
	while (h < canvas.height / 2)
	{
		w = (canvas.width / 2) * (-1);
		while (w < canvas.width / 2)
		{
			D.x = w * viewport.width / canvas.width;
			D.y = h * viewport.height / canvas.height;
			D.z = d;
			D = rotation(D, 0, 0, 0);
			color = TraceRay(camera, D, scene, 1, 2147483647, 10);
			//write_color(color);
			my_mlx_pixel_put(&img, (int)(w + (canvas.width / 2)), (int)(h + (canvas.height / 2)), color);
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free(scene.objects);
	return (0);
}