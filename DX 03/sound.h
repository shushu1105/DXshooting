//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// BGM TITLE
	SOUND_LABEL_GAME,			//BGM GAME
	SOUND_LABEL_RESULT_SE,		//SE
	SOUND_LABEL_EXPLOSION,	// 爆発音
	SOUND_LABEL_DAMAGE,	// ダメージ
	SOUND_LABEL_SHOT,	// ダメージ
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
