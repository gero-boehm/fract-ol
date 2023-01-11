/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 19:21:31 by gbohm             #+#    #+#             */
/*   Updated: 2022/12/19 05:11:44 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static int	is_filled(int i, int ix, int iy)
{
	int	offset_i;
	int	offset_iy;
	int	offset_ix;

	offset_i = i * CHAR_WIDTH * CHAR_HEIGHT;
	offset_iy = iy / FONT_SIZE * CHAR_WIDTH;
	offset_ix = ix / FONT_SIZE;
	return (FONT[offset_i + offset_iy + offset_ix] == '1');
}

static uint32_t	get_color(int filled)
{
	if (filled)
		return (0xffffffff);
	return (0x00000000);
}

static void	put_char(mlx_image_t *img, char c, int ox, int oy)
{
	int			i;
	int			ix;
	int			iy;
	uint32_t	color;

	i = (int) c - 32;
	iy = 0;
	while (iy < CHAR_HEIGHT * FONT_SIZE)
	{
		ix = 0;
		while (ix < CHAR_WIDTH * FONT_SIZE)
		{
			color = get_color(is_filled(i, ix, iy));
			mlx_put_pixel(img, ox + ix, oy + iy, color);
			ix++;
		}
		iy++;
	}
}

static int	prepare_img2(char *str, t_scene *scene)
{
	int	cx;
	int	cy;
	int	width;
	int	height;

	cx = get_columns(str);
	cy = get_rows(str);
	width = (cx * CHAR_WIDTH + (cx - 1) * CHAR_PADDING + PADDING * 2)
		* FONT_SIZE;
	height = (cy * CHAR_HEIGHT + (cy - 1) * LINE_PADDING + PADDING * 2)
		* FONT_SIZE;
	if (scene->info_img != NULL)
		mlx_delete_image(scene->mlx, scene->info_img);
	scene->info_img = mlx_new_image(scene->mlx, width, height);
	if (scene->info_img == NULL)
		return (1);
	mlx_image_to_window(scene->mlx, scene->info_img, 0, 0);
	return (0);
}

void	render_info(t_scene *scene)
{
	char	*str;
	char	*cursor;
	int		ox;
	int		oy;

	if (get_info_str2(scene, &str))
		return ;
	if (prepare_img2(str, scene))
		return ;
	ox = PADDING * FONT_SIZE;
	oy = PADDING * FONT_SIZE;
	cursor = str - 1;
	while (*(++cursor))
	{
		if (*cursor == '\n')
		{
			oy += (CHAR_HEIGHT + LINE_PADDING) * FONT_SIZE;
			ox = PADDING * FONT_SIZE;
			continue ;
		}
		put_char(scene->info_img, *cursor, ox, oy);
		ox += (CHAR_WIDTH + CHAR_PADDING) * FONT_SIZE;
	}
	free(str);
}
