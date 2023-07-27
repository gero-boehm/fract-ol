#version 400

precision highp double;
precision highp float;
in vec2 TexCoord;
flat in int TexIndex;
out vec4 FragColor;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform double daspect;
uniform double dzoom;
uniform dvec2 doffset;
uniform float faspect;
uniform float fzoom;
uniform vec2 foffset;
uniform int iterations;
uniform float time;
uniform int renderer;
uniform int re_op;
uniform int im_op;
uniform int j_re_op;
uniform int j_im_op;
uniform int type;

vec3 hue2rgb(float h)
{
	h = mod(h, 1.) * 360.;

	float x = 1. - abs(mod(h / 60., 2.) - 1.);

	if (h >= 0. && h < 60.)
		return vec3(1., x, 0.);
	if (h >= 60. && h < 120.)
		return vec3(x, 1., 0.);
	if (h >= 120. && h < 180.)
		return vec3(0., 1., x);
	if (h >= 180. && h < 240.)
		return vec3(0., x, 1.);
	if (h >= 240. && h < 300.)
		return vec3(x, 0., 1.);
	return vec3(1., 0., x);
}

dvec2 complex_multiply(dvec2 z1, dvec2 z2)
{
	double r = z1.x * z2.x - z1.y * z2.y;
	double i = z1.x * z2.y + z1.y * z2.x;

	return dvec2(r, i);
}

double complex_modulus_squared(dvec2 z)
{
	return z.x * z.x + z.y * z.y;
}

double apply_op(double v, int op)
{
	if(op == 0)
		return v;
	if(op == 1)
		return -v;
	if(op == 2)
		return abs(v);
	if(op == 3)
		return sin(float(v));
	if(op == 4)
		return cos(float(v));
	if(op == 5)
		return tan(float(v));
	if(op == 6)
		return asin(float(v));
	if(op == 7)
		return atan(float(v));
	if(op == 9)
		return 1. / sin(float(v));
	if(op == 10)
		return 1. / cos(float(v));
	if(op == 11)
		return 1. / tan(float(v));
	if(op == 12)
		return exp(float(v));
	return 0.;
}

dvec2 fractal(dvec2 z, dvec2 c)
{
	z = dvec2(apply_op(z.x, re_op), apply_op(z.y, im_op));
	z = complex_multiply(z, z) + c;
	return z;
}

int iterate(dvec2 z, dvec2 c)
{
	for(int i = 0; i < iterations; i++)
	{
		z = fractal(z, c);
		if(complex_modulus_squared(z) > 4.)
			return i;
	}
	return 0;
}

vec2 complex_multiply(vec2 z1, vec2 z2)
{
	float r = z1.x * z2.x - z1.y * z2.y;
	float i = z1.x * z2.y + z1.y * z2.x;

	return vec2(r, i);
}

float complex_modulus_squared(vec2 z)
{
	return z.x * z.x + z.y * z.y;
}

float apply_op(float v, int op)
{
	if(op == 0)
		return v;
	if(op == 1)
		return -v;
	if(op == 2)
		return abs(v);
	if(op == 3)
		return sin(v);
	if(op == 4)
		return cos(v);
	if(op == 5)
		return tan(v);
	if(op == 6)
		return asin(v);
	if(op == 7)
		return atan(v);
	if(op == 9)
		return 1. / sin(v);
	if(op == 10)
		return 1. / cos(v);
	if(op == 11)
		return 1. / tan(v);
	if(op == 12)
		return exp(v);
	return 0.;
}

vec2 fractal(vec2 z, vec2 c)
{
	z = vec2(apply_op(z.x, re_op), apply_op(z.y, im_op));
	z = complex_multiply(z, z) + c;
	return z;
}

int iterate(vec2 z, vec2 c)
{
	for(int i = 0; i < iterations; i++)
	{
		z = fractal(z, c);
		if(complex_modulus_squared(z) > 4.)
			return i;
	}
	return 0;
}

void main()
{
	if(TexIndex == 1)
	{
		FragColor = texture(Texture1, TexCoord);
		return;
	}

	if(renderer == 0)
	{
		FragColor = texture(Texture0, TexCoord);
		return;
	}

	int result;
	if(renderer == 1)
	{
		dvec2 z;
		dvec2 c;
		if(type == 0)
		{
			z = dvec2(0., 0.);
			c = dvec2(TexCoord - doffset) * dvec2(daspect, 1.) * dzoom;
		}
		else
		{
			z = dvec2(TexCoord - doffset) * dvec2(daspect, 1.) * dzoom;
			c = dvec2(apply_op(time / 10., j_re_op), apply_op(time / 10., j_im_op));
		}
		result = iterate(z, c);
	}
	else
	{
		vec2 z;
		vec2 c;
		if(type == 0)
		{
			z = vec2(0., 0.);
			c = vec2(TexCoord - foffset) * vec2(faspect, 1.) * fzoom;
		}
		else
		{
			z = vec2(TexCoord - foffset) * vec2(faspect, 1.) * fzoom;
			c = vec2(apply_op(time / 10., j_re_op), apply_op(time / 10., j_im_op));
		}
		result = iterate(z, c);
	}
	vec3 color = mix(vec3(0., 0., 0.), hue2rgb(time), float(result) / float(iterations));
	FragColor = vec4(color, 1.0);
}
