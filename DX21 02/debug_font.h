/*==============================================================================

   デバックフォントモジュール [debug_font.h]
														 Author : Youhei Sato
														 Date   : 2018/8/18
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef DEBUG_FONT_H_
#define DEBUG_FONT_H_


/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

// デバックフォントモジュールの初期化
void DebugFont_Initialize(void);

// デバックフォントモジュールの終了処理
void DebugFont_Finalize(void);

// デバックフォントの描画
//
// 引数:x       ... 描画座標x
//      y       ... 描画座標y
//      pFormat ... printfの引数とほぼ同じ仕様
void DebugFont_Draw(int x, int y, const char* pFormat, ...);


#endif // DEBUG_FONT_H_