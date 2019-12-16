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

/* game pad��� */
#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)
#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

#define BUTTON_SQUARE BUTTON_A
#define BUTTON_CROSS BUTTON_B
#define BUTTON_CIRCLE BUTTON_C
#define BUTTON_TRIANGLE BUTTON_X
#define BUTTON_L1 BUTTON_Y
#define BUTTON_R1 BUTTON_Z 
#define BUTTON_L2 BUTTON_L 
#define BUTTON_R2 BUTTON_R 


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


//---------------------------- game pad
bool GamePad_Initialize(HINSTANCE hInstance, HWND hWnd);
void GamePad_Finalize(void);
void GamePad_Update(void);

BOOL GamePad_IsPress(int padNo, DWORD button);
BOOL GamePad_IsTrigger(int padNo, DWORD button);

int GetSearchGamePad();


#endif