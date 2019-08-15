
#include "bullet.h"
#include "texture.h"
#include "common.h"
#include "sprite.h"
#include "enemy.h"

BULLET g_bullet[BULLET_MAX];
CIRCLE g_collisionBullet;
const ENEMY *pEnemy = getEnemy();
float angle;
int g_bulletTexture;

void InitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		g_bullet[i].isUse = false;
		g_bullet[i].move = { 1.0f,0.0f,0.0f,0.0f };
	}
	g_bulletTexture = TextureSetLoadFile("bullet.png", 512, 256);
}
void UninitBullet()
{

}
void UpdateBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {

			g_bullet[i].angle += D3DXToRadian(1);

			g_collisionBullet.position.x = g_bullet[i].position.x;
			g_collisionBullet.position.y = g_bullet[i].position.y;

			g_bullet[i].move.y = (cos(g_bullet[i].angle * 5) * 10);	//螺旋状の弾


			if (g_bullet[i].direction == LEFT)
			{
				g_bullet[i].position -= g_bullet[i].move;
			}
			if (g_bullet[i].direction == RIGHT)
			{
				g_bullet[i].position += g_bullet[i].move;
			}
			//UP DOWNの時は止まるよ

			g_bullet[i].flameCount++;
			if (g_bullet[i].flameCount >= 3000) {
				g_bullet[i].isUse = false;
				g_bullet[i].flameCount = 0;
			}
		}
	}
}

void DrawBullet()
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (g_bullet[i].isUse) {
			spriteDrawDivAnim(
				g_bulletTexture,
				g_bullet[i].position,
				16, 16,
				D3DCOLOR_RGBA(255, 255, 255, 255),
				16, 8, 16 * 8,
				4,
				0, 13,
				g_bullet[i].flameCount
			);
		}
	}
}

void createBullet(float x, float y, Direction direction)
{
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!g_bullet[i].isUse) {
			g_bullet[i].direction = direction;
			g_bullet[i].position = { x,y,0.0f,1.0f };
			g_bullet[i].isUse = true;
			g_bullet[i].flameCount = 0;
			g_bullet[i].angle = 0;
			g_collisionBullet.position.x = x;
			g_collisionBullet.position.y = y;
			g_collisionBullet.radius = 8;	//bulletsize *0.5f
			break;
		}
	}
}

BULLET *getBullet()
{
	return g_bullet;
}

CIRCLE *getCollisionBullet()
{
	return &g_collisionBullet;
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