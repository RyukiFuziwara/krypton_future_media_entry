//==============================================
//
//CSV(csv.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"file.h"
#include"manager.h"
#include"renderer.h"

//マクロ定義
#define CODE_SCRIPT				"SCRIPT"			//スクリプト開始
#define CODE_END_SCRIPT			"END_SCRIPT"		//スクリプト終了

//モーション関係
#define CODE_NUM_MODEL			"NUM_MODEL"			//モデル数
#define CODE_MODEL_FILENAME		"MODEL_FILENAME"	//モデルのファイルパス
#define CODE_CHARACTERSET		"CHARACTERSET"		//キャラクター情報
#define CODE_END_CHARACTERSET	"END_CHARACTERSET"
//パーツ設定
#define CODE_PARTSSET			"PARTSSET"			//パーツ設定開始
#define CODE_END_PARTSSET		"END_PARTSSET"		//パーツ設定終了
//モーション設定
#define CODE_MOTIONSET			"MOTIONSET"			//モーション設定開始
#define CODE_END_MOTIONSET		"END_MOTIONSET"		//モーション設定終了
//キーセット設定
#define CODE_KEYSET				"KEYSET"			//キーセット設定開始
#define CODE_END_KEYSET			"END_KEYSET"		//キーセット設定終了
//キー設定
#define CODE_KEY				"KEY"				//キー設定開始
#define CODE_END_KEY			"END_KEY"			//キー設定終了
//モーション関係
#define CODE_POS				"POS"				//位置
#define CODE_ROT				"ROT"				//向き
#define CODE_RADIUS				"RADIUS"			//半径
#define CODE_JUMP				"JUMP"				//ジャンプ量
#define CODE_NUM_PARTS			"NUM_PARTS"			//パーツ数
#define CODE_INDEX				"INDEX"				//番号
#define CODE_PARENT				"PARENT"			//親モデルの番号
#define CODE_LOOP				"LOOP"				//ループするかの設定
#define CODE_NUM_KEY			"NUM_KEY"			//キー数
#define CODE_FRAME				"FRAME"				//フレーム数

#define fatof(x)				(float)atof(x)

//読み取り状態列挙
typedef enum
{
	//共通
	LOADSTAT_NONE = 0,	//何もしてない
	LOADSTAT_MOTIONSET,
	LOADSTAT_KEYSET,
	LOADSTAT_KEY,
	LOADSTAT_MAX
} LOADSTAT;

