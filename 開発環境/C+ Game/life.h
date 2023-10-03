//==============================================
//
//体力管理(life.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include"ui.h"

//**********************//
//プレイヤークラスの定義//
//**********************//
class CLife : public CUI
{
public:	//アクセス可能

	CLife();						//コンストラクタ
	~CLife();						//デストラクタ

	//メンバ関数
	HRESULT Init(void);				//初期処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	//静的メンバ関数
	static CLife *Create(void);		//生成処理

	void Set(int life);		//体力の設定
	void Sub(int nValue);	//体力の減算
	int Get(void) { return m_nLife; }	//体力の減算

private: //アクセス(メンバ関数内)

	int m_nLife;
	int m_nLifeTemp;
	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;
};

#endif
