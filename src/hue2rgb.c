/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hue2rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:11:34 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/11 18:28:13 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fract_ol.h"

uint32_t	hue2rgb(float h)
{
	uint32_t	x;

	h = fmod(h, 1.) * 360.;
	x = round((1. - fabs(fmod(h / 60., 2.) - 1.)) * 255.);
	if (h >= 0 && h < 60)
		return (0xff0000ff | x << 16);
	if (h >= 60 && h < 120)
		return (0x00ff00ff | x << 24);
	if (h >= 120 && h < 180)
		return (0x00ff00ff | x << 8);
	if (h >= 180 && h < 240)
		return (0x0000ffff | x << 16);
	if (h >= 240 && h < 300)
		return (0x0000ffff | x << 24);
	return (0xff0000ff | x << 8);
}
