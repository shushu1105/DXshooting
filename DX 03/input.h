/*==============================================================================

   キーボード入力処理 [input.h]
                                                         Author : Youhei Sato
                                                         Date   : 2018/09/05
--------------------------------------------------------------------------------
   キーボードモジュールの初期化内でCOMインターフェースや
   DirectInputデバイスの初期化をしているので、マウス入力やパッド入力を
   追加する場合は、切り離さないといけない
   ※パッド対応はxinputの利用を推奨
==============================================================================*/
#ifndef INPUT_H_
#define INPUT_H_


#include <Windows.h>
// dinput.hをインクルードする前にこれを入れないと警告が出るので注意
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

#define ANY_ALPHA DIK_A|DIK_B|DIK_C|DIK_D|DIK_E|DIK_F|DIK_G|DIK_H|DIK_I|DIK_J|DIK_K|DIK_L|DIK_M|DIK_N|DIK_O|DIK_P|DIK_Q|DIK_R|DIK_S|DIK_T|DIK_U|DIK_V|DIK_W|DIK_X|DIK_Y|DIK_Z
/*------------------------------------------------------------------------------
   関数のプロトタイプ宣言
------------------------------------------------------------------------------*/

// キーボード入力モジュールの初期化
//
// 戻り値：初期化出来なかった場合false
//
// 引数：hinstance ... インスタンスハンドル（WinMainの引数などで取得）
//       hWnd      ... ウィンドウハンドル
//
bool Keyboard_Initialize(HINSTANCE hInstance, HWND hWnd);

// キーボードモジュールの終了処理
void Keyboard_Finalize(void);

// キーボードモジュールの更新
// ※キーボード全体のキー状態の取得
//
void Keyboard_Update(void);

// キーボードのキー状態の取得
//
// Keyboard_Update()で取得したキーの状態を確認する関数群
//
// 戻り値：指定のキーが
//     Press   ... 押されている
//     Trigger ... 押した瞬間
//     Release ... 離した瞬間
// であった場合trueを返す
//
// 引数：nKey ... キー指定（DIK_～というキー列挙）
//
bool Keyboard_IsPress(int nKey);
bool Keyboard_IsTrigger(int nKey);
bool Keyboard_IsRelease(int nKey);

#endif