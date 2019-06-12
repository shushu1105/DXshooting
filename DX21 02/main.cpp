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

/*--------------------------------------------------------------------
		プロトタイプ宣言
---------------------------------------------------------------------*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static HWND Init(HWND, HINSTANCE, int);
static void Uninit(void);
static void Update(void);
static void Draw(void);

static HWND InitApp(HINSTANCE, int);
static bool CleanupDirect3D();
static bool InitGemetry();
static bool RenderDirect3D();
void MoveVertex(float vx, float vy, float ox, float oy, float r, float *Nx, float *Ny);
static int SetCircle(D3DXVECTOR4 _center, D3DCOLOR _color, float _radius);

/*--------------------------------------------------------------------
		グローバル変数
---------------------------------------------------------------------*/


//頂点の形を表現する頂点構造体を宣言する
typedef struct Vertex2d_tag {
	//x,y,z,w		座標変換済み頂点の利用　->　RHWに1.0fを設定
	D3DXVECTOR4 position;	//座標
	D3DCOLOR color;
	D3DXVECTOR2 uv;	//texcord
	//	u = 画像のx座標 / 画像の幅
	//	v = 画像のy画像 / 画像の高さ 
}Vertex2d;
D3DXVECTOR2 move;
//デバイスに頂点の形を伝えるためのFVFを宣言する
#define FVF_VERTEX2D ((D3DFVF_XYZRHW)|(D3DFVF_DIFFUSE)|D3DFVF_TEX1)

float radius = 100.0f;
D3DXVECTOR2 center = { 200.0f,200.0f };
float pcount = (2 * D3DX_PI*radius + 1.0f);
float angle = (2 * D3DX_PI) / pcount;
Vertex2d v[SCREEN_WIDTH];
Vertex2d circle[CIRCLE_COUNTER];

int colorValue = 0;
int a = 0;

LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DTEXTURE9 g_pTexture2 = NULL;
LPDIRECT3DTEXTURE9 g_pTexture3 = NULL;


/*サンプラー
	フィルタリング
	デフォルト：ポイントサンプリング
				リニアサンプリング
				アニソトロピックフィルター(3D)
	UV参照値外の取り扱い
*/


Vertex2d g_VertexDate[] = {
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}

};

Vertex2d g_VertexDate2[] = {
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}

};

Vertex2d g_VertexDate3[] = {
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,0,128),D3DXVECTOR2(1.0f,0.0f)},
	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,128),D3DXVECTOR2(1.0f,1.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(0,255,255,128),D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,128),D3DXVECTOR2(0.0f,1.0f)},
	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}

};



//Vertex2d g_VertexDate3[] = {
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 + 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 - 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 + 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 + 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 - 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 - 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 - 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 + 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
//	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}
//
//};

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
			//ゲーム処理
			Update();
			Draw();
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
	if (!InitGemetry())return false;

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




/*===============================
		DirectX	Init.
================================*/
//bool InitDirect3D(HWND hWnd) {


	//hr = D3DXCreateTextureFromFile(
	//	g_pDevive,
	//	"airou.png",
	//	&g_pTexture
	//);
	//hr = D3DXCreateTextureFromFile(
	//	g_pDevive,
	//	"mark01.png",
	//	&g_pTexture2
	//);
	//hr = D3DXCreateTextureFromFile(
	//	g_pDevive,
	//	"mark02.png",
	//	&g_pTexture3
	//);

	/*
	絶対パス：例　C:/App/MyApp\Asset/Texture/kobeni.png
	相対バス：例　Asset/Texture/kobeni.png
	*/


	//FAILED(hr) hrが失敗だったら真 SUCCEEDED(hr) hrが成功だったら真
	//if (FAILED(hr)) {
	//	MessageBox(hWnd, "Can't create device", "error", MB_OK);

	//	return false;
	//}

	//g_pDevive->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//g_pDevive->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//g_pDevive->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//g_pDevive->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//g_pDevive->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////αブレンドパラメータ
	////今から描くポリゴンのRGB*今から描くポリゴンのα+画面のRGB*(1-今から描くポリゴンのα)
	//g_pDevive->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pDevive->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	/*
テクスチャとポリゴンカラーのブレンドについて
デフォルト　カラー	0：DEFFUSE
					1：TEXTURE	}カラーを乗算
					2：DIFFUSE	}
デフォルト　α		0：DEFFUSE
					1：TEXTURE	}引数1を使用
					2：DIFFUSE	}
*/
	//g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	//g_pDevive->SetTextureStageState(0,	D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//g_pDevive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//g_pDevive->SetTextureStageState(0, D3DTSS_COLOROP, D3DTA_TEXTURE);
	//g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	//g_pDevive->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);


//	return true;

//}

bool InitGemetry() {



	return true;
}


/*=====================================
			Uninit all.
======================================*/
void Uninit(void) {
	UninitDirect3d();
}


/*====================================
			Update all.
======================================*/
void Update(void) {
	for (int i = 0; i < sizeof(g_VertexDate3); i++) {
		g_VertexDate3[i].color = D3DCOLOR_RGBA(255, 255, 255, a);
	}
	a = a++ % 255;
}



/*============================================
			Draw all.
=============================================*/
void Draw(void) {
	RenderDirect3D();
}

bool RenderDirect3D() {

	LPDIRECT3DDEVICE9 pDevice = getDevice();

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(205, 205, 55, 255), 1.0f, 0);
	//																			カラー				z,ステンシル
	pDevice->BeginScene();


	//ポリゴン描画命令
	pDevice->SetFVF(FVF_VERTEX2D);
	//SetCircle(D3DXVECTOR4(300.0f, 300.0f, 0.0f, 1.0f), D3DCOLOR_RGBA((255 - colorValue) % 255, (255 - colorValue + 85) % 255, (255 - colorValue + 170) % 255, 255), 50.0f);

	//pDevice->SetTexture(0, g_pTexture);
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate, sizeof(Vertex2d));


	pDevice->SetTexture(0, g_pTexture);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate, sizeof(Vertex2d));

	pDevice->SetTexture(0, g_pTexture2);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate2, sizeof(Vertex2d));

	pDevice->SetTexture(0, g_pTexture3);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate3, sizeof(Vertex2d));
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate2, sizeof(Vertex2d));
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate3, sizeof(Vertex2d));





	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);

	return true;
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
		if (wParam == VK_RIGHT) {
			for (int i = 0; i < 3; i++) {
				move.x = 10.0f;
			}
		}
		if (wParam == VK_LEFT) {
			for (int i = 0; i < 3; i++) {
				move.x = -10.0f;
			}
		}
		if (wParam == VK_UP) {
			for (int i = 0; i < 3; i++) {
				move.y = -10.0f;
			}
		}
		if (wParam == VK_DOWN) {
			for (int i = 0; i < 3; i++) {
				move.y = 10.0f;
			}
		}
		break;
	case WM_KEYUP:
		move = { 0,0 };
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

