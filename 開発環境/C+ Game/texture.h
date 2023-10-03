//==============================================
//
//テクスチャ管理(texture.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include"main.h"

#define MAX_TEXTURE (21)

//**********************//
//テクスチャのクラス定義//
//**********************//
class CTexture
{
public: //アクセス可能

	CTexture();											//コンストラクタ
	virtual ~CTexture();								//デストラクタ

	typedef enum 
	{
		TEXTURE_TITLE = 0,
		TEXTURE_RESULT,
		TEXTURE_ENTER,
		TEXTURE_RANKING,
		TEXTURE_YOURSCORE,
		TEXTURE_FIRST,
		TEXTURE_SECOND,
		TEXTURE_THIRD,
		TEXTURE_NUMBER,
		TEXTURE_FLAME,
		TEXTURE_EFFECT,
		TEXTURE_PLAYER,
		TEXTURE_ENEMY,
		TEXTURE_BLOCK,
		TEXTURE_BULLET,
		TEXTURE_EXPLOSION,
		TEXTURE_CONTROL,
		TEXTURE_MAX,

	}TEXTURE;

	HRESULT Load(void);									//初期化処理
	void Unload(void);									//終了処理
	int Regist(const char *pFilename);					//
	LPDIRECT3DTEXTURE9 GetAddress(int ndlx);			//テクスチャ取得

private: //アクセス(メンバ関数内)

	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];		//テクスチャへのポインタ
	static int m_nNumAll;								//テクスチャの総数
	char *m_nTexname[MAX_TEXTURE];
};
#endif 