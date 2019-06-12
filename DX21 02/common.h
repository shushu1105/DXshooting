#ifndef _COMMON_H_
#define _COMMON_H_


/*
ヘッダファイルのルール
定数,列挙型(enum),構造体(struct),共用体(uninon)...などの宣言
関数のプロトタイプ宣言
#includeはヘッダに書かない ※必要なものを的確に書く
他のファイルで使用するものを書く(cpp内でおさまるものはcpp内で書けばいい)
*/
/*--------------------------------------------------------------------
		定数定義
---------------------------------------------------------------------*/

#define CLASS_NAME	"GameWindow"
#define WINDOW_CAPTION	"ウィンドウ表示処理"
#define SCREEN_WIDTH (960)
#define SCREEN_HEIGHT (540)
#define WINDOW_STYLE WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX)
#define CIRCLE_COUNTER (600)


#endif // !_COMMON_H_

