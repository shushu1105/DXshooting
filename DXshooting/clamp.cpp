
#include "clamp.h"


//対象の領域設定	width,heightにはオブジェクトの幅を入力
void Clamp(D3DXVECTOR4 position, float width, float height, float _minX, float _maxX, float _minY, float _maxY)
{
	position.x = max(position.x, width*0.5 + _minX);
	position.x = min(position.x, _maxX - width * 0.5);


	position.y = max(position.y, height*0.5 + _minY);
	position.y = min(position.y, _maxY - height * 0.5);

}