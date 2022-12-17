/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:22:28 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/17 16:38:43 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fract_ol.h"

static double	apply_op(double v, t_op op)
{
	if (op == OP_NEG)
		return (-v);
	if (op == OP_ABS)
		return (fabs(v));
	if (op == OP_SIN)
		return (sin(v));
	if (op == OP_COS)
		return (cos(v));
	if (op == OP_TAN)
		return (tan(v));
	if (op == OP_ASIN)
		return (asin(v));
	if (op == OP_ACOS)
		return (acos(v));
	if (op == OP_ATAN)
		return (atan(v));
	if (op == OP_CSC)
		return (1. / sin(v));
	if (op == OP_SEC)
		return (1. / cos(v));
	if (op == OP_COT)
		return (1. / tan(v));
	if (op == OP_EXP)
		return (exp(v));
	return (v * (double) op);
}

t_ops	ops(t_op re, t_op im)
{
	t_ops	ops;

	ops.re = re;
	ops.im = im;
	return (ops);
}

t_vec2	apply_op_double(double v, t_ops ops)
{
	return (vec2(apply_op(v, ops.re), apply_op(v, ops.im)));
}

t_vec2	apply_op_vec2(t_vec2 v, t_ops ops)
{
	return (vec2(apply_op(v.x, ops.re), apply_op(v.y, ops.im)));
}
