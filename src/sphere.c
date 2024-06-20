/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:52:10 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/20 13:27:58 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"
#include "ray.h"
#include <stdbool.h>
#include <math.h>
#include "vec3.h"

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
double hit_sphere(const t_sphere *s, const t_ray *r) 
{
    t_vec3 oc = vec3substr(&(s->center), &(r->orig));
    double a = dot(&(r->dir), &(r->dir));
    double h = dot(&(r->dir), &oc);
	double c = length3_squared(&oc) - s->radius * s->radius;
    double discriminant = h*h - a*c;
    // double c = dot(&oc, &oc) - s->radius * s->radius;
    // double discriminant = b*b - 4*a*c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((h - sqrt(discriminant)) /  a);
}
