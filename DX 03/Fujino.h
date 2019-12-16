/*
*	@file	"Fujino.h"
*
*	@autor:	���� �C�D
*
*	@date	2019/09/05	����J�n
*/


#ifndef _FUJINO_H_
#define _FUJINO_H_


//#include <minwindef.h>
#include <Windows.h>
#include <assert.h>
#include <stdio.h>

#define SecondsToFrame( seconds ) ((seconds) * (60))
#define MinutesToFrame( minites ) ((minites) * (3600))

typedef struct {
public:
	float x;
	float y;
}Float2;

typedef struct {
public:
	float x;
	float y;
	float z;
}Float3;

typedef struct {
public:
	float x;
	float y;
	float z;
	float w;
}Float4;



//	�f�[�^�̗̈搧��(�Q�ƌ^)
//
//	����:n		�����������f�[�^
//		:low	����
//		:high	���
template <typename T>
static void clamp(T &n, T low, T high)
{
	assert(low <= high);
	n = min(max(n, low), high);
}


//	�I�u�W�F�N�g�̗̈搧��(�Q�ƌ^)
//
//	����:n		�����������f�[�^
//		:width	�I�u�W�F�N�g�̕�
//		:low	����
//		:high	���
template <typename T>
static void clamp(T &n, T width, T low, T high)
{
	assert(low <= high);
	n = min(max(n, width / 2 + low), high - width / 2);
}

//	�^�[���A���E���h�֐�(�Q�ƌ^)
//
//	����:x		�J��Ԃ������f�[�^
//		:low	����
//		:high	���
template <typename T>
static void wrap(T &x, T low, T high)
{
	assert(low < high);
	const float n = fmod(x - low, high - low);
	x = ((n >= 0) ? (n + low) : (n + high));
}


//	�����`�F�b�N�֐�
//
//	����:n	�`�F�b�N�������f�[�^
//
//	�߂�l:int ����n�̌���
static int digitCount(int n)
{
	int digit = 1;
	while (((n /= 10) != 0))
	{
		digit++;
	}
		return digit;
}

//	�f�[�^�̗̈������(�Q�ƌ^)
//
//	����:x		���肵�����f�[�^
//		:low	����
//		:high	���
//
//	�߂�l:bool	�̈�����ǂ���
template <typename T>
static bool isInside(T &x, T low, T high)
{
	assert(low < high);
	return (low < x) && (x < high) ? true : false;
}

//	���o�E���h�֐�
//	
//	����:x			�Ώۂ̈ʒu
//		:width		�Ώۂ̕�
//		:vel		�Ώۂ̉����x(�Q�ƌ^)
//		:minLine	���o�E���h���������̈�̍ŏ��l
//		:minLine	���o�E���h���������̈�̍ő�l
//		:inside		�̈���Ńo�E���h���������Ȃ�true	�̈�O�Ńo�E���h���������Ȃ�false
template<typename T>
static void rebound(T x, T width, T &vel, T value, T minLine, T maxLine, bool inside)
{
	assert(minLine < maxLine);

	if (inside)
	{
		if (x + width + vel > minLine)
			if (x - width + vel < maxLine)
				vel *= -value;
	}
	else
	{
		if (x - width + vel < minLine)
			vel *= -value;
		else if (x + width + vel > maxLine)
			vel *= -value;
	}
}
//	���o�E���h�֐�
//
//	����:

//enum
//{
//	Pass = 0,
//	CollisionX,
//	CollisionY,
//};
//static int rebound(Float2 objectPos, Float2 objectVel, Float2 Reference, float wOffset, float hOffset)
//{
//	Float2 returnVal = { objectVel.x,objectVel.y };
//
//	if (objectPos.y > Reference.y - hOffset &&
//		objectPos.y < Reference.y + hOffset)
//	{
//		if (objectPos.x > Reference.x - wOffset &&
//			objectPos.x < Reference.x + wOffset)
//		{
//			returnVal.y = returnVal.y*-1;
//			if (objectPos.y + returnVal.y<Reference.y + hOffset &&
//				objectPos.y + returnVal.y>Reference.y - hOffset)
//				return CollisionX;
//		}
//		return CollisionY;
//	}
//	return Pass;
//}

class Vector2
{
public:
	float x;
	float y;

	//	���W�̈ʒu�ړ�
	//
	//	����:_x	x�̈ړ���
	//		:_y	y�̈ړ���
	void move(float _x, float _y)
	{
		this->x += _x;
		this->y += _y;
	}

	//	���W���m�̋��������߂�֐�
	//	
	//	����:other	Vector2�N���X�̑Ώە�
	//
	//	�߂�l:float	�Ώە��Ƃ̋���
	float length(const Vector2 &other) const
	{
		return (float)(sqrt(pow((this->x - other.x), 2) + pow((this->y - other.y), 2)));
	}

protected:
	//	���W���m�̋��������߂�֐�
	//
	//	����:other	Vector2�N���X�̑Ώە�
	//
	//	�߂�l:float	�Ώە��Ƃ̋����̓��
	float lengthSq(const Vector2 &other)const
	{
		return (float)(pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
	}

};

//	Circle�N���X
//
//	collision�̃N���X�Ŏg��
//
//	��09/09���݃A�b�v�f�[�g��
class Collision :public Vector2
{
public:
	float radius;

	//	�I�u�W�F�N�g���m�̓����蔻��t���O(�~)
	//
	//	����:other	Collision�N���X�̑Ώە�
	//
	//	�߂�l:bool	�Ώە��Ɠ������Ă��邩�ǂ���
	bool isCollideCir(const Collision &other)const
	{
		return lengthSq(other) < pow((this->radius + other.radius), 2);
	}
	//	�����蔻��̍X�V
	//
	//	����:other	Vector2�^�̑Ώە�
	void Update(const Vector2 &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
};


//�摜����T�C�Y���擾�i�r���j
typedef struct Size_t
{

	int w;
	int h;
}Size;

static int cenvertByteOrder(int x)
{
	return
		((x & 0xFF000000) >> 24) |
		((x & 0x00FF0000) >> 8) |
		((x & 0x0000FF00) << 8) |
		((x & 0x000000FF) << 24);
}

static bool GetImageSize(const char* filename, Size *size)
{
	FILE *fp;
	if ((fopen_s(&fp, filename, "rb")))
		return false;

	fseek(fp, 16L, SEEK_SET);
	fread(&size->w, sizeof(int), 1, fp);
	fread(&size->h, sizeof(int), 1, fp);
	fclose(fp);
	size->w = cenvertByteOrder(size->w);
	size->h = cenvertByteOrder(size->h);

	return true;
}



#endif // !_FUJINO_H_
