#ifndef _FONT_H_
#define _FONT_H_

#include "bullet.h"

enum FONT_TYPE
{
	a = 0, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
};

void InitFont();
void UninitFont();
void UpdateFont();
void DrawFont();

void SetFont(float x, float y, float width, float height, FONT_TYPE type);


#endif // !_FONT_H_
