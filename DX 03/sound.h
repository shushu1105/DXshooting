//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <Windows.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// BGM TITLE
	SOUND_LABEL_GAME,			//BGM GAME
	SOUND_LABEL_RESULT_SE,		//SE
	SOUND_LABEL_EXPLOSION,	// ������
	SOUND_LABEL_DAMAGE,	// �_���[�W
	SOUND_LABEL_SHOT,	// �_���[�W
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
