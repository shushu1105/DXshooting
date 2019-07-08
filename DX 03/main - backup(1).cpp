/*================================================================
		Window�̕\��[main.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/05/08

==================================================================*/

#include <Windows.h>

/*--------------------------------------------------------------------
		�萔��`
---------------------------------------------------------------------*/

#define CLASS_NAME	"GameWindow"
#define WINDOW_CAPTION	"�E�B���h�E�\������"

/*--------------------------------------------------------------------
	�v���g�^�C�v�錾
---------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*--------------------------------------------------------------------
	���C��
----------------------------------------------------------------------*/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	/*�E�B���h�E=>�E�B���h���\������p�[�c��"�e�L�X�g�{�b�N�X","�{�^��",�Ȃ�
	�V�X�e���ɂ����p�[�c�̃N���X(*���̃N���X��C++��"�N���X"�Ƃ͖��֌W)���o�^����Ă���
	�I���W�i���̃E�B���h�E�͎����ŃN���X���V�X�e���ɓo�^����K�v������B*/

	WNDCLASS wc = {};	//������
	wc.lpfnWndProc = WndProc;	//�E�B���h�E�v���V�[�W���R�[���o�b�N�֐��̓o�^
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//���̐ݒ�
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);	//�F�ݒ�

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,	//x
		CW_USEDEFAULT,	//y
		CW_USEDEFAULT,	//w
		CW_USEDEFAULT,	//h
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg = {};
	//���b�Z�[�W���[�v =>GetMessage() ���b�Z�[�W���󂯎��܂Ńv���O�������u���b�N����@�� scanf
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F",MB_OKCANCEL | MB_DEFBUTTON2) == IDOK){
		DestroyWindow(hWnd);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}