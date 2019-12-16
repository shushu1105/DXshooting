
#include "bullet.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"
#include "enemy.h"
#include "effect.h"

BULLET g_bullet[BULLET_MAX];
const ENEMY *pEnemy = getEnemy();
void deleteBullet(int _id);
unsigned int g_bulletTexture;


void InitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		g_bullet[i].isUse = false;
		g_bullet[i].position.x = 0;
		g_bullet[i].position.y = 0;
		g_bullet[i].width = 32.0f;
		g_bullet[i].height = 32.0f;
		g_bullet[i].HitCount = 0;
		g_bullet[i].addScore = 2;
	}
	g_bulletTexture = TextureSetLoadFile("rom/texture/bulletStar.png");
}
void UninitBullet()
{

}
void UpdateBullet()
{

	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {

			g_bullet[i].position.move(0, -BULLETSPEED);
			createEffect(g_bullet[i].position.x, g_bullet[i].position.y, D3DCOLOR_RGBA(200, 50, 100, 192), 20, g_bullet[i].width);

			g_bullet[i].collision.Update(g_bullet[i].position);


			if (!isInside(g_bullet[i].position.y, 0.0f, SCREEN_HEIGHT))	deleteBullet(i);
		}

	}
}


void DrawBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {
			spriteDraw(g_bulletTexture,
				{ g_bullet[i].position.x, g_bullet[i].position.y },
				g_bullet[i].width,
				g_bullet[i].height,
				D3DCOLOR_RGBA(255, 255, 255, 255)
			);
		}
	}
}

void createBullet(float x, float y)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!g_bullet[i].isUse) {
			g_bullet[i].position = { x,y };
			g_bullet[i].isUse = true;
			g_bullet[i].collision.radius = g_bullet[i].width * 0.5f;
			g_bullet[i].HitCount = 1;
			break;
		}
	}
}

void deleteBullet(int _id)
{
	g_bullet[_id].isUse = false;
}

BULLET *getBullet()
{
	return g_bullet;
}

int GetAddScoreBullet(int id)
{
	return g_bullet[id].addScore;
}


/*
�@複数化
typedef struct Bullet_tag
{
D3DXVECTOR2 position;
Circle collision;
bool isUse;
}Bullet;

↑ヘッダーには書かない

�A配列を作る
static Bullet g_Bullets[BULLET_MAX];
�B初期化
g_Bullet全て無効にする
�C更新
すべてのg_Bulletに今までどおりの処理をする
�D作成
for(すべてのg_Bullet){
if(!g_Bullet[i].used){
	//今までどおりの処理
	break;
	}
}
				↓ int Bullet_GetMax();
for(int i=0;i<弾の数;i++){
if(弾のi番目が有効で敵が有効){
	if(弾のi番目と敵との当たり判定){
		弾のi番目無効			←	void destroy(int _ids)有効かどうかの引数
		敵の無効
		}
	}
}

*/