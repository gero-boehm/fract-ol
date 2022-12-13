#include "fract_ol.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>


mlx_image_t	*g_img;
int use_double = 1;

void	on_loop(void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;
	float time_step;

	scene = param;
	mlx = scene->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		mlx_set_uniform_1i(mlx, "iterations", ++scene->iterations);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		mlx_set_uniform_1i(mlx, "iterations", --scene->iterations);

	time_step = .1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		time_step = .5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_ALT))
		time_step = .01;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		mlx_set_uniform_1f(mlx, "time", scene->time -= time_step);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		mlx_set_uniform_1f(mlx, "time", scene->time += time_step);

	int32_t x;
	int32_t y;
	mlx_get_mouse_pos(mlx, &x, &y);

	double mx = (double) x / (double) scene->width;
	double my = (double) y / (double) scene->height;

	if(mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT) && (mx != scene->mouse.x || my != scene->mouse.y))
	{
		t_vec2 difference = vec2_sub(vec2(mx, my), scene->mouse);
		scene->offset = vec2_add(difference, scene->offset);
		set_offset_uniform(mlx, &scene->offset);
	}

	scene->mouse.x = mx;
	scene->mouse.y = my;

	// scene->time += .05;
	// mlx_set_uniform_1f(mlx, "time", scene->time);
}

void	on_resize(int32_t width, int32_t height, void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;

	scene = param;
	mlx = scene->mlx;
	scene->width = width;
	scene->height = height;
	scene->aspect = (double) width / (double) height;
	mlx_resize_image(g_img, width, height);
	set_aspect_uniform(mlx, scene->aspect);
}

void on_scroll(double xdelta, double ydelta, void* param)
{
	t_scene	*scene;
	mlx_t	*mlx;
	t_vec2 difference;

	(void) xdelta;
	scene = param;
	mlx = scene->mlx;
	double step = (ydelta * scene->zoom) / 10.;
	scene->zoom += step;
	difference = vec2_sub(scene->mouse, scene->offset);
	scene->offset = vec2_add(vec2_mult_scalar(vec2_div_scalar(difference, scene->zoom), step), scene->offset);
	set_offset_uniform(mlx, &scene->offset);
	set_zoom_uniform(mlx, scene->zoom);
}

void on_keydown(mlx_key_data_t key, void *param)
{
	t_scene	*scene;
	mlx_t	*mlx;

	scene = param;
	mlx = scene->mlx;
	if (key.key == MLX_KEY_I)
		printf("i");
}

void	setup_scene(t_scene *scene)
{
	t_settings settings;

	scene->mlx = mlx_init(DEFAULT_WIDTH, DEFAULT_HEIGHT, "MLX42", true);
	if (scene->mlx == NULL)
		exit(EXIT_FAILURE);
	scene->width = DEFAULT_WIDTH;
	scene->height = DEFAULT_HEIGHT;
	scene->aspect = (double) scene->width / (double) scene->height;
	scene->zoom = DEFAULT_ZOOM;
	scene->iterations = DEFAULT_ITERATIONS;
	scene->time = 0;
	scene->mouse = vec2(.5, .5);
	scene->offset = vec2(.5, .5);
	settings.renderer = RENDERER_GPU_DOUBLE;
	settings.type = TYPE_BURNING_SHIP;
	settings.subtype = SUBTYPE_MANDELBROT;
	scene->settings = settings;
}

int	iterate(t_scene *scene, t_vec2 z, t_vec2 c)
{
	int	i;

	i = 0;
	while (i < scene->iterations)
	{
		if (scene->settings.type == TYPE_MANDELBROT)
			z = mandelbrot(z, c);
		else if (scene->settings.type == TYPE_TRICORN)
			z = tricorn(z, c);
		else if (scene->settings.type == TYPE_BURNING_SHIP)
			z = burning_ship(z, c);
		if (complex_modulus_squared(z) > 4)
			return (i);
	}
	return (0);
}

void	run(t_scene *scene)
{
	int		x;
	int		y;
	t_vec2	z;
	t_vec2	c;

	x = 0;
	y = 0;
	while (x < scene->width)
	{
		while (y < scene->height)
		{

		}
	}
}

int32_t	main(void)
{
	t_scene scene;
	mlx_t *mlx;

	setup_scene(&scene);
	mlx = scene.mlx;
	set_aspect_uniform(mlx, scene.aspect);
	set_zoom_uniform(mlx, scene.zoom);
	set_offset_uniform(mlx, &scene.offset);
	mlx_set_uniform_1i(mlx, "iterations", scene.iterations);
	mlx_set_uniform_1f(mlx, "time", scene.time);
	mlx_set_uniform_1i(mlx, "use_double", use_double);
	mlx_set_uniform_1i(mlx, "renderer", scene.settings.renderer);
	mlx_set_uniform_1i(mlx, "type", scene.settings.type);
	mlx_set_uniform_1i(mlx, "subtype", scene.settings.subtype);

	g_img = mlx_new_image(mlx, scene.width, scene.height);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &on_loop, &scene);
	mlx_resize_hook(mlx, &on_resize, &scene);
	mlx_scroll_hook(mlx, &on_scroll, &scene);
	mlx_key_hook(mlx, &on_keydown, &scene);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}