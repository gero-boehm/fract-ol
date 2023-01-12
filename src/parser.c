/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:49:58 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 10:45:20 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fract_ol.h"

static float	get_whole(const char *str)
{
	if (!str)
		return (0.);
	return (ft_atoi(str));
}

static float	get_fraction(const char *str)
{
	float	result;
	size_t	length;

	if (!str)
		return (0.);
	length = ft_strlen(str);
	result = ft_atoi(str);
	while (length--)
		result /= 10;
	return (result);
}

static int	eval_time(const char *str, float *time)
{
	char	**sub;
	int		neg;

	neg = 0;
	if (*str == '-')
	{
		neg = 1;
		str++;
	}
	if (split2(str, '.', &sub))
		return (1);
	*time = 0.;
	if (*str == '.')
		*time += get_fraction(sub[0]);
	else
	{
		*time += get_whole(sub[0]);
		*time += get_fraction(sub[1]);
	}
	if (neg)
		*time *= -1;
	free_all(sub);
	return (0);
}

static int	eval_sub(const char *str, int i, t_scene *scene)
{
	if (i == 2)
		return (eval_ops(str, &scene->fractal));
	if (i == 3)
		return (eval_ops(str, &scene->julia));
	if (i == 4)
		return (eval_time(str, &scene->time));
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
