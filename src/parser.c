/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:49:58 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 09:02:56 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static int	eval_sub(const char *str, int i, t_scene *scene)
{
	if (i == 2)
		return (eval_ops(str, &scene->fractal));
	if (i == 3)
		return (eval_ops(str, &scene->julia));
	if (streq(str, "mandelbrot"))
		return (0);
	if (streq(str, "tricorn"))
		return (setup_tricorn(scene));
	if (streq(str, "burning_ship"))
		return (setup_burning_ship(scene));
	if (streq(str, "julia"))
		return (setup_julia(scene));
	return (1);
}

int	parse(int argc, const char **argv, t_scene *scene)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (eval_sub(argv[i], i, scene))
			return (1);
		i++;
	}
	return (0);
}
