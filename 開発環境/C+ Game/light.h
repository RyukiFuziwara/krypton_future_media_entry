//==============================================
//
//ライト(Light.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _LIGHT_H_
#define _LIGhT_H_

#include"main.h"

//******************//
//ライトのクラス定義//
//******************//
class CLight
{
public: //アクセス可能

	CLight();							//コンストラクタ
	virtual ~CLight();					//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理

private: //アクセス(メンバ関数内)

	D3DLIGHT9 m_Light;
};
#endif 
