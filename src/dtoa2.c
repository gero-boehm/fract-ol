/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:07:01 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/17 15:28:40 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static int	get_offset(double value)
{
	int		offset;

	offset = 0;
	while (value >= 1.)
	{
		offset++;
		value /= 10;
	}
	if (offset == 0)
		offset = 1;
	return (offset);
}

static void	fill_left(double value, char *buffer, int offset)
{
	long long	ival;

	ival = (long long) value;
	while (offset--)
	{
		buffer[offset] = (char)(ival % 10) + '0';
		ival /= 10;
	}
}

static void	fill_right(double value, char *buffer, int offset)
{
	long long	ival;
	int			i;

	i = 0;
	ival = (long long) value;
	while (i < 6)
	{
		value -= (double) ival;
		value *= 10;
		ival = (long long) value;
		buffer[++offset] = (char)(ival) + '0';
		i++;
	}
}

int	dtoa2(double value, char **str)
{
	int		offset;
	int		is_neg;

	is_neg = 0;
	if (value < 0)
	{
		is_neg = 1;
		value *= -1;
	}
	offset = get_offset(value);
	if (malloc2(offset + 8 + is_neg, str))
		return (1);
	if (is_neg)
		(*str)[0] = '-';
	(*str)[offset + 7 + is_neg] = 0;
	fill_left(value, *str + is_neg, offset);
	(*str)[offset + is_neg] = '.';
	fill_right(value, *str, offset + is_neg);
	return (0);
}
