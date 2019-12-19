/*************************************************

			game

				ÉÅÉCÉìÉQÅ[ÉÄÇÃèàóù

**************************************************/


#include "bg.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "gameManager.h"
#include "score.h"
#include "effect.h"
#include "star.h"
#include "texture.h"
#include "scene.h"
#include "fade.h"
#include "sound.h"

static bool endgame;


void InitGame()
{
	endgame = false;
	Fade_Start(0, D3DCOLOR_RGBA(255, 255, 255, 255), false);


	InitBG();
	InitScore();
	InitPlayer();
	InitEnemy();
	InitBullet();
	InitStar();
	InitGameManager();
	InitEffect();

	PlaySound(SOUND_LABEL_GAME);
	TextureLoad();
}

void UninitGame()
{
	UninitEffect();
	UninitBullet();
	UninitEnemy();
	UninitPlayer();
	UninitScore();
	UninitBG();

	StopSound(SOUND_LABEL_GAME);
	TextureRelease();
}

void UpdateGame()
{
	UpdateBG();
	UpdateScore();
	UpdatePlayer();
	UpdateEnemy();
	UpdateBullet();
	UpdateStar();
	UpdateEffect();
	UpdateGameManager();

	if (!endgame)
	{
		if (isDead() && NoneStatus())
		{
			Fade_Start(60, D3DCOLOR_RGBA(255, 255, 255, 255), true);
			endgame = true;
		}
	}
	else if (endgame)
	{
		if (!Fade_IsFade())
		{
			SceneChange(SCENE_RESULT);
		}
	}

}

void DrawGame()
{
	DrawBG();
	DrawScore();
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawStar();
	DrawEffect();
	DrawGameManager();
}