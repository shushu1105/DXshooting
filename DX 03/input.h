/*==============================================================================

   �L�[�{�[�h���͏��� [input.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/09/05
--------------------------------------------------------------------------------
   �L�[�{�[�h���W���[���̏���������COM�C���^�[�t�F�[�X��
   DirectInput�f�o�C�X�̏����������Ă���̂ŁA�}�E�X���͂�p�b�h���͂�
   �ǉ�����ꍇ�́A�؂藣���Ȃ��Ƃ����Ȃ�
   ���p�b�h�Ή���xinput�̗��p�𐄏�
==============================================================================*/
#ifndef INPUT_H_
#define INPUT_H_


#include <Windows.h>
// dinput.h���C���N���[�h����O�ɂ�������Ȃ��ƌx�����o��̂Œ���
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

#define ANY_ALPHA DIK_A|DIK_B|DIK_C|DIK_D|DIK_E|DIK_F|DIK_G|DIK_H|DIK_I|DIK_J|DIK_K|DIK_L|DIK_M|DIK_N|DIK_O|DIK_P|DIK_Q|DIK_R|DIK_S|DIK_T|DIK_U|DIK_V|DIK_W|DIK_X|DIK_Y|DIK_Z
/*------------------------------------------------------------------------------
   �֐��̃v���g�^�C�v�錾
------------------------------------------------------------------------------*/

// �L�[�{�[�h���̓��W���[���̏�����
//
// �߂�l�F�������o���Ȃ������ꍇfalse
//
// �����Fhinstance ... �C���X�^���X�n���h���iWinMain�̈����ȂǂŎ擾�j
//       hWnd      ... �E�B���h�E�n���h��
//
bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);

// �L�[�{�[�h���W���[���̏I������
void Keyboard_Finalize(void);

// �L�[�{�[�h���W���[���̍X�V
// ���L�[�{�[�h�S�̂̃L�[��Ԃ̎擾
//
void Keyboard_Update(void);

// �L�[�{�[�h�̃L�[��Ԃ̎擾
//
// Keyboard_Update()�Ŏ擾�����L�[�̏�Ԃ��m�F����֐��Q
//
// �߂�l�F�w��̃L�[��
//     Press   ... ������Ă���
//     Trigger ... �������u��
//     Release ... �������u��
// �ł������ꍇtrue��Ԃ�
//
// �����FnKey ... �L�[�w��iDIK_�`�Ƃ����L�[�񋓁j
//
bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);
bool Keyboard_IsRelease(int nKey);

#endif