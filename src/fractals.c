/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:05:54 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/14 14:58:41 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fract_ol.h"

t_vec2	mandelbrot(t_vec2 z, t_vec2 c)
{
	return (complex_add(complex_mult(z, z), c));
}

t_vec2	tricorn(t_vec2 z, t_vec2 c)
{
	z = complex_mult(z, vec2(1, -1));
	return (complex_add(complex_mult(z, z), c));
}

t_vec2	burning_ship(t_vec2 z, t_vec2 c)
{
	z = vec2(fabs(z.x), fabs(z.y));
	return (complex_add(complex_mult(z, z), c));
}
