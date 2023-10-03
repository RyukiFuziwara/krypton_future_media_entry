//==============================================
//
//数字関係(ui.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _UI_H_
#define _UI_H_

#include"object2D.h"

//********************//
//数字関係クラスの定義//
//********************//
class CUI : public CObject2D
{
public:	//アクセス可能

	CUI();									//コンストラクタ
	virtual~CUI();							//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);							//初期処理
	virtual void Uninit(void);							//終了処理
	virtual void Update(void);							//更新処理
	virtual void Draw(void);							//描画処理

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//位置取得処理

	//静的メンバ関数
	static CUI *Create(void);						//メモリ生成処理

private: //アクセス(メンバ関数内)

	//メンバ変数
	LPDIRECT3DTEXTURE9		m_pTexture; 	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	//バッファへのポインタ
	D3DXVECTOR3 m_pos;						//位置
};

#endif
