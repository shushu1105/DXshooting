
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
�@������
typedef struct Bullet_tag
{
D3DXVECTOR2 position;
Circle collision;
bool isUse;
}Bullet;

���w�b�_�[�ɂ͏����Ȃ�

�A�z������
static Bullet g_Bullets[BULLET_MAX];
�B������
g_Bullet�S�Ė����ɂ���
�C�X�V
���ׂĂ�g_Bullet�ɍ��܂łǂ���̏���������
�D�쐬
for(���ׂĂ�g_Bullet){
if(!g_Bullet[i].used){
	//���܂łǂ���̏���
	break;
	}
}
				�� int Bullet_GetMax();
for(int i=0;i<�e�̐�;i++){
if(�e��i�Ԗڂ��L���œG���L��){
	if(�e��i�ԖڂƓG�Ƃ̓����蔻��){
		�e��i�Ԗږ���			��	void destroy(int _ids)�L�����ǂ����̈���
		�G�̖���
		}
	}
}

*/