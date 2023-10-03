//==============================================
//
//エフェクトのビルボード(effect.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _effect_H_
#define _effect_H_

#include"billboard.h"

//**********************************//
//エフェクトのビルボードクラスの定義//
//**********************************//
class CEffect : public CBillboard
{
public:	//アクセス可能

	CEffect();									//コンストラクタ
	virtual~CEffect();							//デストラクタ

													//メンバ関数
	HRESULT Init(void);								//初期処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

	//静的メンバ関数
	static CEffect *Create(void);				//メモリ生成処理

private: //アクセス(メンバ関数内)

	//メンバ変数
	int							m_nLife;		//体力
};

#endif