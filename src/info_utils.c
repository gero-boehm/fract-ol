/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:16:06 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/18 16:16:25 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	get_rows(char *str)
{
	int	rows;

	rows = 1;
	while (*str)
	{
		if (*str == '\n')
			rows++;
		str++;
	}
	return (rows);
}

int	get_columns(char *str)
{
	int	columns;
	int	count;

	columns = 0;
	count = 0;
	while (*str)
	{
		if (*str == '\n')
		{
			if (count > columns)
				columns = count;
			count = 0;
		}
		else
			count++;
		str++;
	}
	if (count > columns)
		columns = count;
	return (columns);
}

char	*get_renderer(t_scene *scene)
{
	if (scene->renderer == RENDERER_CPU)
		return ("cpu");
	if (scene->renderer == RENDERER_GPU_DOUBLE)
		return ("gpu_double");
	if (scene->renderer == RENDERER_GPU_FLOAT)
		return ("gpu_float");
	return ("(null)");
}

char	*get_op(t_op op)
{
	if (op == OP_NONE)
		return ("none");
	if (op == OP_NEG)
		return ("neg");
	if (op == OP_ABS)
		return ("abs");
	if (op == OP_SIN)
		return ("sin");
	if (op == OP_COS)
		return ("cos");
	if (op == OP_TAN)
		return ("tan");
	if (op == OP_ASIN)
		return ("asin");
	if (op == OP_ATAN)
		return ("atan");
	if (op == OP_CSC)
		return ("csc");
	if (op == OP_SEC)
		return ("sec");
	if (op == OP_COT)
		return ("cot");
	if (op == OP_EXP)
		return ("exp");
	return ("zero");
}

char	*get_type(t_scene *scene)
{
	if (scene->type == TYPE_MANDELBROT)
		return ("mandelbrot");
	if (scene->type == TYPE_JULIA)
		return ("julia");
	return ("(null)");
}
