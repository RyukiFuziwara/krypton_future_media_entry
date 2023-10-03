//==============================================
//
//岩(rock.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _rock_H_
#define _rock_H_

#include"objX.h"

//**************************//
//2Dオブジェクトクラスの定義//
//**************************//
class CRock : public CObjX
{
public:	//アクセス可能

	CRock();									//コンストラクタ
	virtual~CRock();							//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);										//初期処理
	virtual void Uninit(void);										//終了処理
	virtual void Update(void);										//更新処理
	virtual void Draw(void);										//描画処理

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)					//位置設定処理
	{
		m_pos = pos;
		m_scale = scale;
		CObjX::SetPos(m_pos, m_scale);
	};

	void SetRot(D3DXVECTOR3 rot)									//角度設定処理
	{
		m_rot = rot; CObjX::SetRot(m_rot);
	}

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
	static CRock *Create(void);									//メモリ生成処理

private: //アクセス(メンバ関数内)

		 //メンバ変数
	D3DXVECTOR3				m_pos;										//位置
	static D3DXVECTOR3		m_rot;										//角度
	D3DXVECTOR3				m_move;										//移動
	D3DXVECTOR3				m_scale;									//角度
	bool					m_bsmash;									//飛ばすフラグ
	int						m_nCnt;										//エフェクトカウント
	D3DXVECTOR3				m_spin;										//角度
	int						m_nCntEfe;										//エフェクトカウント

};

#endif