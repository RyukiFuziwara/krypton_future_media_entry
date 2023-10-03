//==============================================
//
//ブロック(block.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _block_H_
#define _block_H_

#include"objX.h"

//**************************//
//2Dオブジェクトクラスの定義//
//**************************//
class CBlock : public CObjX
{
public:	//アクセス可能

	CBlock();									//コンストラクタ
	virtual~CBlock();							//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);										//初期処理
	virtual void Uninit(void);										//終了処理
	virtual void Update(void);										//更新処理
	virtual void Draw(void);										//描画処理

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)					//位置設定処理
	{m_pos = pos;
	m_scale = scale;
	CObjX::SetPos(m_pos, m_scale);
	};

	void SetRot(D3DXVECTOR3 rot)									//角度設定処理
	{m_rot = rot; CObjX::SetRot(m_rot);}

	D3DXVECTOR3 GetPos(void) { return m_pos; }						//位置取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//角度取得処理

	static bool Collision(D3DXVECTOR3 *pPos,
		D3DXVECTOR3 pPosOld,
		D3DXVECTOR3 *pMove,
		D3DXVECTOR3 scale,
		float fWidth,
		float fHeight,
		bool bflag);

	//静的メンバ関数
	static CBlock *Create(void);										//メモリ生成処理

	static void InitDest(void) { m_nDest = 0; }							//破壊数初期化

private: //アクセス(メンバ関数内)

	//メンバ変数
	D3DXVECTOR3				m_pos;										//位置
	D3DXVECTOR3				m_rot;										//角度
	D3DXVECTOR3				m_move;										//移動
	D3DXVECTOR3				m_scale;									//角度
	bool					m_bsmash;									//飛ばすフラグ
	int						m_nCnt;										//エフェクトカウント
	int						m_nLife;									//体力
	static int				m_nDest;									//破壊数
};

#endif
