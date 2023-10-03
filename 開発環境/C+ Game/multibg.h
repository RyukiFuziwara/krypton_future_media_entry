//==============================================
//
//多重背景(multibg.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MULTIBG_H_
#define _MULTIBG_H_

//マクロ定義
#define	 MAX_BG		(3)

#include"object2D.h"

//**************************//
//2Dオブジェクトクラスの定義//
//**************************//
class CMultibg : public CObject
{
public:	//アクセス可能

	CMultibg();											//コンストラクタ
	~CMultibg();										//デストラクタ

	//メンバ関数
	HRESULT Init(void);									//初期処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	//位置設定処理
	void SetTex(D3DXVECTOR2 tex);						//テクスチャ座標設定処理

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//位置取得処理
	D3DXVECTOR3 GetScale(void) { return m_scale; }		//大きさ取得処理

	static CMultibg *CMultibg::Create(void);

private: //アクセス(メンバ関数内)

	//メンバ変数
	static CObject2D			*m_apObject2D[MAX_BG];

	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffer;			//バッファへのポインタ
	D3DXVECTOR3					m_pos;					//位置
	D3DXVECTOR3					m_move;					//移動量
	D3DXVECTOR3					m_scale;				//大きさ
	D3DXVECTOR2					m_tex[MAX_BG];


	static char *m_aTexName[MAX_BG];
};

#endif
