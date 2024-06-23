
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
	union {
        struct {
            double x;
            double y;
            double z;
        };
        struct {
            double r;
            double g;
            double b;
        };
	};
}				t_vec3, t_color, t_point3;

t_vec3		vec3(double x, double y, double z);
t_point3	point3(double x, double y, double z);

t_vec3	vec3negate(const t_vec3 a);
t_vec3	vec3add(const t_vec3 a, const t_vec3 b);
t_vec3	vec3substr(const t_vec3 a, const t_vec3 b);
t_vec3	vec3mult(const t_vec3 a, const t_vec3 b);
t_vec3	vec3multscalar(const t_vec3 a, double t);
t_vec3	vec3divscalar(const t_vec3 a, double t);
  
double	length3_squared(const t_vec3 v);
double	length3(const t_vec3 v);

// Vector Utility Functions

void	print_vec3(const t_vec3 *v);

double	dot(const t_vec3 a, const t_vec3 b);
t_vec3	vec3cross(const t_vec3 a, const t_vec3 b);

t_vec3	random_vec3();
t_vec3	random_vec3_min_max(double min, double max);

inline t_vec3 unit_vector(t_vec3 v)
{
	return vec3divscalar(v, length3(v));
}

/*
 * Random vector in unit sphere
 */
inline t_vec3 random_in_unit_sphere() 
{
    while (1) {
        t_vec3 p = random_vec3_min_max(-1,1);
        if (length3_squared(p) < 1)
            return p;
    }
}

/*
 * Random unit vector in unit 
 */
inline t_vec3 random_unit_vector() 
{
    return unit_vector(random_in_unit_sphere());
}

/*
 * Random vector on the correct hemisphere. We just need to check the dot product
 * of the random vector with the normal. If it is negative, we negate the vector.
 * We acually just care about having a random vector in the hemisphere of the normal.
 */
inline t_vec3 random_on_hemisphere(const t_vec3 normal) 
{
    t_vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return vec3negate(on_unit_sphere);
}


#endif