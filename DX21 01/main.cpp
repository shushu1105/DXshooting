#include <windows.h>
#include "debugPrintf.h"
//�����^�C�����C�u���� DLL���Ȃ� ���I�����N����ÓI�����N��
//���I�����N�c�v���O���������s����Ă��烉�C�u�����Ȃǂ������N����(DLL)
//�ÓI�����N�c�v���O�����Ƀ����N������Ԃ̎��s�t�@�C�������

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//int ret1 = MessageBox(NULL, "�����m��", "�搶", MB_OKCANCEL | MB_ICONERROR | MB_DEFBUTTON2);
	//if (ret1 == IDOK) {
	//	MessageBox(NULL, "ok", "�搶", MB_OK | MB_ICONWARNING);
	//}

	//int ret2 = MessageBox(NULL, "�����m��", "�搶", MB_OKCANCEL | MB_ICONERROR | MB_DEFBUTTON2);
	//if (ret2 == IDOK) {
	//	MessageBox(NULL, "ok", "�搶", MB_OK | MB_ICONWARNING);
	//}


	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	DebugPrintf("hInstance�̒l=%p\n", hInstance);
	DebugPrintf("�|�C���^�^�̑傫��=%dByte\n", (int)sizeof(void*));
	DebugPrintf("int�^�̑傫��=%dByte\n", (int)sizeof(int));
	DebugPrintf("long long�^�̑傫��= %dByte\n", (int)sizeof(long long));
	DebugPrintf("__int64�^�̑傫��=%dByte\n", (int)sizeof(__int64));

	return 0;
}