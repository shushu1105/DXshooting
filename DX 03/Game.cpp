
#include "player.h"
#include "spriteAnim.h"

//������ (�e��������)
void InitGame()
{
	InitPlayer();
}

//�I������ (��ԍŏ�)
void UninitGame()
{
	UninitPlayer();
}
//�X�V (�L�[���͂̌� �t���[���v���̑O)
void UpdateGame()
{
	spriteAnimUpdate();
	UpdatePlayer();
}
//�`��iBeginscene �` Endscene�j
void DrawGame()
{
	DrawPlayer();
}