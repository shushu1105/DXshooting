/*********************************************

			score
					�Q�[���p�X�R�A�\��

**********************************************/
#ifndef _SCORE_H_
#define _SCORE_H_

#define TRUSS (10)	//����
#define POP_MAX 32

#include <d3d9.h>
#include <d3dx9.h>

typedef struct
{
	D3DXVECTOR2 position;
	float width;
	float height;
	int num;	//�X�R�A�̐������
}Score;

typedef struct
{
	D3DXVECTOR2 position;
	float width;
	float height;
	int frame;
	int num;	//�X�R�A�̐������
	bool isUse;
}Pop;

void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int _n);
void SetPop(float x, float y, int num);
void DeletePop(int id);

void numberDraw(int _n, D3DXVECTOR2 _position, float width, float height);


int GetScore();


#endif // !_SCORE_H_
