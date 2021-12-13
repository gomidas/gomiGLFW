#pragma once
#ifndef _MYCOLOR_
#define _MYCOLOR_
#include "myMath.h"
#endif

typedef struct FRGB
{
	float r; float g; float b;
	FRGB() {};

	FRGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b)
	{
		if (_r > 1.0f) {
			clamp(_r, 0.0f, 1.0f); r = _r;
		}
		if (_g > 1.0f) {
			clamp(_g, 0.0f, 1.0f); g = _g;
		}
		if (_g > 1.0f) {
			clamp(_g, 0.0f, 1.0f); g = _g;
		}
	}
};

static FRGB RGBTOFRGB(float r, float g, float b)
{
		clamp((int)r, 0, 255);
		clamp((int)g, 0, 255);
		clamp((int)b, 0, 255);

		r = (float)(r / 255);
		g = (float)(g / 255);
		b = (float)(b / 255);

		return FRGB(r,g,b);
};

static class COLORNAME {
	FRGB frgb;
	COLORNAME(FRGB arg) : frgb(arg) {}
public:
	static const FRGB RED;
	static const FRGB GREEN;
	static const FRGB BLUE;
	static const FRGB ORANGE;

	operator FRGB() const {
		return frgb;
	}
};
