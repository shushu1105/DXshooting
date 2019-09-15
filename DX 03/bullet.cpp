
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