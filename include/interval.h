/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:53:54 by lbrusa            #+#    #+#             */
/*   Updated: 2024/06/23 10:16:33 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H

#include <stdbool.h>
#include <math.h>


typedef struct	s_interval
{
	double		min;
	double		max;
}				t_interval;

t_interval interval(double min, double max);

inline double size(const t_interval *i)
{
	return (i->max - i->min);
}

/*
 * The contains will return true for values including edges
 */
inline bool contains(const t_interval *i, double x)
{
	return (x >= i->min && x <= i->max);
}

/*
 * the surrounds will return false for values inside but
 * not including the boundaries of the interval
 */
inline bool surrounds(const t_interval *i, double x)
{
	return (x > i->min && x < i->max);
}

/*
 * Returns an empty interval
 */
inline t_interval empty_interval()
{
	return (t_interval){0, 0};
}

/*
 * Returns an interval that contains all values
 */
inline t_interval universe_interval()
{
	return (t_interval){-INFINITY, INFINITY};
}

#endif
