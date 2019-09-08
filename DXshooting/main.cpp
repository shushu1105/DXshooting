/*================================================================
		DXshooting[main.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#include <windows.h>
#include <tchar.h>
#include "directX.h"
#include "common.h"



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してもよろしいですか?", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		//Uninit();	//開放終了処理
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		WndProc,
		0,
		0,
		hInstance,
		(HICON)LoadImage(NULL,MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED),
		(HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL,
		WC_BASIC ,
		NULL };

	if (!RegisterClassEx(&wcex))
		return false;


	HWND hWnd = CreateWindowEx(
		0,
		WC_BASIC,
		WINDOW_CAPTION,
		WINDOW_STYLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	///////////////////////////////////////////////////////////////////////////////////////////////

	DirectX directX;
	if (!directX.Init(hInstance, hWnd, WINDOW_WIDTH, WINDOW_HEIGHT, FONT_W, FONT_H)) return 0;
	///////////////////////////////////////////////////////////////////////////////////////////////

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
		else {

			///////////////////////////////////////////////////////////////////////////////////////////////


			directX.MainLoop();


			///////////////////////////////////////////////////////////////////////////////////////////////
		}
	}


	return 0;
}