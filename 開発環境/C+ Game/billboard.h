//==============================================
//
//ビルボード(billvoard.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include"object.h"

//**************************//
//2Dオブジェクトクラスの定義//
//**************************//
class CBillboard : public CObject
{
public:	//アクセス可能

	CBillboard();										//コンストラクタ
	virtual~CBillboard();								//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);							//初期処理
	virtual void Uninit(void);							//終了処理
	virtual void Update(void);							//更新処理
	virtual void Draw(void);							//描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);		//テクスチャの割り当て

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	//位置設定処理
	void SetCol(D3DXCOLOR col, float fRadius);				//色設定処理

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//位置取得処理
	D3DXVECTOR3 GetScale(void) { return m_scale; }		//角度取得処理
	D3DXCOLOR	GetCol(void) { return m_col; }		//角度取得処理

	//静的メンバ関数
	static CBillboard *Create(void);					//メモリ生成処理

private: //アクセス(メンバ関数内)

	//メンバ変数
	static LPDIRECT3DTEXTURE9	m_pTexture; 			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffer;			//バッファへのポインタ
	D3DXMATRIX					m_mtxworld;				//ワールドマトリックス
	D3DXVECTOR3					m_pos;					//位置
	D3DXVECTOR3					m_scale;				//大きさ
	D3DXCOLOR					m_col;				//大きさ
};

#endif