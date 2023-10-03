//==============================================
//
//体力管理(gauge.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include"ui.h"

//**********************//
//クラスの定義//
//**********************//
class CGauge : public CUI
{
public:	//アクセス可能

	CGauge();						//コンストラクタ
	virtual ~CGauge();				//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);		//初期処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理
	virtual void Draw(void);		//描画処理

	void Set(int Actiongauge);		//行動ゲージの設定
	void AddSub(int nValue);		//行動ゲージの加減算
	
private: //アクセス(メンバ関数内)

	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;
};

#endif
