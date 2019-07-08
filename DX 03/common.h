#ifndef _COMMON_H_
#define _COMMON_H_


/*
�w�b�_�t�@�C���̃��[��
�萔,�񋓌^(enum),�\����(struct),���p��(uninon)...�Ȃǂ̐錾
�֐��̃v���g�^�C�v�錾
#include�̓w�b�_�ɏ����Ȃ� ���K�v�Ȃ��̂�I�m�ɏ���
���̃t�@�C���Ŏg�p������̂�����(cpp���ł����܂���̂�cpp���ŏ����΂���)
*/
/*--------------------------------------------------------------------
		�萔��`
---------------------------------------------------------------------*/

#define CLASS_NAME	"GameWindow"
#define WINDOW_CAPTION	""
#define SCREEN_WIDTH (960)
#define SCREEN_HEIGHT (540)
#define WINDOW_STYLE WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define CIRCLE_COUNTER (600)

#define FPS_MEASUREMENT_TIME (1.0)	//���̕b�����ɍX�V

typedef struct Vertex2d_tag {
	//x,y,z,w		���W�ϊ��ςݒ��_�̗��p�@->�@RHW��1.0f��ݒ�
	D3DXVECTOR4 position;	//���W
	D3DCOLOR color;
	D3DXVECTOR2 uv;	//texcord
	//	u = �摜��x���W / �摜�̕�
	//	v = �摜��y�摜 / �摜�̍��� 
}Vertex2d;
#define FVF_VERTEX2D ((D3DFVF_XYZRHW)|(D3DFVF_DIFFUSE)|D3DFVF_TEX1)



typedef struct FLOAT2 {
public:
	FLOAT2(FLOAT x, FLOAT y);
	FLOAT x, y;
}FLOAT2;

typedef struct FLOAT3 {
public:
	FLOAT3(FLOAT x, FLOAT y, FLOAT z);
	FLOAT x, y, z;
}FLOAT3;

typedef struct FLOAT4 {
public:
	FLOAT4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);
	FLOAT x, y, z, w;
}FLOAT4;


#endif // !_COMMON_H_

