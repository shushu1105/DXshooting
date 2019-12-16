#ifndef _STAR_H_
#define _STAR_H_

#include "Fujino.h"

#define STAR_MAX 128

typedef struct
{
	Vector2 pos;
	Collision col;
	float width;
	float height;
	float dir;
	float frame;
	bool isUse;
	long addScore;
	int HitCount;
}STAR;

void InitStar();
void UpdateStar();
void DrawStar();


void CreateStar(float x, float y, float dir, int score);
void DeleteStar(int id);


bool UsedStar(int id);
STAR *GetStar();
int GetAddScoreStar(int id);


#endif // !_STAR_H_

