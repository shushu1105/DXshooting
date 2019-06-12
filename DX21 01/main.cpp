#include <windows.h>
#include "debugPrintf.h"
//ランタイムライブラリ DLLを省く 動的リンクから静的リンクに
//動的リンク…プログラムが実行されてからライブラリなどをリンクする(DLL)
//静的リンク…プログラムにリンクした状態の実行ファイルを作る

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//int ret1 = MessageBox(NULL, "佐藤洋平", "先生", MB_OKCANCEL | MB_ICONERROR | MB_DEFBUTTON2);
	//if (ret1 == IDOK) {
	//	MessageBox(NULL, "ok", "先生", MB_OK | MB_ICONWARNING);
	//}

	//int ret2 = MessageBox(NULL, "佐藤洋平", "先生", MB_OKCANCEL | MB_ICONERROR | MB_DEFBUTTON2);
	//if (ret2 == IDOK) {
	//	MessageBox(NULL, "ok", "先生", MB_OK | MB_ICONWARNING);
	//}


	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	DebugPrintf("hInstanceの値=%p\n", hInstance);
	DebugPrintf("ポインタ型の大きさ=%dByte\n", (int)sizeof(void*));
	DebugPrintf("int型の大きさ=%dByte\n", (int)sizeof(int));
	DebugPrintf("long long型の大きさ= %dByte\n", (int)sizeof(long long));
	DebugPrintf("__int64型の大きさ=%dByte\n", (int)sizeof(__int64));

	return 0;
}