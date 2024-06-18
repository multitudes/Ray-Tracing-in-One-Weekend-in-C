
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
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

void	init_vec3(t_vec3 *v, double x, double y, double z);


double	vec3x(t_vec3 *v);
double 	vec3y(t_vec3 *v);
double 	vec3z(t_vec3 *v);
t_vec3	vec3negate(t_vec3 *a);

t_vec3	vec3add(t_vec3 *a, t_vec3 *b);
t_vec3	vec3substr(t_vec3 *a, t_vec3 *b);
t_vec3	vec3mult(t_vec3 *a, t_vec3 *b);
t_vec3	vec3multscalar(t_vec3 *a, double t);

t_vec3	vec3divide(t_vec3 *a, double t);
  
double	length3_squared(t_vec3 *v);
double	length3(t_vec3 *v);

// Vector Utility Functions

void	print_vec3(t_vec3 *v);

double	vec3dot(t_vec3 *a, t_vec3 *b);
t_vec3	vec3cross(t_vec3 *a, t_vec3 *b);
t_vec3	vec3unit(t_vec3 *v);

#endif