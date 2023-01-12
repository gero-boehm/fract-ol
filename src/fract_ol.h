/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:40:49 by gbohm             #+#    #+#             */
/*   Updated: 2023/01/12 14:17:01 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <stdlib.h>
# include "MLX42/MLX42.h"

# define DEFAULT_ZOOM 5
# define DEFAULT_ITERATIONS 100
# define DEFAULT_WIDTH 256
# define DEFAULT_HEIGHT 256

# define CHAR_WIDTH 7
# define CHAR_HEIGHT 13
# define PADDING 5
# define CHAR_PADDING 1
# define LINE_PADDING 1
# define FONT_SIZE 1

typedef enum e_renderer {
	RENDERER_CPU,
	RENDERER_GPU_DOUBLE,
	RENDERER_GPU_FLOAT,
}	t_renderer;

typedef enum e_color_component {
	R,
	G,
	B,
	A,
}	t_color_component;

typedef enum e_op {
	OP_NONE,
	OP_NEG,
	OP_ABS,
	OP_SIN,
	OP_COS,
	OP_TAN,
	OP_ASIN,
	OP_ATAN,
	OP_CSC,
	OP_SEC,
	OP_COT,
	OP_EXP,
	OP_ZERO,
	OP_INVALID,
}	t_op;

typedef enum e_type {
	TYPE_MANDELBROT,
	TYPE_JULIA,
}	t_type;

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

typedef struct s_ops {
	t_op	re;
	t_op	im;
}	t_ops;

typedef struct s_scene {
	mlx_t		*mlx;
	uint32_t	width;
	uint32_t	height;
	mlx_image_t	*img;
	mlx_image_t	*info_img;
	double		aspect;
	double		zoom;
	t_vec2		mouse;
	t_vec2		offset;
	int			iterations;
	float		time;
	t_renderer	renderer;
	t_ops		fractal;
	t_ops		julia;
	t_type		type;
}	t_scene;

void		init_scene(t_scene *scene);
int			init_mlx2(t_scene *scene);
void		setup_hooks(t_scene *scene);

t_vec2		vec2(double x, double y);
t_vec2		vec2_add(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_sub(t_vec2 v1, t_vec2 v2);
t_vec2		vec2_div_scalar(t_vec2 v, double s);
t_vec2		vec2_mult_scalar(t_vec2 v, double s);

t_vec2		mandelbrot(t_vec2 z, t_vec2 c);
t_vec2		tricorn(t_vec2 z, t_vec2 c);
t_vec2		burning_ship(t_vec2 z, t_vec2 c);

t_vec2		complex_mult(t_vec2 z1, t_vec2 z2);
t_vec2		complex_add(t_vec2 z1, t_vec2 z2);
double		complex_modulus_squared(t_vec2 z);

void		on_loop(void *param);
void		on_resize(int32_t width, int32_t height, void *param);
void		on_scroll(double xdelta, double ydelta, void *param);
void		on_keydown(mlx_key_data_t key, void *param);

uint32_t	hue2rgb(float h);

void		color_pixel(t_scene *scene, int x, int y, int result);

void		calculate(t_scene *scene);
void		render_info(t_scene *scene);

int			malloc2(size_t size, char **str);
int			dtoa2(double value, char **str);
t_ops		ops(t_op re, t_op im);
t_vec2		apply_op_double(double v, t_ops ops);
t_vec2		apply_op_vec2(t_vec2 v, t_ops ops);

void		update_uniforms(t_scene *scene);

t_op		get_op_for_key(keys_t key);

void		update_iterations(t_scene *scene, int *rerender);
void		update_time(t_scene *scene, int *rerender);
void		update_mouse(t_scene *scene, int *rerender);
void		update_ops(t_scene *scene, mlx_key_data_t key, int *rerender);
void		update_settings(t_scene *scene, keys_t key, int *rerender);

int			get_info_str2(t_scene *scene, char **str);
int			get_rows(char *str);
int			get_columns(char *str);
char		*get_renderer(t_scene *scene);
char		*get_op(t_op op);
char		*get_type(t_scene *scene);

int			streq(const char *s1, const char *s2);
size_t		arrlen(char **arr);
int			eval_ops(const char *str, t_ops *ops);
int			parse(int argc, const char **argv, t_scene *scene);
int			split2(const char *str, char c, char ***result);
void		free_all(char **arr);

int			setup_tricorn(t_scene *scene);
int			setup_burning_ship(t_scene *scene);
int			setup_julia(t_scene *scene);

#endif