
#include "player.h"
#include "spriteAnim.h"

//初期化 (各初期化後)
void InitGame()
{
	InitPlayer();
}

//終了処理 (一番最初)
void UninitGame()
{
	UninitPlayer();
}
//更新 (キー入力の後 フレーム計測の前)
void UpdateGame()
{
	spriteAnimUpdate();
	UpdatePlayer();
}
//描画（Beginscene ～ Endscene）
void DrawGame()
{
	DrawPlayer();
}