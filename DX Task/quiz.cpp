#include "quiz.h"

//�N�C�Y�Ɏg���ϐ��̏�����
int IniQuiz() {

	for (int i = 0; i < Questions; i++) {
		quiz[i] = {0};
		Ans[i] = {0};
	}

	quiz[0] = "�����R���s�������ƂɎc�镲����̂��͉̂��H";
	quiz[1] = "������ �M���ނȂǂɂ���A��C�ċz���s�����߂̓����튯�͉��H";
	quiz[2] = "��Ɏ������Ĉ��ފ�̂��Ƃ����Ƃ������H";

	return 0;
}

//�N�C�Y�̎���e
int MainQuiz() {
	for (int i = 0; i < Questions; i++) {
		Ans[i] = MessageBox(NULL, quiz[i], "", MB_YESNO | MB_ICONQUESTION);
		if (Ans[i] == IDYES) {
			MessageBox(NULL, "����", "", MB_ICONASTERISK);
		}
		else {
			MessageBox(NULL, "���{��̕׋����I�X�X�����܂�", "", MB_ICONERROR);
		}
	}
	return 0;
}

int Quiz() {

	
	IniQuiz();
	MainQuiz();

	return 0;
}