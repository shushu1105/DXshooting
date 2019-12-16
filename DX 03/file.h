#ifndef _FILE_H_
#define _FILE_H_


//-----------------------------------------------------------------------------
// File.cppの関数のうち、他のソースで利用される関数のプロトタイプ宣言
//-----------------------------------------------------------------------------

int HighScore_Load(void);
void HighScore_Save(int);

int GetHighScore();

#endif // !_FILE_H_
