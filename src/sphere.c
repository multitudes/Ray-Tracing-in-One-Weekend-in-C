/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:52:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/21 07:38:27 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "ray.h"
#include <stdbool.h>
#include <math.h>
#include "vec3.h"
#include "hittable.h"

/*
 * a sort of initializer for a sphere
 */
t_sphere sphere(t_point3 center, double radius)
{
	t_sphere s;

	s.center = center;
	s.radius = radius;
	return s;
}

/*
 * in the body oc is the vector from origin of the ray 
 * to the center of the sphere
 * At first the formula was derived from the quadratic formula
 * double b = -2.0 * dot(&(r->dir), &oc);
 * double c = dot(&oc, &oc) - s->radius * s->radius;
 * but this has been refactored using double h 
 */
bool hit_sphere(const t_sphere *s, const t_ray *r, double ray_tmin, double ray_tmax, t_hit_record *rec) 
{
    t_vec3 oc = vec3substr(&(s->center), &(r->orig));
    double a = length3_squared(&r->dir); 
    double h = dot(&(r->dir), &oc);
	double c = length3_squared(&oc) - s->radius * s->radius;
    double discriminant = h*h - a*c;

	if (discriminant < 0)
		return (false);
	double sqrtd = sqrt(discriminant);
	double root = (h - sqrtd) / a;
	if (root <= ray_tmin || ray_tmax <= root) {
	root = (h + sqrtd) / a;
	if (root <= ray_tmin || ray_tmax <= root)
		return false;
    }
	rec->t = root;
	rec->p = point_at(r, rec->t);
	t_vec3 inters_minus_center = vec3substr(&rec->p, &(s->center));
	rec->normal = vec3divscalar(&inters_minus_center, s->radius);

	return (true);
}


