/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:39:04 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/19 13:16:53 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <stdio.h>
#include <math.h>

/*
 * This is the C equivalent of a C++ initializer
 */
t_vec3	vec3(double x, double y, double z)
{
	t_vec3 result;

	result.p[0] = x;
	result.p[1] = y;
	result.p[2] = z;
	return result;
}

t_point3	point3(double x, double y, double z)
{
	t_point3 result;

	result.p[0] = x;
	result.p[1] = y;
	result.p[2] = z;
	return result;
}

// do I need these getters? we are not in cpp here :)
double	vec3x(const t_vec3 *v)
{
	return (v->p[0]);
}
double 	vec3y(const t_vec3 *v)
{
	return (v->p[1]);
}
double 	vec3z(const t_vec3 *v)
{
	return (v->p[2]);
}


t_vec3	vec3negate(const t_vec3 *a)
{
	t_vec3 result;

	result.p[0] = -a->p[0];
	result.p[1] = -a->p[1];
	result.p[2] = -a->p[2];
	return result;
}

t_vec3	vec3add(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[0] + b->p[0];
	result.p[1] = a->p[1] + b->p[1];
	result.p[2] = a->p[2] + b->p[2];
	return result;
}

t_vec3	vec3substr(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[0] - b->p[0];
	result.p[1] = a->p[1] - b->p[1];
	result.p[2] = a->p[2] - b->p[2];
	return result;
}

t_vec3	vec3mult(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[0] * b->p[0];
	result.p[1] = a->p[1] * b->p[1];
	result.p[2] = a->p[2] * b->p[2];
	return result;

}

t_vec3	vec3multscalar(const t_vec3 *a, double t)
{
	t_vec3 result;

	result.p[0] = a->p[0] * t;
	result.p[1] = a->p[1] * t;
	result.p[2] = a->p[2] * t;
	return result;
}

t_vec3	vec3divide(const t_vec3 *a, double t)
{
	t_vec3 result;

	result.p[0] = a->p[0] / t;
	result.p[1] = a->p[1] / t;
	result.p[2] = a->p[2] / t;
	return result;
}
  
double	length3_squared(const t_vec3 *v)
{
	return (v->p[0] * v->p[0] + v->p[1] * v->p[1] + v->p[2] * v->p[2]);
}

double	length3(const t_vec3 *v)
{
	return (sqrt(length3_squared(v)));
}

// Vector Utility Functions
/*
 * to debug
 */
void	print_vec3(const t_vec3 *v)
{
	printf("%f %f %f\n", v->p[0], v->p[1], v->p[2]);
}

/*
 * dot product of vectors a . b = a1*b1 + a2*b2 + a3*b3
 */
double	dot(const t_vec3 *a, const t_vec3 *b)
{
	double result;

	result = a->p[0] * b->p[0];
	result += a->p[1] * b->p[1];
	result += a->p[2] * b->p[2];
	return result;
}

/*
returns the cross product of a and b by value
*/
t_vec3	vec3cross(const t_vec3 *a, const t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[1] * b->p[2] - a->p[2] * b->p[1];
	result.p[1] = a->p[2] * b->p[0] - a->p[0] * b->p[2];
	result.p[2] = a->p[0] * b->p[1] - a->p[1] * b->p[0];
	return result;
}

/*
Modify in place
*/
void unit_vector(t_vec3 *v)
{
    double length = length3(v);
    v->p[0] /= length;
    v->p[1] /= length;
    v->p[2] /= length;
}

