
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:59:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/18 14:25:03 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct 	s_vec3
{
	double p[3];
}				t_vec3, t_color, t_point3;

t_vec3		vec3(double x, double y, double z);
t_point3	point3(double x, double y, double z);

double	vec3x(const t_vec3 *v);
double 	vec3y(const t_vec3 *v);
double 	vec3z(const t_vec3 *v);


t_vec3	vec3negate(const t_vec3 a);
t_vec3	vec3add(const t_vec3 a, const t_vec3 b);
t_vec3	vec3substr(const t_vec3 *a, const t_vec3 *b);
t_vec3	vec3mult(const t_vec3 a, const t_vec3 b);
t_vec3	vec3multscalar(const t_vec3 a, double t);
t_vec3	vec3divscalar(const t_vec3 a, double t);
  
double	length3_squared(const t_vec3 *v);
double	length3(const t_vec3 *v);

// Vector Utility Functions

void	print_vec3(const t_vec3 *v);

double	dot(const t_vec3 a, const t_vec3 b);
t_vec3	vec3cross(const t_vec3 a, const t_vec3 b);
void	unit_vector(t_vec3 *v);

#endif