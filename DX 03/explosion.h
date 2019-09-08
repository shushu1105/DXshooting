#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include <d3d9.h>
#include <d3dx9.h>

typedef struct 
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	int flameCount;
	bool isUse;
}EXPLOSION;



void InitExplosion();
void UninitExplosion();
void UpdateExplosion();
void DrawExplosion();

void SetExplosion(D3DXVECTOR2 _explosionPosition);



#endif // !_EXPLOSION_H_

