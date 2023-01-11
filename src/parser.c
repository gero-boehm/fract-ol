/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:49:58 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/11 21:55:51 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fract_ol.h"

int	streq(const char *s1, const char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*s1)
	{
		if (*s1++ != *s2++)
			return (0);
	}
	return (1);
}

int	split2(const char *str, char c, char ***result)
{
	*result = ft_split(str, c);
	return (*result == NULL);
}

size_t	arrlen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int	setup_mandelbrot(t_scene *scene)
{
	(void) scene;
	return (0);
}

int	setup_tricorn(t_scene *scene)
{
	scene->fractal.im = OP_NEG;
	return (0);
}

int	setup_burning_ship(t_scene *scene)
{
	scene->fractal.re = OP_ABS;
	scene->fractal.im = OP_ABS;
	return (0);
}

int	setup_julia(t_scene *scene)
{
	scene->type = TYPE_JULIA;
	scene->fractal.im = OP_ZERO;
	scene->time = .285;
	return (0);
}

int	eval_sub(const char *str, int i, t_scene *scene)
{
	if (i == 1)
		return (eval_ops(str, &scene->fractal));
	if (i == 2)
		return (eval_ops(str, &scene->julia));
	if (streq(str, "mandelbrot"))
		return (setup_mandelbrot(scene));
	if (streq(str, "tricorn"))
		return (setup_tricorn(scene));
	if (streq(str, "burning_ship"))
		return (setup_burning_ship(scene));
	if (streq(str, "julia"))
		return (setup_burning_ship(scene));
	return (0);
}

int	parse(int argc, const char **argv, t_scene *scene)
{
	int		i;

	i = 0;
	while (i < argc)
	{
		if (eval_sub(argv[i], i, scene))
			return (1);
		i++;
	}
	return (0);
}
