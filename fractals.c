/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:05:54 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/13 16:37:03 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fract-ol.h"

t_vec2	mandelbrot(t_vec2 z, t_vec2 c)
{
	return (vec2_add(vec2_mult(z, z), c));
}

t_vec2	tricorn(t_vec2 z, t_vec2 c)
{
	z = vec2_mult(z, vec2(1, -1));
	return (vec2_add(vec2_mult(z, z), c));
}

t_vec2	burning_ship(t_vec2 z, t_vec2 c)
{
	z = vec2(abs(z.x), abs(z.y));
	return (vec2_add(vec2_mult(z, z), c));
}
