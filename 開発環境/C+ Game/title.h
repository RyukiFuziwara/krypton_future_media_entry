//==============================================
//
//タイトル(title.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include"manager.h"
#include"object2d.h"

//******************//
//ライトのクラス定義//
//******************//
class CTitle : public CScene
{
public: //アクセス可能

	CTitle();							//コンストラクタ
	~CTitle();					//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理

	//静的メンバ関数
	static CTitle *Create(void);		//メモリ生成処理

private: //アクセス(メンバ関数内)

	CObject2D *Obj2D[3];

	bool m_bCon;
};

#endif 

