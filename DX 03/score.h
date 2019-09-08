#ifndef _SCORE_H_
#define _SCORE_H_

#define TRUSS (5)	//Œ…”

#include <d3d9.h>
#include <d3dx9.h>

typedef struct
{
	D3DXVECTOR2 position;
	float width;
	float height;
	unsigned int texture;
	int num;	//ƒXƒRƒA‚Ì”šî•ñ
}Score;

void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int _n);

#endif // !_SCORE_H_
