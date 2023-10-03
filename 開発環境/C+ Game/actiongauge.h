//==============================================
//
//体力管理(actiongauge.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _ACTIONGAUGE_H_
#define _ACTIONGAUGE_H_

#include"gauge.h"

//マクロ定義
#define ACTION_COST		(-150)	//アクションの消費コスト
#define MALTICON_COST	(-3)	//同時操作の消費コスト
#define HEAL_VALUE		(1)		//回復コスト
//**********************//
//クラスの定義//
//**********************//
class CActiongauge : public CGauge
{
public:	//アクセス可能

	CActiongauge();					//コンストラクタ
	~CActiongauge();				//デストラクタ

	//メンバ関数
	HRESULT Init(void);				//初期処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理

	//静的メンバ関数
	static CActiongauge *Create(void);		//生成処理

	void Set(int Actiongauge);						//行動ゲージの設定
	void AddSub(int nValue);						//行動ゲージの加減算
	static int GetGauge(void) { return m_nActiongauge; }	//行動ゲージの取得

private: //アクセス(メンバ関数内)

	static int m_nActiongauge;
	static int m_nActiongaugeTemp;
	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;
};

#endif