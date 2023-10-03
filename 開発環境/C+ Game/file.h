//==============================================
//
//ファイル関係(file.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _FILE_H_
#define _FILE_H_

#include"main.h"
#include"object.h"
#include"motion.h"

//************************//
//	敵の攻撃クラスの定義　//
//************************//
class CFile
{
public:	//アクセス可能

	CFile();														//コンストラクタ
	~CFile();														//デストラクタ

	//メンバ関数
	void Input(void);												//入力処理
	void Output(void);												//書込処理
	template<class T> static T *ObjectLoad(const char*pFilename);	//オブジェクト読込処理
	static void MotionLoad(const char*pFilename, CMotion *motion);	//モーション読込処理
	static void RankingLoad(const char*pFilename, int nScore[3]);		//ランキング読込処理
	static void RankingSave(const char*pFilename, int nScore[3]);		//ランキング読込処理

private: //アクセス(メンバ関数内)
};

//==============================================
//CSVのオブジェクト読込処理
//==============================================
template<class T> T *CFile::ObjectLoad(const char*pFilename)
{
	int c = 0;			//一文字ずつ確認する変数
	int column = 1;		//列数を数える変数
	int line = 0;		//行数を数える処理
	char aData[1000];	//つなげる文字数
	FILE *pFile;		//ファイルポインタを宣言

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;

	memset(aData, 0, sizeof(aData));

	// ファイルを開く
	pFile = fopen(pFilename, "r");

	T *obj[100];

	if (pFile != NULL)
	{//ファイルが開けた場合

		//ファイルから一文ずつ読み込む
		while (fgetc(pFile) != '\n');

		while (c != EOF)
		{
			//1セル分の文字列を作る
			while (1)
			{
				c = fgetc(pFile);

				//末尾ならループを抜ける
				if (c == EOF)
				{
					break;
				}

				//カンマか改行でなければ、文字としてつなげる
				if (c != ',' && c != '\n')
				{
					strcat(aData, (const char*)&c);
				}
				//カンマか改行ならループを抜ける
				else
				{
					break;
				}
			}

			switch (column)
			{
				//atoi関数で数値として代入
			case 1: pos.x = (float)(atoi(aData));	break;	//X位置
			case 2: pos.y = (float)(atoi(aData));	break;	//Y位置
			case 3: pos.z = (float)(atoi(aData));	break;	//Z位置
			case 4: rot.x = (float)(atoi(aData));	break;	//X角度
			case 5: rot.y = (float)(atoi(aData));	break;	//Y角度
			case 6: rot.z = (float)(atoi(aData));	break;	//Z角度
			case 7:	scale.x = (float)(atoi(aData));	break;	//X幅
			case 8:	scale.y = (float)(atoi(aData));	break;	//Y幅
			case 9: scale.z = (float)(atoi(aData));	break;	//Z幅
			}
			//バッファを初期化
			memset(aData, 0, sizeof(aData));

			//列数を足す
			column++;

			//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
			if (c == '\n')
			{
				obj[line] = T::Create();

				obj[line]->SetPos(pos,scale);				//位置幅設定
				obj[line]->SetRot(rot * 0.001f);			//角度設定

				column = 1;
				line++;
			}
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	return obj[0];
}
#endif