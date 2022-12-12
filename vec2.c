/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:38:28 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/12 15:59:11 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

t_vec2	vec2(double x, double y)
{
	t_vec2	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vec2	vec2_add(t_vec2 v1, t_vec2 v2)
{
	return (vec2(v1.x + v2.x, v1.y + v2.y));
}

t_vec2	vec2_sub(t_vec2 v1, t_vec2 v2)
{
	return (vec2(v1.x - v2.x, v1.y - v2.y));
}

t_vec2	vec2_div_scalar(t_vec2 v, double s)
{
	return (vec2(v.x / s, v.y / s));
}

t_vec2	vec2_mult_scalar(t_vec2 v, double s)
{
	return (vec2(v.x * s, v.y * s));
}
