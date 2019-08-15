
#include "player.h"
#include "spriteAnim.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "gameManager.h"

//������ (�e��������)
void InitGame()
{
	InitPlayer();
	InitEnemy();
	InitBullet();
	InitGameManager();
	InitExplosion();
}

//�I������ (��ԍŏ�)
void UninitGame()
{
	UninitBullet();
	UninitEnemy();
	UninitPlayer();
}
//�X�V (�L�[���͂̌� �t���[���v���̑O)
void UpdateGame()
{
	spriteAnimUpdate();
	UpdatePlayer();
	UpdateEnemy();
	UpdateBullet();
	UpdateGameManager();
	UpdateExplosion();
}
//�`��iBeginscene �` Endscene�j
void DrawGame()
{
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
	DrawExplosion();
}