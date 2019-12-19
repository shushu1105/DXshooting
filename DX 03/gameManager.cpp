/*************************************************

			gameManager
					ƒQ[ƒ€’†‚Ì“–‚½‚è”»’è—pˆ—

**************************************************/
#include <math.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "star.h"
#include "debug_font.h"
#include "score.h"
#include "scene.h"
#include "sound.h"

PLAYER *pPlayer = getPlayer();
ENEMY *pEnemy = getEnemy();
BULLET *pBullet = getBullet();
STAR *pStar = GetStar();
bool UsedEnemy(int _i);
bool UsedBullet(int _i);
void destroyBullet(int _i);
void destroyEnemy(int _i);



void InitGameManager()
{

}

void UpdateGameManager()
{
	static bool offset_flag;

	for (int i = 0; i < ENEMY_MAX; i++) {
		offset_flag = false;
		if (UsedEnemy(i)) {

			for (int j = 0; j < BULLET_MAX; j++) {
				if (UsedBullet(j)) {

					if ((pBullet + j)->collision.isCollideCir((pEnemy + i)->collision))
					{
						//“–‚½‚Á‚½‚Ìˆ—
						for (int k = 0; k < rand() % 3 + 3; k++)
						{
							CreateStar((pEnemy + i)->position.x, (pEnemy + i)->position.y, rand() % 360, (pBullet + j)->HitCount);
						}
						AddScore(GetAddScoreBullet(j));
						SetPop((pEnemy + i)->position.x, (pEnemy + i)->position.y - (pEnemy + i)->height, GetAddScoreBullet(j));
						destroyBullet(j);
						destroyEnemy(i);
						offset_flag = true;
						PlaySound(SOUND_LABEL_EXPLOSION);
					}
				}
			}

			for (int j = 0; j < STAR_MAX; j++)
			{
				if (UsedStar(j)) {
					if ((pStar + j)->col.isCollideCir((pEnemy + i)->collision))
					{
						for (int k = 0; k < rand() % 3 + 3; k++)
						{
							CreateStar((pEnemy + i)->position.x, (pEnemy + i)->position.y, rand() % 360, (pStar + j)->HitCount);
						}
						AddScore(GetAddScoreStar(j));
						SetPop((pEnemy + i)->position.x, (pEnemy + i)->position.y - (pEnemy + i)->height, GetAddScoreStar(j));

						if (!offset_flag)
						{
							destroyEnemy(i);
							PlaySound(SOUND_LABEL_EXPLOSION);
						}
					}
				}
			}

			if (pPlayer->collision.isCollideCir((pEnemy + i)->collision))
				if (NoneStatus())
					Damage(1);
		}
	}
}

void DrawGameManager()
{
	//DebugFont_Draw(50, 70, "%.2f", pPlayer->position.length(pEnemy->position));
	//for (int i = 0; i < ENEMY_MAX; i++)
	//	DebugFont_Draw(50, 100 + 20 * i, pPlayer->collision.isCollideCir(((pEnemy + i)->collision)) ? "true" : "false");
}


bool UsedEnemy(int _i)
{
	return (pEnemy + _i)->isUse;
}


bool UsedBullet(int _i)
{
	return (pBullet + _i)->isUse;
}

void destroyBullet(int _i)
{
	pBullet[_i].isUse = false;
}