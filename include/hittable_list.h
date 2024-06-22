/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable_list.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:21:39 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/21 11:05:30 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"


typedef struct 	s_hittablelist {
	t_hittable 	**list;
	int 		size;
} 				t_hittablelist; 

bool hit(t_hittablelist *list, const t_ray* r, double ray_tmin, double ray_tmax, t_hit_record* rec);



#endif
