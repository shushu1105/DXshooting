#include "directX.h"
#include "common.h"
#include "manage.h"

// コンストラクタ
DirectX::DirectX()
{

}
// デストラクタ
DirectX::~DirectX()
{

}

// 各メンバ変数の初期化
bool DirectX::Init(HINSTANCE hInstance, HWND hWnd, int window_w, int window_h, int font_w, int font_h)
{
	//(Init処理)

	// Direct3D作成
	if (!direct3d.Create(hWnd, window_w, window_h))	return false;
	//DirectXtext作成
	if (!text.Create(direct3d.pDevice3D, font_w, font_h))return false;
	// DirectSound作成
	if (!directsound.Create(hWnd))return false;
	//keyboard_Init
	if (!Keyboard_Initialize(hInstance, hWnd))return false;
	////////////////////////////////
	// Texture
	////////////////////////////////
	////////////////////////////////

	////////////////////////////////
	// DirectSound
	////////////////////////////////

	///////////////////////////////////////////////
	//	Wave
	///////////////////////////////////////////////
	//wave[0].Load(_T("katana.wav"));
	//wave[1].Load(_T("bomb.wav"));

	/////////////////////////////////
	//	soundBuffer
	/////////////////////////////////
	//for (int i = 0; i < 2; ++i)	//読み込んだ数のみ(関数)
	//	if (!sb[i].Create(directsound.pDirectSound8, wave[i].WaveFormat, wave[i].WaveData, wave[i].DataSize))return false;

	return true;
}


// メインループ
void DirectX::MainLoop()
{
	Manage *manage = new Manage;


	if (SUCCEEDED(direct3d.pDevice3D->BeginScene()))
	{

		direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, CLEAR_COLOR, 1.0f, 0);

		SetRender(direct3d.pDevice3D, RENDER_ALPHA);
		///////////////////////////////////
		//	main loop
		Keyboard_Update();
		//manage->All();	//引数にdirect3d.pDevice3d

		//if (GetAsyncKeyState('A'))
		//	sb[1].Play(true);
		//if (GetAsyncKeyState('b'))
		//	sb[1].Stop();


		//for (int i = 0; i < 2; ++i) {
		//	sprite[i].Draw(direct3d.pDevice3D, cartex.pTexture);

		text.Draw(D3DCOLOR_RGBA(200, 200, 200, 255), 30, 40, "hello");

		direct3d.pDevice3D->EndScene();
	}
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}
