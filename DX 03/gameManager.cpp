
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"

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

void destroyEnemy(int _i)
{
	pEnemy[_i].isUse = false;
}