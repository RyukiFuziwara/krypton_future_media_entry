//==============================================
//
//リザルト(result.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include"manager.h"
#include"object2d.h"

//******************//
//リザルトのクラス定義//
//******************//
class CResult : public CScene
{
public: //アクセス可能

	CResult();							//コンストラクタ
	virtual ~CResult();					//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理

	void RankSort(int nScore);

	//静的メンバ関数
	static CResult *Create(void);		//メモリ生成処理

private: //アクセス(メンバ関数内)

	CObject2D *Obj2D;
};

#endif 
