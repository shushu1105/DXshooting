#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_

#include <windows.h>
#include <stdio.h>


	//�f�o�b�O�pprintf...ViualStudio�̏o�̓E�B���h�E�ɏo�͂����
inline void DebugPrintf(const char* pFormat, ...) {
	//Debug���݂̂̃r���h�ݒ�
#if defined(_DEBUG)|| defined(DEBUG)
	va_list argp;
	char buf[256];	//�o�b�t�@�͑傫�߂�
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);	//�o�b�t�@�ʂƑ����������킹��
	va_end(argp);
	MessageBox(NULL, buf, "�f�o�b�O", MB_OK);
	//OutputDebugStringA(buf);
#endif //DEBUG || DEBUG
}




#endif // _DEBUG_PRINTF_H_
