/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:21:31 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/17 17:49:14 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
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

void	print_char(char c)
{
	int i = (int) c - 32;

	int iy = 0;
	while (iy < CHAR_HEIGHT)
	{
		int ix = 0;
		while (ix < CHAR_WIDTH)
		{
			// scene->info_img->pixels[(dy + iy) * width + dx + ix] = FONT[iy / FONT_SIZE * CHAR_WIDTH * 95 + ix / FONT_SIZE];
			printf("%c", FONT[i * CHAR_WIDTH * CHAR_HEIGHT + iy * CHAR_WIDTH + ix] == '1' ? '0' : '.');
			ix++;
		}
		printf("\n");
		iy++;
	}
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
	if (op == OP_ACOS)
		return ("acos");
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

int	strcat2(char *src, char **dst)
{
	char	*new;
	size_t	length;

	length = strlen(*dst) + strlen(src);
	new = calloc(length + 1, 1);
	if (new == NULL)
		return (1);
	strcat(new, *dst);
	strcat(new, src);
	free(*dst);
	*dst = new;
	return (new == NULL);
}

int	append_str(char *key, char *value, char **str)
{
	if (strcat2(key, str))
		return (1);
	if (strcat2(value, str))
		return (2);
	return (0);
}

int	append_double(char *key, double value, char **str)
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

int	append_ops(char *key, t_ops ops, char **str)
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

void	render_info(t_scene *scene)
{
	char	*str;

	if (get_info_str2(scene, &str))
		return ;
	int cx = get_columns(str);
	int cy = get_rows(str);
	int width = (cx * CHAR_WIDTH + (cx - 1) * CHAR_PADDING + PADDING * 2) * FONT_SIZE;
	int height = (cy * CHAR_HEIGHT + (cy - 1) * LINE_PADDING + PADDING * 2) * FONT_SIZE;

	if (scene->info_img != NULL)
		mlx_delete_image(scene->mlx, scene->info_img);
	scene->info_img = mlx_new_image(scene->mlx, width, height);
	if (scene->info_img == NULL)
		exit(EXIT_FAILURE);
	mlx_image_to_window(scene->mlx, scene->info_img, 0, 0);
	int dx = PADDING * FONT_SIZE;
	int dy = PADDING * FONT_SIZE;
	while(*str)
	{
		if (*str == '\n')
		{
			dy += (CHAR_HEIGHT + LINE_PADDING) * FONT_SIZE;
			dx = PADDING * FONT_SIZE;
			str++;
			continue;
		}

		int i = (int) *str - 32;
		int iy = 0;
		while (iy < CHAR_HEIGHT * FONT_SIZE)
		{
			int ix = 0;
			while (ix < CHAR_WIDTH * FONT_SIZE)
			{
				// scene->info_img->pixels[(dy + iy) * width + dx + ix] = FONT[iy / FONT_SIZE * CHAR_WIDTH * 95 + ix / FONT_SIZE];
				uint32_t color = FONT[i * CHAR_WIDTH * CHAR_HEIGHT + iy / FONT_SIZE * CHAR_WIDTH + ix / FONT_SIZE] == '1' ? 0xffffffff : 0x00000000;
				mlx_put_pixel(scene->info_img, dx + ix, dy + iy, color);
				// printf("%c", FONT[i * CHAR_WIDTH * CHAR_HEIGHT + iy / FONT_SIZE * CHAR_WIDTH + ix / FONT_SIZE] == '1' ? '0' : '.');
				ix++;
			}
			// printf("\n");
			iy++;
		}
		dx += (CHAR_WIDTH + CHAR_PADDING) * FONT_SIZE;
		str++;
	}
}