//==============================================
//コンストラクタ
//==============================================
CFile::CFile()
{
}
//==============================================
//デスストラクタ
//==============================================
CFile::~CFile()
{

}
//==============================================
//ファイルの初期化処理
//==============================================
void CFile::Input(void)
{

}
//==============================================
//ファイルの終了処理
//==============================================
void CFile::Output(void)
{
}
//==============================================
//TXTのモーション読込処理
//==============================================
void CFile::MotionLoad(const char*pFilename,CMotion *motion)
{
	FILE *pFile;		//ファイルポインタを宣言
	char cData[1000];	//一文字ずつ確認する変数
	bool bLoad = false;
	LOADSTAT LoadStat = LOADSTAT_NONE;
	char *pSprit;
	int nCntMotionInfo = 0;
	int nCntKeyInfo = 0;
	int nCntKey = 0;
	CMotion::INFO Info[10];

	// ファイルを開く
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		while (1)
		{
			//ファイルから文字読み込む
			fgets(&cData[0], 1000, pFile);

			//コメントアウトチェック
			char *pCharPos = strchr(&cData[0], '#');
			if (pCharPos != nullptr)
			{//strchrの返り値がNULLではない
				*pCharPos = '\0';
			}

			//タブ消去
			while (cData[0] == '\t')
			{
				char cDataBackup[1000];
				strcpy(&cDataBackup[0], &cData[0]);
				strcpy(&cData[0], &cDataBackup[1]);
			}

			//文字列チェック
			if (strncmp(&cData[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り開始
				bLoad = true;
			}
			else if (strncmp(&cData[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り終了
				bLoad = false;

				break;
			}
			else if (cData[0] == EOF)
			{//EOFの微レ存

				if (feof(pFile))
				{//EOFと仮定

					bLoad = false;
					break;
				}
			}
			else if (bLoad == true)
			{//読み取り

				switch (LoadStat)
				{
				case LOADSTAT_NONE:	//処理取得

					if (strncmp(&cData[0], CODE_MOTIONSET, sizeof CODE_MOTIONSET / sizeof(char) - 1) == 0)
					{
						if (nCntMotionInfo < MOTIONTYPE_MAX)
						{
							LoadStat = LOADSTAT_MOTIONSET;
						}
					}
					break;
				case LOADSTAT_MOTIONSET:
					if (strncmp(&cData[0], CODE_KEYSET, sizeof CODE_KEYSET / sizeof(char) - 1) == 0)
					{
						LoadStat = LOADSTAT_KEYSET;
					}
					else if (strncmp(&cData[0], CODE_END_MOTIONSET, sizeof CODE_END_MOTIONSET / sizeof(char) - 1) == 0)
					{
						nCntMotionInfo++;
						nCntKeyInfo = 0;
						LoadStat = LOADSTAT_NONE;
					}
					else if (strncmp(&cData[0], CODE_LOOP, sizeof CODE_LOOP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//処理内容の部分消す

						//ループ可否読み取り
						pSprit = strtok(NULL, " =\n");
								
						Info[nCntMotionInfo].m_bLoop = atoi(pSprit) == 1 ? true : false;
					}
					else if (strncmp(&cData[0], CODE_NUM_KEY, sizeof CODE_NUM_KEY / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//処理内容の部分消す

						//キー数読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].nNumKey = atoi(pSprit);
					}
					break;
				case LOADSTAT_KEYSET:
					if (strncmp(&cData[0], CODE_KEY, sizeof CODE_KEY / sizeof(char) - 1) == 0)
					{
						LoadStat = LOADSTAT_KEY;
					}
					else if (strncmp(&cData[0], CODE_END_KEYSET, sizeof CODE_END_KEYSET / sizeof(char) - 1) == 0)
					{
						nCntKeyInfo++;
						nCntKey = 0;
						LoadStat = LOADSTAT_MOTIONSET;
					}
					else if (strncmp(&cData[0], CODE_FRAME, sizeof CODE_FRAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//処理内容の部分消す

						//フレーム数読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].nFrame = atoi(pSprit);
					}
					break;
				case LOADSTAT_KEY:
					if (strncmp(&cData[0], CODE_END_KEY, sizeof CODE_END_KEY / sizeof(char) - 1) == 0)
					{
						nCntKey++;
						LoadStat = LOADSTAT_KEYSET;
					}
					else if (strncmp(&cData[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fPosX = fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fPosY = fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fPosZ = fatof(pSprit);
					}
					else if (strncmp(&cData[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//処理内容の部分消す

															//X向き読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fRotX = fatof(pSprit);

						//Y向き読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fRotY = fatof(pSprit);

						//Z向き読み取り
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fRotZ = fatof(pSprit);
					}
					break;
				}
			}

		}

		for (int nCntInfo = 0; nCntInfo <= nCntMotionInfo; nCntInfo++)
		{
			motion->SetInfo(Info[nCntInfo]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}
//==============================================
//TXTのランキング読込処理
//==============================================
void CFile::RankingLoad(const char*pFilename, int nScore[3])
{
	FILE *pFile;		//ファイルポインタを宣言

	// ファイルを開く
	pFile = fopen(pFilename, "rb");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//ファイルからデータ数を読み込む
		fread(&nScore[0], sizeof(int), 3, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}
//==============================================
//TXTのランキング書込処理
//==============================================
void CFile::RankingSave(const char*pFilename, int nScore[3])
{
	FILE *pFile;		//ファイルポインタを宣言

	// ファイルを開く
	pFile = fopen(pFilename, "wb");

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //ファイルからデータ数を読み込む
		fwrite(&nScore[0], sizeof(int), 3, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}