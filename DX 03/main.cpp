/*================================================================
		Windowの表示[main.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/05/08

==================================================================*/
/*利用するファイルの指定=============================================
#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG)||defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif
===================================================================*/

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "system_timer.h"
#include "debug_font.h"
#include "spriteAnim.h"
#include "input.h"
#include "Game.h"

/*--------------------------------------------------------------------
		プロトタイプ宣言
---------------------------------------------------------------------*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND Init(HWND, HINSTANCE, int);
static void Uninit(void);
static void Update(void);
static void Draw(void);

static HWND InitApp(HINSTANCE, int);
static bool InitGemetry();

/*--------------------------------------------------------------------
		グローバル変数
---------------------------------------------------------------------*/


//頂点の形を表現する頂点構造体を宣言する

//デバイスに頂点の形を伝えるためのFVFを宣言する



static int g_FrameCount = 0;		//フレームカウンター
static int g_FPSBaseFrameCount = 0;	//FPS計測用フレームカウンター
static double g_FPSBaseTime = 0.0;	//FPS計測用時間
static float g_FPS = 0.0f;			//FPS
static double g_StaticFrameTime = 0.0f;



/*サンプラー
	フィルタリング
	デフォルト：ポイントサンプリング
				リニアサンプリング
				アニソトロピックフィルター(3D)
	UV参照値外の取り扱い
*/

/*--------------------------------------------------------------------
	メイン
----------------------------------------------------------------------*/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg = {};
	HWND hWnd = 0;
	hWnd = Init(hWnd, hInstance, nCmdShow);
	if (!hWnd) return false;


	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			double time = SystemTimer_GetTime();
			if (time - g_StaticFrameTime < 1.0 / 60.0) {

				Sleep(0);
			}
			else {
				g_StaticFrameTime = time;
				//ゲーム処理
				Update();
				Draw();
			}

		}
	}
	return(int)msg.wParam;
}




/*========================================
				Init all.
=========================================*/
HWND Init(HWND hWnd, HINSTANCE hInstance, int nCmdShow) {
	hWnd = InitApp(hInstance, nCmdShow);

	if (!hWnd)return false;
	if (!InitDirect3d(hWnd))return false;
	if (!Keyboard_Initialize(hInstance, hWnd))return false;


	DebugFont_Initialize();
	SystemTimer_Initialize();
	SystemTimer_Start();




	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_FPS = 0.0f;

	InitTexture();
	InitGame();
	TextureLoad();

	return hWnd;
}

/*===================================
		Appllication Init.
====================================*/
HWND InitApp(HINSTANCE hInstance, int nCmdShow) {

	HWND hWnd;

	WNDCLASS wc = {};	//初期化
	wc.lpfnWndProc = WndProc;	//ウィンドウプロシージャコールバック関数の登録
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//矢印の設定
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//色設定

	if (!RegisterClass(&wc)) {
		return false;
	}



	/*ウィンドウ=>ウィンドを構成するパーツ類"テキストボックス","ボタン",など
	システムにこれらパーツのクラス(*このクラスはC++の"クラス"とは無関係)が登録されている
	オリジナルのウィンドウは自分でクラスをシステムに登録する必要がある。*/



	RECT window_rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	DWORD window_style = WINDOW_STYLE;
	AdjustWindowRect(&window_rect, window_style, FALSE);

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	int window_width = max(window_rect.right - window_rect.left, 0);
	int window_height = max(window_rect.bottom - window_rect.top, 0);

	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);

	hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,//ビット演算の順番にも気を付ける
		window_x,	//x
		window_y,	//y
		window_width,	//w
		window_height,	//h
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)return false;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}





/*=====================================
			Uninit all.
======================================*/
void Uninit(void) {
	UninitDirect3d();
	UninitGame();
	DebugFont_Finalize();
}


/*====================================
			Update all.
======================================*/
void Update(void) {

	Keyboard_Update();


	UpdateGame();


	g_FrameCount++;
	double time = SystemTimer_GetTime();
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) {
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));
		g_FPSBaseTime = time;
		g_FPSBaseFrameCount = g_FrameCount;
	}
}



/*============================================
			Draw all.
=============================================*/
void Draw(void) {
	LPDIRECT3DDEVICE9 Device = getDevice();

	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(55, 205, 255, 255), 1.0f, 0);
	//																			カラー				z,ステンシル
	Device->BeginScene();


	DrawGame();

	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}



/*===============================================
			window proc.
================================================*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		Uninit();
		PostQuitMessage(0);
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
