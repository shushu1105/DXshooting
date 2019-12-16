
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
‡@•¡”‰»
typedef struct Bullet_tag
{
D3DXVECTOR2 position;
Circle collision;
bool isUse;
}Bullet;

ªƒwƒbƒ_[‚É‚Í‘‚©‚È‚¢

‡A”z—ñ‚ðì‚é
static Bullet g_Bullets[BULLET_MAX];
‡B‰Šú‰»
g_Bullet‘S‚Ä–³Œø‚É‚·‚é
‡CXV
‚·‚×‚Ä‚Ìg_Bullet‚É¡‚Ü‚Å‚Ç‚¨‚è‚Ìˆ—‚ð‚·‚é
‡Dì¬
for(‚·‚×‚Ä‚Ìg_Bullet){
if(!g_Bullet[i].used){
	//¡‚Ü‚Å‚Ç‚¨‚è‚Ìˆ—
	break;
	}
}
				« int Bullet_GetMax();
for(int i=0;i<’e‚Ì”;i++){
if(’e‚Ìi”Ô–Ú‚ª—LŒø‚Å“G‚ª—LŒø){
	if(’e‚Ìi”Ô–Ú‚Æ“G‚Æ‚Ì“–‚½‚è”»’è){
		’e‚Ìi”Ô–Ú–³Œø			©	void destroy(int _ids)—LŒø‚©‚Ç‚¤‚©‚Ìˆø”
		“G‚Ì–³Œø
		}
	}
}

*/