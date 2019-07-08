/*================================================================
		Window�̕\��[main.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/05/08

==================================================================*/
/*���p����t�@�C���̎w��=============================================
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

/*--------------------------------------------------------------------
		�v���g�^�C�v�錾
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

void reverce(float num, float plus, float minus, float minLimit, float maxLimit, bool upStart);
/*--------------------------------------------------------------------
		�O���[�o���ϐ�
---------------------------------------------------------------------*/


//���_�̌`��\�����钸�_�\���̂�錾����

D3DXVECTOR2 move;
//�f�o�C�X�ɒ��_�̌`��`���邽�߂�FVF��錾����

float radius = 100.0f;
D3DXVECTOR2 center = { 200.0f,200.0f };
float pcount = (2 * D3DX_PI*radius + 1.0f);
Vertex2d v[1024];
Vertex2d circle[CIRCLE_COUNTER];

int colorValue = 0;
int a = 0;

LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DTEXTURE9 g_pTexture2 = NULL;
LPDIRECT3DTEXTURE9 g_pTexture3 = NULL;


static int g_FrameCount = 0;		//�t���[���J�E���^�[
static int g_FPSBaseFrameCount = 0;	//FPS�v���p�t���[���J�E���^�[
static double g_FPSBaseTime = 0.0;	//FPS�v���p����
static float g_FPS = 0.0f;			//FPS
static double g_StaticFrameTime = 0.0f;

static int g_spiceTexture;




typedef struct 
{
	D3DXVECTOR4 position = { 200.0f,200.0f,0.0f,1.0f };
	D3DXVECTOR4 move = { 0.0f,0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 scale = { 1.0f,1.0f,1.0f };
	float angle = 0;
}SPICE;

SPICE g_spice;

/*�T���v���[
	�t�B���^�����O
	�f�t�H���g�F�|�C���g�T���v�����O
				���j�A�T���v�����O
				�A�j�\�g���s�b�N�t�B���^�[(3D)
	UV�Q�ƒl�O�̎�舵��
*/

//
//Vertex2d g_VertexDate[] = {
//	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
//	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
//	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
//	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
//	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}
//
//};
//
//Vertex2d g_VertexDate2[] = {
//	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
//	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
//	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
//	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
//	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}
//
//};
//
//Vertex2d g_VertexDate3[] = {
//	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,0,128),D3DXVECTOR2(1.0f,0.0f)},
//	{D3DXVECTOR4(256.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,128),D3DXVECTOR2(1.0f,1.0f)},
//	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,0.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(0,255,255,128),D3DXVECTOR2(0.0f,0.0f)},
//	{D3DXVECTOR4(0.0f + 150.0f - 0.5f,256.0f - 0.5f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,128),D3DXVECTOR2(0.0f,1.0f)},
//	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}
//
//};



//Vertex2d g_VertexDate3[] = {
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 + 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 - 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f)},
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 + 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 + 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f)},
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 - 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 - 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f)},
//	{D3DXVECTOR4(SCREEN_WIDTH / 2 - 384.0f + SCREEN_WIDTH / 4,SCREEN_HEIGHT / 2 + 384.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f)},
//	//{D3DXVECTOR4(SCREEN_WIDTH - 100.0f,400.0f - (float)(100.0f*sqrt(3)),0.0f,1.0f),D3DCOLOR_RGBA(255,0,255,255)}
//
//};

