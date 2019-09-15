
#include "bg.h"
#include "player.h"
#include "spriteAnim.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "gameManager.h"
#include "score.h"
#include "effect.h"
#include "font.h"

void InitGame()
{
	InitBG();
	InitScore();
	InitPlayer();
	InitEnemy();
	InitBullet();
	InitGameManager();
	InitExplosion();
	InitEffect();
	InitFont();
}

void UninitGame()
{
	UninitEffect();
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
	UpdateEffect();
	UpdateExplosion();
}

void DrawGame()
{
	DrawBG();
	DrawScore();
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawGameManager();
	DrawEffect();
	DrawExplosion();
	DrawFont();
}