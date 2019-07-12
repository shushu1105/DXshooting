#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include <d3d9.h>
#include <d3dx9.h>

typedef struct EXPLOSION
{
	D3DXVECTOR4 position;
	D3DXVECTOR2 size;
};



void InitExplosion();
void UninitExplosion();
void UpdateExplosion();
void DrawExplosion();


#endif // !_EXPLOSION_H_