/*--------------------------------------------------------------------
	���C��
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
				//�Q�[������
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
	Sprite_Init();


	DebugFont_Initialize();
	SystemTimer_Initialize();
	SystemTimer_Start();

	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_FPS = 0.0f;

	if (!InitGemetry())return false;
	InitTexture();
	g_spiceTexture = TextureSetLoadFile("spice_and_wolf.png", 1024, 1024);
	//spriteAnimInit();
	TextureLoad();

	return hWnd;
}

/*===================================
		Appllication Init.
====================================*/
HWND InitApp(HINSTANCE hInstance, int nCmdShow) {

	HWND hWnd;

	WNDCLASS wc = {};	//������
	wc.lpfnWndProc = WndProc;	//�E�B���h�E�v���V�[�W���R�[���o�b�N�֐��̓o�^
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//���̐ݒ�
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//�F�ݒ�

	if (!RegisterClass(&wc)) {
		return false;
	}



	/*�E�B���h�E=>�E�B���h���\������p�[�c��"�e�L�X�g�{�b�N�X","�{�^��",�Ȃ�
	�V�X�e���ɂ����p�[�c�̃N���X(*���̃N���X��C++��"�N���X"�Ƃ͖��֌W)���o�^����Ă���
	�I���W�i���̃E�B���h�E�͎����ŃN���X���V�X�e���ɓo�^����K�v������B*/



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
		window_style,//�r�b�g���Z�̏��Ԃɂ��C��t����
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
	��΃p�X�F��@C:/App/MyApp\Asset/Texture/kobeni.png
	���΃o�X�F��@Asset/Texture/kobeni.png
	*/


	//FAILED(hr) hr�����s��������^ SUCCEEDED(hr) hr��������������^
	//if (FAILED(hr)) {
	//	MessageBox(hWnd, "Can't create device", "error", MB_OK);

	//	return false;
	//}

	//g_pDevive->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//g_pDevive->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//g_pDevive->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	//g_pDevive->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	//g_pDevive->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	////���u�����h�p�����[�^
	////������`���|���S����RGB*������`���|���S���̃�+��ʂ�RGB*(1-������`���|���S���̃�)
	//g_pDevive->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pDevive->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	/*
�e�N�X�`���ƃ|���S���J���[�̃u�����h�ɂ���
�f�t�H���g�@�J���[	0�FDEFFUSE
					1�FTEXTURE	}�J���[����Z
					2�FDIFFUSE	}
�f�t�H���g�@��		0�FDEFFUSE
					1�FTEXTURE	}����1���g�p
					2�FDIFFUSE	}
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
	DebugFont_Finalize();
	Sprite_Uninit();
}


/*====================================
			Update all.
======================================*/
void Update(void) {

	Keyboard_Update();
	//for (int i = 0; i < sizeof(g_VertexDate3); i++) {
	//	g_VertexDate3[i].color = D3DCOLOR_RGBA(255, 255, 255, a);
	//}
	//a = a++ % 255;

	//spriteAnimUpdate();


	if (Keyboard_IsPress(DIK_UP)) {
		g_spice.scale.x += 0.01f;
		g_spice.scale.y += 0.01f;
	}
	if (Keyboard_IsPress(DIK_DOWN)) {
		g_spice.scale.x -= 0.01f;
		g_spice.scale.y -= 0.01f;
	}
	if (Keyboard_IsPress(DIK_LEFT)) {
		g_spice.angle -= 60;
	}
	if (Keyboard_IsPress(DIK_RIGHT)) {
		g_spice.angle += 60;
	}
	if (Keyboard_IsPress(DIK_W)) {
		g_spice.position.y -= 5.0f;
	}
	if (Keyboard_IsPress(DIK_S)) {
		g_spice.position.y += 5.0f;

	}
	if (Keyboard_IsPress(DIK_A)) {
		g_spice.position.x -= 5.0f;

	}
	if (Keyboard_IsPress(DIK_D)) {
		g_spice.position.x += 5.0f;
	}



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
	RenderDirect3D();
}

bool RenderDirect3D() {

	LPDIRECT3DDEVICE9 Device = getDevice();

	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(205, 205, 55, 255), 1.0f, 0);
	//																			�J���[				z,�X�e���V��
	Device->BeginScene();

	//spriteDraw(0, { SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f,0.0f,1.0f }, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 256, 512, 256, { 0.0f,0.0f }, angle);
	//spriteDraw(g_spiceTexture, { SCREEN_WIDTH*0.5f, SCREEN_HEIGHT*0.5f,0.0f,1.0f }, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 256, 512, 256, scale.x, scale.y, scale.z);
	
	spriteDrawRS(g_spiceTexture, g_spice.position, D3DCOLOR_RGBA(255, 255, 255, 255), 0, 256, 512, 256, g_spice.scale.x, g_spice.scale.y, g_spice.scale.z, { g_spice.position.x,g_spice.position.y }, D3DXToRadian(g_spice.angle));
	Sprite_Draw(g_spiceTexture, 0.0f, 0.0f);
	DebugFont_Draw(32, 32, "%.2f", g_FPS);
	//spriteAnimDraw();

	//�|���S���`�施��
	//SetCircle(D3DXVECTOR4(300.0f, 300.0f, 0.0f, 1.0f), D3DCOLOR_RGBA((255 - colorValue) % 255, (255 - colorValue + 85) % 255, (255 - colorValue + 170) % 255, 255), 50.0f);

	//Device->SetTexture(0, g_pTexture);
	//Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate, sizeof(Vertex2d));

	//Device->SetTexture(0, g_pTexture2);
	//Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate2, sizeof(Vertex2d));

	//Device->SetTexture(0, g_pTexture3);
	//Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate3, sizeof(Vertex2d));
	//Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate2, sizeof(Vertex2d));
	//Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g_VertexDate3, sizeof(Vertex2d));


	//Device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2d));
	//D3DFMT_INDEX16 = �C���f�b�N�X�f�[�^�̃r�b�g16	WORD
	//D3DFMT_INDEX32 = �C���f�b�N�X�f�[�^�̃r�b�g32	DWORD


	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);

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
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
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
