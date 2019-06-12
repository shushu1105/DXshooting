#include "quiz.h"

//クイズに使う変数の初期化
int IniQuiz() {

	for (int i = 0; i < Questions; i++) {
		quiz[i] = {0};
		Ans[i] = {0};
	}

	quiz[0] = "物が燃え尽きたあとに残る粉末状のものは何？";
	quiz[1] = "両生類 哺乳類などにある、空気呼吸を行うための内臓器官は何？";
	quiz[2] = "主に酒を入れて飲む器のことを何というか？";

	return 0;
}

//クイズの主内容
int MainQuiz() {
	for (int i = 0; i < Questions; i++) {
		Ans[i] = MessageBox(NULL, quiz[i], "", MB_YESNO | MB_ICONQUESTION);
		if (Ans[i] == IDYES) {
			MessageBox(NULL, "正解", "", MB_ICONASTERISK);
		}
		else {
			MessageBox(NULL, "日本語の勉強をオススメします", "", MB_ICONERROR);
		}
	}
	return 0;
}

int Quiz() {

	
	IniQuiz();
	MainQuiz();

	return 0;
}