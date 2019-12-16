#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include "Fujino.h"

enum ObjType
{
	TYPE_NONE,
	TYPE_PLAYER,
	TYPE_BULLET,
	TYPE_ENEMY,
	TYPE_ITEM,
	TYPE_NUM
};

class Obj;
typedef std::shared_ptr<Obj> ObjRef;

//	オブジェクト基本クラス

class Obj
{
	static int texture_image[TYPE_NUM];
	bool remove_flag;
protected:
	int image;

	Vector2 pos;
	Collision col;

	void remove() { remove_flag = true; }

public:
	Obj();
	void setImage(const char*);
	void setPosition(float, float);
	void setHitArea(float, float);
	bool isRemove() { return remove_flag; }
	virtual ObjType getType() = 0;
	virtual ObjType hitType() { return TYPE_NONE; }
	virtual void update() = 0;
	virtual void draw();
	bool isHit(ObjRef&);
	virtual void hit() {};
};

#endif // !_OBJECT_H_
