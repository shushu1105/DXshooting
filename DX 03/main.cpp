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
#include "frameCounter.h"
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "system_timer.h"
#include "debug_font.h"
#include "spriteAnim.h"
#include "input.h"
#include "Game.h"
#include "sound.h"
#include "fade.h"

/*--------------------------------------------------------------------
		�v���g�^�C�v�錾
---------------------------------------------------------------------*/


static HWND Init(HWND, HINSTANCE, int);
static HWND InitApp(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*--------------------------------------------------------------------
		�O���[�o���ϐ�
---------------------------------------------------------------------*/




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


	InitFrame();

	//InitSound(hWnd);
	InitTexture();
	InitFade();


	InitGame();

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



	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
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


/*=====================================
			Uninit all.
======================================*/
void Uninit(void) {

	TextureRelease();

	//UninitSound();
	UninitDirect3d();
	UninitGame();
	DebugFont_Finalize();
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




/*====================================
			Update all.
======================================*/
void Update(void) {

	Keyboard_Update();
	UpdateFade();

	UpdateGame();

	UpdateFrame();
}



/*============================================
			Draw all.
=============================================*/
void Draw(void) {
	LPDIRECT3DDEVICE9 Device = getDevice();

	Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(55, 205, 255, 255), 1.0f, 0);
	//																			�J���[				z,�X�e���V��
	Device->BeginScene();


	DrawGame();
	DrawFade();

	DrawFrame();	//FPS�f�o�b�O�p
	Device->EndScene();
	Device->Present(NULL, NULL, NULL, NULL);
}


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
			if (time - StaticFrameTime() < 1.0 / 60.0) {

				Sleep(0);
			}
			else {
				StaticFrameTime(time);
				//�Q�[������
				Update();
				Draw();
			}

		}
	}
	return(int)msg.wParam;
}




