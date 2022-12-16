/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:21:31 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/16 02:46:45 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
			// scene->info->pixels[(dy + iy) * width + dx + ix] = FONT[iy / FONT_SIZE * CHAR_WIDTH * 95 + ix / FONT_SIZE];
			printf("%c", FONT[i * CHAR_WIDTH * CHAR_HEIGHT + iy * CHAR_WIDTH + ix] == '1' ? '0' : '.');
			ix++;
		}
		printf("\n");
		iy++;
	}
}

char	*get_renderer(t_scene *scene)
{
	if (scene->settings.renderer == RENDERER_CPU)
		return ("cpu");
	if (scene->settings.renderer == RENDERER_GPU_DOUBLE)
		return ("gpu_double");
	if (scene->settings.renderer == RENDERER_GPU_FLOAT)
		return ("gpu_float");
	return ("(null)");
}

char	*get_op(t_op op)
{
	if(op == OP_NONE)
		return ("none");
	if(op == OP_NEG)
		return ("neg");
	if(op == OP_ABS)
		return ("abs");
	if(op == OP_SIN)
		return ("sin");
	if(op == OP_COS)
		return ("cos");
	if(op == OP_TAN)
		return ("tan");
	if(op == OP_ASIN)
		return ("asin");
	if(op == OP_ACOS)
		return ("acos");
	if(op == OP_ATAN)
		return ("atan");
	if(op == OP_CSC)
		return ("csc");
	if(op == OP_SEC)
		return ("sec");
	if(op == OP_COT)
		return ("cot");
	if(op == OP_EXP)
		return ("exp");
	return ("zero");
}

char	*get_type(t_scene *scene)
{
	if (scene->settings.type == TYPE_MANDELBROT)
		return ("mandelbrot");
	if (scene->settings.type == TYPE_JULIA)
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
	int	ival;

	ival = (int) value;
	while (offset--)
	{
		buffer[offset] = (char)(ival % 10) + '0';
		ival /= 10;
	}
}

static void	fill_right(double value, char *buffer, int offset)
{
	int	ival;
	int	i;

	i = 0;
	ival = (int) value;
	while (i < 6)
	{
		value -= (double) ival;
		value *= 10;
		ival = (int) value;
		buffer[++offset] = (char)(ival) + '0';
		i++;
	}
}

char	*dtoa(double value)
{
	char	*buffer;
	int		offset;

	offset = get_offset(value);
	buffer = malloc(offset + 8);
	if (buffer == NULL)
		return (NULL);
	buffer[offset + 7] = 0;
	fill_left(value, buffer, offset);
	buffer[offset] = '.';
	fill_right(value, buffer, offset);
	return (buffer);
}

void render_info(t_scene *scene)
{
	char *str = calloc(1, 1);
	strcat2("renderer: ", &str);
	strcat2(get_renderer(scene), &str);
	strcat2("\nfractal:  #", &str);
	strcat2(get_op(scene->settings.re_op), &str);
	strcat2("_", &str);
	strcat2(get_op(scene->settings.im_op), &str);
	strcat2("\ntype:     ", &str);
	strcat2(get_type(scene), &str);
	strcat2("\nzoom:     ", &str);
	strcat2(dtoa(scene->zoom), &str);
	strcat2("\noffset.x: ", &str);
	strcat2(dtoa(scene->offset.x), &str);
	strcat2("\noffset.y: ", &str);
	strcat2(dtoa(scene->offset.y), &str);

	int cx = get_columns(str);
	int cy = get_rows(str);
	int width = (cx * CHAR_WIDTH + (cx - 1) * CHAR_PADDING + PADDING * 2) * FONT_SIZE;
	int height = (cy * CHAR_HEIGHT + (cy - 1) * LINE_PADDING + PADDING * 2) * FONT_SIZE;

	if (scene->info != NULL)
		mlx_delete_image(scene->mlx, scene->info);
	scene->info = mlx_new_image(scene->mlx, width, height);
	if (scene->info == NULL)
		exit(EXIT_FAILURE);
	mlx_image_to_window(scene->mlx, scene->info, 0, 0);
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
				// scene->info->pixels[(dy + iy) * width + dx + ix] = FONT[iy / FONT_SIZE * CHAR_WIDTH * 95 + ix / FONT_SIZE];
				uint32_t color = FONT[i * CHAR_WIDTH * CHAR_HEIGHT + iy / FONT_SIZE * CHAR_WIDTH + ix / FONT_SIZE] == '1' ? 0xffffffff : 0x00000000;
				mlx_put_pixel(scene->info, dx + ix, dy + iy, color);
				printf("%c", FONT[i * CHAR_WIDTH * CHAR_HEIGHT + iy / FONT_SIZE * CHAR_WIDTH + ix / FONT_SIZE] == '1' ? '0' : '.');
				ix++;
			}
			printf("\n");
			iy++;
		}
		dx += (CHAR_WIDTH + CHAR_PADDING) * FONT_SIZE;
		str++;
	}
}

void	toggle_info(t_scene *scene)
{
	if (scene->info != NULL)
	{
		mlx_delete_image(scene->mlx, scene->info);
		scene->info = NULL;
	}

	// print_char('0');
	// return;
	render_info(scene);
}
