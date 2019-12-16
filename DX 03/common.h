#ifndef _COMMON_H_
#define _COMMON_H_

#include <d3d9.h>
#include <d3dx9.h>
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
#define SCREEN_WIDTH (1080.0f)
#define SCREEN_HEIGHT (640.0f)
#define WINDOW_STYLE WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)


typedef struct Vertex2d_tag {
	//x,y,z,w		���W�ϊ��ςݒ��_�̗��p�@->�@RHW��1.0f��ݒ�
	D3DXVECTOR4 position;	//���W
	D3DCOLOR color;
	D3DXVECTOR2 uv;	//texcord
	//	u = �摜��x���W / �摜�̕�
	//	v = �摜��y�摜 / �摜�̍��� 
}Vertex2d;
#define FVF_VERTEX2D ((D3DFVF_XYZRHW)|(D3DFVF_DIFFUSE)|D3DFVF_TEX1)
//���_�̌`��\�����钸�_�\���̂�錾����

//�f�o�C�X�ɒ��_�̌`��`���邽�߂�FVF��錾����




#endif // !_COMMON_H_

