
#include "bullet.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"
#include "enemy.h"

BULLET g_bullet[BULLET_MAX];
const ENEMY *pEnemy = getEnemy();
float angle;
void deleteBullet(int _id);
unsigned int g_bulletTexture;

void InitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		g_bullet[i].isUse = false;
	}
	g_bulletTexture = TextureSetLoadFile("alphabullet.png", 255, 297);
}
void UninitBullet()
{

}
void UpdateBullet()
{

	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {


			//g_bullet[i].angle += D3DXToRadian(1);


			g_bullet[i].position.move(0, -BULLETSPEED);
			g_bullet[i].collision.Update(g_bullet[i].position);


			if (!isInside(g_bullet[i].position.y, 0.0f, SCREEN_HEIGHT))	deleteBullet(i);
		}

	}
}


void DrawBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {
			spriteDivDraw(
				g_bulletTexture,
				{ g_bullet[i].position.x,g_bullet[i].position.y },
				BULLETSIZE,
				BULLETSIZE,
				5, 6,
				g_bullet[i].alpha
			);
		}
	}
}

void createBullet(float x, float y, float size, BULLET_ALPHA _alpha)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!g_bullet[i].isUse) {
			g_bullet[i].position = { x,y };
			g_bullet[i].isUse = true;
			g_bullet[i].angle = 0;
			g_bullet[i].alpha = _alpha;
			g_bullet[i].collision.x = x;
			g_bullet[i].collision.y = y;
			g_bullet[i].collision.radius = size * 0.5f;
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