
#include "object.h"
#include "texture.h"
#include "sprite.h"

int Obj::texture_image[TYPE_NUM] = {};

Obj::Obj()
{
	remove_flag = false;
}

void Obj::setImage(const char* filename)
{
	//テクスチャの読み込み方法に問題あり
	if (texture_image[getType()] == 0)
		texture_image[getType()] = TextureSetLoadFile(filename);

	image = texture_image[getType()];
}

void Obj::setPosition(float posX, float posY)
{
	this->pos.x = posX;
	this->pos.y = posY;
}

void Obj::setHitArea(float width, float height)
{
	this->col.x = this->pos.x;
	this->col.y = this->pos.y;
	this->col.width = width;
	this->col.height = height;
	this->col.radius = width >= height ? height / 2 : width / 2;
}

void Obj::draw()
{
	SetSpriteColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	if (getType() == TYPE_BULLET)
		spriteDivDraw(image, { this->pos.x,this->pos.y }, this->col.width, this->col.height, 7, 4, 10);
	else
		spriteDraw(image, { this->pos.x,this->pos.y }, this->col.width, this->col.height);
}

bool Obj::isHit(ObjRef &objRef)
{
	if (this->col.isCollideCir(objRef->col))
		return true;

	return false;
}