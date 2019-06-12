#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_

#include <windows.h>
#include <stdio.h>


	//デバッグ用printf...ViualStudioの出力ウィンドウに出力される
inline void DebugPrintf(const char* pFormat, ...) {
	//Debug時のみのビルド設定
#if defined(_DEBUG)|| defined(DEBUG)
	va_list argp;
	char buf[256];	//バッファは大きめに
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);	//バッファ量と第二因数を合わせる
	va_end(argp);
	MessageBox(NULL, buf, "デバッグ", MB_OK);
	//OutputDebugStringA(buf);
#endif //DEBUG || DEBUG
}




#endif // _DEBUG_PRINTF_H_
