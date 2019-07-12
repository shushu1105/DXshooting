
#include "player.h"
#include "spriteAnim.h"
#include "bullet.h"
#include "enemy.h"

//初期化 (各初期化後)
void InitGame()
{
	InitPlayer();
	InitEnemy();
	InitBullet();
}

//終了処理 (一番最初)
void UninitGame()
{
	UninitBullet();
	UninitEnemy();
	UninitPlayer();
}
//更新 (キー入力の後 フレーム計測の前)
void UpdateGame()
{
	spriteAnimUpdate();
	UpdatePlayer();
	UpdateEnemy();
	UpdateBullet();
}
//描画（Beginscene ～ Endscene）
void DrawGame()
{
	DrawPlayer();
	DrawEnemy();
	DrawBullet();
}