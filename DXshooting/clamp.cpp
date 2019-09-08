
#include "clamp.h"


//�Ώۂ̗̈�ݒ�	width,height�ɂ̓I�u�W�F�N�g�̕������
void Clamp(D3DXVECTOR4 position, float width, float height, float _minX, float _maxX, float _minY, float _maxY)
{
	position.x = max(position.x, width*0.5 + _minX);
	position.x = min(position.x, _maxX - width * 0.5);


	position.y = max(position.y, height*0.5 + _minY);
	position.y = min(position.y, _maxY - height * 0.5);

}