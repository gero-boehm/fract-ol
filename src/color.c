/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:42:19 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/15 13:09:30 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static uint8_t	get_component(uint32_t color, t_color_component component)
{
	if (component == R)
		return ((uint8_t)(color >> 24 & 0xff));
	if (component == G)
		return ((uint8_t)(color >> 16 & 0xff));
	if (component == B)
		return ((uint8_t)(color >> 8 & 0xff));
	if (component == A)
		return ((uint8_t)(color & 0xff));
	return (0);
}

static uint8_t	lerp(uint8_t min, uint8_t max, double t)
{
	return ((max - min) * t + min);
}

uint32_t	lerp_color(uint32_t min, uint32_t max, double t)
{
	uint32_t	result;

	result = 0;
	result |= lerp(get_component(min, R), get_component(max, R), t) << 24;
	result |= lerp(get_component(min, G), get_component(max, G), t) << 16;
	result |= lerp(get_component(min, B), get_component(max, B), t) << 8;
	result |= lerp(get_component(min, A), get_component(max, A), t);
	return (result);
}

void	set_color_at(uint8_t *pixel, uint32_t color)
{
	*pixel++ = get_component(color, R);
	*pixel++ = get_component(color, G);
	*pixel++ = get_component(color, B);
	*pixel++ = get_component(color, A);
}
