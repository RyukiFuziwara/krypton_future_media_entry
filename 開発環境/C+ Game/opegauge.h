//==============================================
//
//管理(opegauge.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _OPEGAUGE_H_
#define _OPEGAUGE_H_

#include"gauge.h"
#include"life.h"

//マクロ定義

//**********************//
//クラスの定義//
//**********************//
class COpegauge : public CGauge
{
public:	//アクセス可能

	COpegauge();					//コンストラクタ
	~COpegauge();					//デストラクタ

	//メンバ関数
	HRESULT Init(void);				//初期処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	//静的メンバ関数
	static COpegauge *Create(void);		//生成処理

	void Set(int Opegauge);								//操作ゲージの設定
	void AddSub(int nValue);							//操作ゲージの加減算
	int GetLife(void) { return m_nLife; }				//体力の取得
	static int GetGauge(void) { return m_nOpegauge; }	//操作ゲージの取得

private: //アクセス(メンバ関数内)

	static int m_nOpegauge;
	static int m_nOpegaugeTemp;

	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;

	int m_nLife;
};

#endif
