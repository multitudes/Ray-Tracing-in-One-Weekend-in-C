/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:59:14 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/20 17:11:21 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

typedef struct 	s_hit_record {
    t_point3 	p;
    t_vec3 		normal;
    double 		t;
} 				t_hit_record;

/* translated from cpp - remains to see if I will incorporate this into every object*/
typedef struct 	s_hittable{
    bool 		(*hit)(const t_ray* r, double ray_tmin, double ray_tmax, t_hit_record* rec);
} 				t_hittable;

#endif


