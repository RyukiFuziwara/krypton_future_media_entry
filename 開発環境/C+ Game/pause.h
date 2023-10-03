//==============================================
//
//ポーズ(pause.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"manager.h"
#include"object2d.h"

//******************//
//ライトのクラス定義//
//******************//
class CPause : public CScene
{
public: //アクセス可能

	CPause();							//コンストラクタ
	~CPause();							//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理

	//静的メンバ関数
	static CPause *Create(void);		//メモリ生成処理

	static bool GetPause(void) { return m_bPause; }

private: //アクセス(メンバ関数内)

	static bool	  m_bPause;
};

#endif 
