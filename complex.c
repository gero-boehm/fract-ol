/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:42:09 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/13 16:53:56 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

t_vec2	complex_multiply(t_vec2 z1, t_vec2 z2)
{
	return (vec2(
			z1.x * z2.x - z1.y * z2.y,
			z1.x * z2.y + z1.y * z2.x
		));
}

t_vec2	complex_add(t_vec2 z1, t_vec2 z2)
{
	return (vec2_add(z1, z2));
}

double	complex_modulus_squared(t_vec2 z)
{
	return (z.x * z.x + z.y * z.y);
}
