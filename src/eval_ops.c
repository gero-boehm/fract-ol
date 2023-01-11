/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:22:28 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/11 21:51:33 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static t_op	eval_op(const char *str)
{
	if (streq(str, "zero"))
		return (OP_ZERO);
	if (streq(str, "neg"))
		return (OP_NEG);
	if (streq(str, "abs"))
		return (OP_ABS);
	if (streq(str, "sin"))
		return (OP_SIN);
	if (streq(str, "cos"))
		return (OP_COS);
	if (streq(str, "tan"))
		return (OP_TAN);
	if (streq(str, "asin"))
		return (OP_ASIN);
	if (streq(str, "atan"))
		return (OP_ATAN);
	if (streq(str, "csc"))
		return (OP_CSC);
	if (streq(str, "sec"))
		return (OP_SEC);
	if (streq(str, "cot"))
		return (OP_COT);
	if (streq(str, "exp"))
		return (OP_EXP);
	return (OP_NONE);
}

int	eval_ops(const char *str, t_ops *ops)
{
	char	**sub;

	if (split2(str, '_', &sub))
		return (1);
	if (arrlen(sub) != 2)
		return (2);
	ops->re = eval_op(sub[0]);
	ops->im = eval_op(sub[1]);
	return (0);
}
