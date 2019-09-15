#ifndef _BULLET_H_
#define _BULLET_H_

#include <d3d9.h>
#include <d3dx9.h>
#include "player.h"
#include "Fujino.h"

#define BULLETSPEED (8)
#define BULLETSIZE (32)
#define BULLET_MAX (64)
enum BULLET_ALPHA
{
	a = 0, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, ALPHA_MAX
};

typedef struct
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 move;
	float velocity;
	bool isUse;
	float angle;
	BULLET_ALPHA alpha;
	Circle collision;
}BULLET;

void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

void createBullet(float x, float y, float size, BULLET_ALPHA alpha);
BULLET *getBullet();

#endif // !_BULLET_H_

