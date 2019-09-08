/*================================================================
		DXshooting[wave.cpp]
										Author	:	Fujino Shuma
										Date	:	2019/08/17

==================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "wave.h"

Wave::Wave()
{
	memset(&WaveFormat, 0, sizeof(WAVEFORMATEX));
	WaveData = NULL;
	DataSize = 0;
}

Wave::~Wave()
{
	if (WaveData != NULL)
		delete[] WaveData;
}

//wavファイル読み込み
bool Wave::Load(const char* FileName)
{
	//バイナリ読み込みモードで開く
	FILE* fp;
	if (!(fp = ::_tfopen(FileName, _T("rb"))))
		return false;

	char chunkId[5] = {};
	char tmp[5] = {};
	unsigned int chunkSize = 0;

	//RIFFチャンク読み込み
	fread(chunkId, sizeof(char) * 4, 1, fp);
	fread(&chunkSize, sizeof(unsigned int), 1, fp);
	fread(tmp, sizeof(char) * 4, 1, fp);
	if (strcmp(chunkId, "RIFF") || strcmp(tmp, "WAVE")) {
		return false;	
	}

	//子チャンク読み込み
	bool fmtchunk = false;
	bool datachunk = false;
	while (true)
	{
		fread(chunkId, sizeof(char) * 4, 1, fp);
		fread(&chunkSize, sizeof(unsigned int), 1, fp);
		if (!strcmp(chunkId, "fmt "))
		{
			if (chunkSize >= sizeof(WAVEFORMATEX))
			{
				fread(&WaveFormat, sizeof(WAVEFORMATEX), 1, fp);
				int diff = chunkSize - sizeof(WAVEFORMATEX);
				fseek(fp, diff, SEEK_CUR);
			}
			else
			{
				memset(&WaveFormat, 0, sizeof(WAVEFORMATEX));
				fread(&WaveFormat, chunkSize, 1, fp);
			}
			fmtchunk = true;
		}
		else if (!strcmp(chunkId, "data"))
		{
			DataSize = chunkSize;
			WaveData = new byte[chunkSize];
			if (fread(WaveData, sizeof(byte), chunkSize, fp) != chunkSize)
			{
				fclose(fp);
				return false;
			}
			datachunk = true;
		}
		else
		{
			fseek(fp, chunkSize, SEEK_CUR);
		}

		if (fmtchunk && datachunk)
			break;

	}

	fclose(fp);
	return true;
}