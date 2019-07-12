
#include "player.h"
#include "spriteAnim.h"
#include "bullet.h"
#include "enemy.h"

//������ (�e��������)
void InitGame()
{
	InitPlayer();
	InitEnemy();
	InitBullet();
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
}
//�`��iBeginscene �` Endscene�j
void DrawGame()
{
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
}