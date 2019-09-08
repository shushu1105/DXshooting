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
	ID3DXFont*			pFont;	// Direct3Dフォント
	RECT				Rect;	// 描画領域
	std::vector<TCHAR>	Buf;	// 文字列バッファ
public:

	// コンストラクタ
	DirectXText();
	// デストラクタ
	virtual ~DirectXText();

	// DirectXフォント作成
	bool Create(IDirect3DDevice9* pD3DDevice, int font_w, int font_h);

	// 文字列の描画
	void Draw(DWORD Color, int x, int y, const TCHAR* Str, ...);
};



#endif // !_FONT_H_
