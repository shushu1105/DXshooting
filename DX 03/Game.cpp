
#include "bg.h"
#include "player.h"
#include "spriteAnim.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "gameManager.h"
#include "score.h"

void InitGame()
{
	InitBG();
	InitScore();
	InitPlayer();
	InitEnemy();
	InitBullet();
	InitGameManager();
	InitExplosion();
}

void UninitGame()
{
	UninitBullet();
	UninitEnemy();
	UninitPlayer();
	UninitScore();
	UninitBG();
}

void UpdateGame()
{
	UpdateBG();
	UpdateScore();
	spriteAnimUpdate();
	UpdatePlayer();
	UpdateEnemy();
	UpdateBullet();
	UpdateGameManager();
	UpdateExplosion();
}

void DrawGame()
{
	DrawBG();
	DrawScore();
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawExplosion();
}