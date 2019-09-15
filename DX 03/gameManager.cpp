
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "debug_font.h"

PLAYER *pPlayer = getPlayer();
ENEMY *pEnemy = getEnemy();
BULLET *pBullet = getBullet();
bool UsedEnemy(int _i);
bool UsedBullet(int _i);
void destroyBullet(int _i);
void destroyEnemy(int _i);


void InitGameManager()
{

}

void UpdateGameManager()
{


	for (int j = 0; j < BULLET_MAX; j++) {
		for (int i = 0; i < ENEMY_MAX; i++) {

			if (UsedEnemy(i) && UsedBullet(j))
			{
				if ((pBullet + j)->collision.isCollide((pEnemy + i)->collision))
				{
					//“–‚½‚Á‚½Žž‚Ìˆ—
					SetExplosion({ (pBullet + j)->position.x, (pBullet + j)->position.y });
					destroyEnemy(i);
					destroyBullet(j);
				}
			}
		}
	}
}

void DrawGameManager()
{
	DebugFont_Draw(50, 50, "%.2f", pPlayer->position.length(pEnemy->position));
	for (int i = 0; i < ENEMY_MAX; i++)
		DebugFont_Draw(50, 100 + 20 * i, pPlayer->collision.isCollide(((pEnemy + i)->collision)) ? "true" : "false");
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

