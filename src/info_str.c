/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 16:12:18 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/18 16:20:00 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "fract_ol.h"






// change intrinsic functions to libft functions
static int	strcat2(char *src, char **dst)
{
	char	*new;
	size_t	length;

	length = strlen(*dst) + strlen(src);
	new = calloc(length + 1, sizeof(char));
	if (new == NULL)
		return (1);
	strcat(new, *dst);
	strcat(new, src);
	free(*dst);
	*dst = new;
	return (new == NULL);
}

static int	append_str(char *key, char *value, char **str)
{
	if (strcat2(key, str))
		return (1);
	if (strcat2(value, str))
		return (2);
	return (0);
}

static int	append_double(char *key, double value, char **str)
{
	char	*aval;

	if (strcat2(key, str))
		return (1);
	if (dtoa2(value, &aval))
		return (2);
	if (strcat2(aval, str))
		return (free(aval), 3);
	free(aval);
	return (0);
}

static int	append_ops(char *key, t_ops ops, char **str)
{
	if (strcat2(key, str))
		return (1);
	if (strcat2(get_op(ops.re), str))
		return (2);
	if (strcat2("_", str))
		return (3);
	if (strcat2(get_op(ops.im), str))
		return (4);
	return (0);
}

int	get_info_str2(t_scene *scene, char **str)
{
	if (malloc2(1, str))
		return (1);
	**str = 0;
	if (append_str("renderer:   ", get_renderer(scene), str))
		return (2);
	if (append_ops("\nfractal:    #", scene->fractal, str))
		return (3);
	if (append_str("\ntype:       ", get_type(scene), str))
		return (4);
	if (scene->type == TYPE_JULIA
		&& append_ops("\njulia:      #", scene->julia, str))
		return (5);
	if (append_double("\niterations: ", scene->iterations, str))
		return (6);
	if (append_double("\nzoom:       ", scene->zoom, str))
		return (7);
	if (append_double("\noffset.x:   ", scene->offset.x, str))
		return (8);
	if (append_double("\noffset.y:   ", scene->offset.y, str))
		return (9);
	if (append_double("\ntime:       ", scene->time, str))
		return (10);
	return (0);
}
