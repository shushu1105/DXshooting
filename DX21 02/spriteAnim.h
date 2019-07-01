#ifndef _SPRITEANIM_H_
#define _SPRITEANIM_H_

//	アニメーションスプライト初期化
void spriteAnimInit();
//	アニメーションスプライト終了処理
void spriteAnimUninit();
//	アニメーションスプライト更新処理
void spriteAnimUpdate();
//	アニメーションスプライト描画処理
void spriteAnimDraw(float dx,float dy);
//	フレームカウンターのゲッター
int GetFrameCounter();

#endif // !_SPRITEANIM_H_
