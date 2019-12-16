//=============================================================================
//	�t�@�C�������֌W�̎���֐��Q
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "debug_font.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
static char FileName[] = "HiScore.txt";	// �n�C�X�R�A���i�[����t�@�C����

int HighScore = 0;

//-----------------------------------------------------------------------------
// �֐����@�F�@HighScore_Load()�@
// �@�\�T�v�F�@�n�C�X�R�A��ǂݍ���
//-----------------------------------------------------------------------------
int HighScore_Load(void)
{
	FILE *fp;

	if ((fp = fopen(FileName, "r")) == NULL)
		HighScore = 0;
	else
	{
		fscanf(fp, "%d", &HighScore);
		fclose(fp);
	}

	return (HighScore);

}

//-----------------------------------------------------------------------------
// �֐����@�F�@HighScore_Save()�@
// �@�\�T�v�F�@�n�C�X�R�A��ۑ�����
//-----------------------------------------------------------------------------
void HighScore_Save(int NewScore)
{
	FILE *fp;
	char mes[80];

	if ((fp = fopen(FileName, "w")) == NULL)
	{
		DebugFont_Draw(200, 200, "�t�@�C���I�[�v���Ɏ��s���܂���");
		return;
	}

	fprintf(fp, "%d", NewScore);
	fclose(fp);

}

int GetHighScore()
{
	return HighScore;
}