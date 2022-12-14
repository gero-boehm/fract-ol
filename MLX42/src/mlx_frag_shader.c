/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_frag_shader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:34:59 by W2wizard          #+#    #+#             */
/*   Updated: 2023/01/11 18:25:48 by gbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If you wish to modify this file edit the .vert or .frag file!

#include "MLX42/MLX42_Int.h"

const char* frag_shader = "#version 400\n"
	"precision highp double;\n"
	"precision highp float;\n"
	"in vec2 TexCoord;\n"
	"flat in int TexIndex;\n"
	"out vec4 FragColor;\n"
	"uniform sampler2D Texture0;\n"
	"uniform sampler2D Texture1;\n"
	"uniform double daspect;\n"
	"uniform double dzoom;\n"
	"uniform dvec2 doffset;\n"
	"uniform float faspect;\n"
	"uniform float fzoom;\n"
	"uniform vec2 foffset;\n"
	"uniform int iterations;\n"
	"uniform float time;\n"
	"uniform int renderer;\n"
	"uniform int re_op;\n"
	"uniform int im_op;\n"
	"uniform int j_re_op;\n"
	"uniform int j_im_op;\n"
	"uniform int type;\n"
	"\n"
	"vec3 hue2rgb(float h)\n"
	"{\n"
	"	h = mod(h, 1.) * 360.;"
	"	\n"
	"	float x = 1. - abs(mod(h / 60., 2.) - 1.);\n"
	"	\n"
	"	if (h >= 0. && h < 60.)\n"
	"		return vec3(1., x, 0.);\n"
	"	if (h >= 60. && h < 120.)\n"
	"		return vec3(x, 1., 0.);\n"
	"	if (h >= 120. && h < 180.)\n"
	"		return vec3(0., 1., x);\n"
	"	if (h >= 180. && h < 240.)\n"
	"		return vec3(0., x, 1.);\n"
	"	if (h >= 240. && h < 300.)\n"
	"		return vec3(x, 0., 1.);\n"
	"	return vec3(1., 0., x);\n"
	"}\n"
	"\n"
	"dvec2 complex_multiply(dvec2 z1, dvec2 z2)\n"
	"{\n"
	"	double r = z1.x * z2.x - z1.y * z2.y;\n"
	"	double i = z1.x * z2.y + z1.y * z2.x;\n"
	"\n"
	"	return dvec2(r, i);\n"
	"}\n"
	"\n"
	"double complex_modulus_squared(dvec2 z)\n"
	"{\n"
	"	return z.x * z.x + z.y * z.y;\n"
	"}\n"
	"\n"
	"double apply_op(double v, int op)\n"
	"{\n"
	"	if(op == 0)\n"
	"		return v;\n"
	"	if(op == 1)\n"
	"		return -v;\n"
	"	if(op == 2)\n"
	"		return abs(v);\n"
	"	if(op == 3)\n"
	"		return sin(float(v));\n"
	"	if(op == 4)\n"
	"		return cos(float(v));\n"
	"	if(op == 5)\n"
	"		return tan(float(v));\n"
	"	if(op == 6)\n"
	"		return asin(float(v));\n"
	"	if(op == 7)\n"
	"		return atan(float(v));\n"
	"	if(op == 9)\n"
	"		return 1. / sin(float(v));\n"
	"	if(op == 10)\n"
	"		return 1. / cos(float(v));\n"
	"	if(op == 11)\n"
	"		return 1. / tan(float(v));\n"
	"	if(op == 12)\n"
	"		return exp(float(v));\n"
	"	return 0.;\n"
	"}\n"
	"\n"
	"dvec2 fractal(dvec2 z, dvec2 c)\n"
	"{\n"
	"	z = dvec2(apply_op(z.x, re_op), apply_op(z.y, im_op));\n"
	"	z = complex_multiply(z, z) + c;\n"
	"	return z;\n"
	"}\n"
	"\n"
	"int iterate(dvec2 z, dvec2 c)\n"
	"{\n"
	"	for(int i = 0; i < iterations; i++)\n"
	"	{\n"
	"		z = fractal(z, c);\n"
	"		if(complex_modulus_squared(z) > 4.)\n"
	"			return i;\n"
	"	}\n"
	"	return 0;\n"
	"}\n"
	"\n"
	"vec2 complex_multiply(vec2 z1, vec2 z2)\n"
	"{\n"
	"	float r = z1.x * z2.x - z1.y * z2.y;\n"
	"	float i = z1.x * z2.y + z1.y * z2.x;\n"
	"\n"
	"	return vec2(r, i);\n"
	"}\n"
	"\n"
	"float complex_modulus_squared(vec2 z)\n"
	"{\n"
	"	return z.x * z.x + z.y * z.y;\n"
	"}\n"
	"\n"
	"float apply_op(float v, int op)\n"
	"{\n"
	"	if(op == 0)\n"
	"		return v;\n"
	"	if(op == 1)\n"
	"		return -v;\n"
	"	if(op == 2)\n"
	"		return abs(v);\n"
	"	if(op == 3)\n"
	"		return sin(v);\n"
	"	if(op == 4)\n"
	"		return cos(v);\n"
	"	if(op == 5)\n"
	"		return tan(v);\n"
	"	if(op == 6)\n"
	"		return asin(v);\n"
	"	if(op == 7)\n"
	"		return atan(v);\n"
	"	if(op == 9)\n"
	"		return 1. / sin(v);\n"
	"	if(op == 10)\n"
	"		return 1. / cos(v);\n"
	"	if(op == 11)\n"
	"		return 1. / tan(v);\n"
	"	if(op == 12)\n"
	"		return exp(v);\n"
	"	return 0.;\n"
	"}\n"
	"\n"
	"vec2 fractal(vec2 z, vec2 c)\n"
	"{\n"
	"	z = vec2(apply_op(z.x, re_op), apply_op(z.y, im_op));\n"
	"	z = complex_multiply(z, z) + c;\n"
	"	return z;\n"
	"}\n"
	"\n"
	"int iterate(vec2 z, vec2 c)\n"
	"{\n"
	"	for(int i = 0; i < iterations; i++)\n"
	"	{\n"
	"		z = fractal(z, c);\n"
	"		if(complex_modulus_squared(z) > 4.)\n"
	"			return i;\n"
	"	}\n"
	"	return 0;\n"
	"}\n"
	"\n"
	"void main()\n"
	"{\n"
	"	if(TexIndex == 1)\n"
	"	{\n"
	"		FragColor = texture(Texture1, TexCoord);\n"
	"		return;\n"
	"	}\n"
	"\n"
	"	if(renderer == 0)\n"
	"	{\n"
	"		FragColor = texture(Texture0, TexCoord);\n"
	"		return;\n"
	"	}\n"
	"\n"
	"	int result;\n"
	"	if(renderer == 1)\n"
	"	{\n"
	"		dvec2 z;\n"
	"		dvec2 c;\n"
	"		if(type == 0)\n"
	"		{\n"
	"			z = dvec2(0., 0.);\n"
	"			c = dvec2(TexCoord - doffset) * dvec2(daspect, 1.) * dzoom;\n"
	"		}\n"
	"		else\n"
	"		{\n"
	"			z = dvec2(TexCoord - doffset) * dvec2(daspect, 1.) * dzoom;\n"
	"			c = dvec2(apply_op(time / 10., j_re_op), apply_op(time / 10., j_im_op));\n"
	"		}\n"
	"		result = iterate(z, c);\n"
	"	}\n"
	"	else\n"
	"	{\n"
	"		vec2 z;\n"
	"		vec2 c;\n"
	"		if(type == 0)\n"
	"		{\n"
	"			z = vec2(0., 0.);\n"
	"			c = vec2(TexCoord - foffset) * vec2(faspect, 1.) * fzoom;\n"
	"		}\n"
	"		else\n"
	"		{\n"
	"			z = vec2(TexCoord - foffset) * vec2(faspect, 1.) * fzoom;\n"
	"			c = vec2(apply_op(time / 10., j_re_op), apply_op(time / 10., j_im_op));\n"
	"		}\n"
	"		result = iterate(z, c);\n"
	"	}\n"
	"	vec3 color = mix(vec3(0., 0., 0.), hue2rgb(time), float(result) / float(iterations));\n"
	"	FragColor = vec4(color, 1.0);\n"
	"}\n";
