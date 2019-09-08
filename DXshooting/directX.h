/*================================================================
		DXshooting[directSound.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef _DIRECTX_H_
#define _DIRECTX_H_

#include "clamp.h"
#include "direct3d.h"
#include "directsound.h"
#include "font.h"
#include "input.h"
#include "player.h"
#include "sprite.h"
#include "texture.h"
#include "wave.h"
#include "soundbuffer.h"

class DirectX
{
public:
	// DirectX関係のメンバ変数
	Direct3D	direct3d;
	DirectXText text;
	Texture texture;
	Sprite sprite;
	Wave wave;
	SoundBuffer sb[32];
	DirectSound	directsound;

	// コンストラクタ
	DirectX();
	// デストラクタ
	~DirectX();

	// 各メンバ変数の初期化
	bool Init(HINSTANCE hInstance,HWND hWnd, int window_w, int window_h, int font_w, int font_h);
	// メインループ
	void MainLoop();
};


#endif // !_DIRECTX_H_



