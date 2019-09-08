/*================================================================
		DXshooting[font.h]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#ifndef _FONT_H_
#define _FONT_H_

#include <vector>
#include "direct3d.h"

class DirectXText
{
private:
	ID3DXFont*			pFont;	// Direct3D�t�H���g
	RECT				Rect;	// �`��̈�
	std::vector<TCHAR>	Buf;	// ������o�b�t�@
public:

	// �R���X�g���N�^
	DirectXText();
	// �f�X�g���N�^
	virtual ~DirectXText();

	// DirectX�t�H���g�쐬
	bool Create(IDirect3DDevice9* pD3DDevice, int font_w, int font_h);

	// ������̕`��
	void Draw(DWORD Color, int x, int y, const TCHAR* Str, ...);
};



#endif // !_FONT_H_
