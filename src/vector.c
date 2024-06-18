/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:39:04 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/18 14:46:29 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdio.h>
#include <math.h>

void	init_vec3(t_vec3 *v, double x, double y, double z)
{
	v->p[0] = x;
	v->p[1] = y;
	v->p[2] = z;
}


double	vec3x(t_vec3 *v)
{
	return (v->p[0]);
}

double	vec3y(t_vec3 *v)
{
	return (v->p[1]);
}

double	vec3z(t_vec3 *v)
{
	return (v->p[2]);
}

t_vec3	vec3negate(t_vec3 *a)
{
	t_vec3 result;

	result.p[0] = -a->p[0];
	result.p[1] = -a->p[1];
	result.p[2] = -a->p[2];
	return (result);
}

t_vec3	vec3add(t_vec3 *a, t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[0] + b->p[0];
	result.p[1] = a->p[1] + b->p[1];
	result.p[2] = a->p[2] + b->p[2];
	return (result);
}

t_vec3	vec3substr(t_vec3 *a, t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[0] - b->p[0];
	result.p[1] = a->p[1] - b->p[1];
	result.p[2] = a->p[2] - b->p[2];
	return (result);
}	

t_vec3	vec3mult(t_vec3 *a, t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[0] * b->p[0];
	result.p[1] = a->p[1] * b->p[1];
	result.p[2] = a->p[2] * b->p[2];
	return (result);
}


t_vec3	vec3multscalar(t_vec3 *a, double t)
{
	t_vec3 result;

	result.p[0] = a->p[0] * t;
	result.p[1] = a->p[1] * t;
	result.p[2] = a->p[2] * t;
	return (result);
}

t_vec3	vec3divide(t_vec3 *a, double t)
{
	t_vec3 result;

	result.p[0] = a->p[0] / t;
	result.p[1] = a->p[1] / t;
	result.p[2] = a->p[2] / t;
	return (result);
}

double	length3_squared(t_vec3 *v)
{
	return (v->p[0] * v->p[0] + v->p[1] * v->p[1] + v->p[2] * v->p[2]);
}

double	length3(t_vec3 *v)
{
	return (sqrt(length3_squared(v)));
}

void	print_vec3(t_vec3 *v)
{
	printf("%f %f %f\n", v->p[0], v->p[1], v->p[2]);
}

double	vec3dot(t_vec3 *a, t_vec3 *b)
{
	return (a->p[0] * b->p[0] + a->p[1] * b->p[1] + a->p[2] * b->p[2]);
}

t_vec3	vec3cross(t_vec3 *a, t_vec3 *b)
{
	t_vec3 result;

	result.p[0] = a->p[1] * b->p[2] - a->p[2] * b->p[1];
	result.p[1] = a->p[2] * b->p[0] - a->p[0] * b->p[2];
	result.p[2] = a->p[0] * b->p[1] - a->p[1] * b->p[0];
	return (result);
}


t_vec3	vec3unit(t_vec3 *v)
{
	return (vec3divide(v, length3(v)));
}

