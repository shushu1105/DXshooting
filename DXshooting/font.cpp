#define _CRT_SECURE_NO_WARNINGS
#include "font.h"
#include <tchar.h>
// �R���X�g���N�^
DirectXText::DirectXText()
{
	pFont = NULL;
}
// �f�X�g���N�^
DirectXText::~DirectXText()
{
	if (pFont != NULL)
		pFont->Release();
}

// DirectX�t�H���g�쐬
bool DirectXText::Create(IDirect3DDevice9* pD3DDevice, int font_w,int font_h)
{
	HFONT	hFont = NULL;	// �t�H���g�n���h��
	LOGFONT	LogFont = {};	// �t�H���g�\����

	// �f�t�H���g�t�H���g�擾
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	// �f�t�H���g�t�H���g���擾
	GetObject(hFont, sizeof(LOGFONT), &LogFont);
	// DirectX�t�H���g�쐬
	if (FAILED(D3DXCreateFont(pD3DDevice,
		font_h,					// ��������
		font_w,						// ������
		LogFont.lfWeight,			// �t�H���g�̑���
		0,							// �~�b�v�}�b�v���x��
		LogFont.lfItalic,			// �C�^���b�N�t���O
		LogFont.lfCharSet,			// �����Z�b�g
		LogFont.lfOutPrecision,		// ���ۂ̃t�H���g�ƖړI�̃t�H���g�̓����̈�v���@
		LogFont.lfQuality,			// �N�H���e�B
		LogFont.lfPitchAndFamily,	// �s�b�`�ƃt�@�~���C���f�b�N�X
		LogFont.lfFaceName,			// �t�H���g��
		&pFont)))
	{
		return false;
	}

	return true;
}

// ������̕`��
void DirectXText::Draw(DWORD Color, int x, int y, const TCHAR* Str, ...)
{
	va_list args;
	va_start(args, Str);					// �ψ����̍ŏ��̗v�f���i�[����
	int len = _vsctprintf(Str, args) + 1;	// �������J�E���g�A�k��������������
	if (Buf.size() < (UINT)len)
		Buf.resize(len);						// �����T�C�Y�����I�Ƀ������m��
	_vstprintf(&Buf[0], Str, args);			// �����𐮌`����

	SetRect(&Rect, 0, 0, 0, 0);
	// �`��̈�T�C�Y�擾
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT | DT_CALCRECT, Color);
	// �{�`��
	Rect.left += x;
	Rect.right += x;
	Rect.top += y;
	Rect.bottom += y;
	pFont->DrawText(NULL, &Buf[0], -1, &Rect, DT_LEFT, Color);
}