/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:22:28 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/18 15:26:16 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fract_ol.h"

static double	apply_op(double v, t_op op)
{
	if (op == OP_NONE)
		return (v);
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
	return (0.);
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

t_op	get_op_for_key(keys_t key)
{
	const keys_t	keys[] = {MLX_KEY_Q, MLX_KEY_W, MLX_KEY_E, MLX_KEY_R,
		MLX_KEY_T, MLX_KEY_Y, MLX_KEY_U, MLX_KEY_I, MLX_KEY_O, MLX_KEY_P,
		MLX_KEY_A, MLX_KEY_S, MLX_KEY_D};
	const t_op		ops[] = {OP_NONE, OP_NEG, OP_ABS, OP_SIN, OP_COS,
		OP_TAN, OP_ASIN, OP_ATAN, OP_CSC, OP_SEC, OP_COT, OP_EXP, OP_ZERO};
	int				i;

	i = 0;
	while (i < 13)
	{
		if (key == keys[i])
			return (ops[i]);
		i++;
	}
	return (OP_INVALID);
}
