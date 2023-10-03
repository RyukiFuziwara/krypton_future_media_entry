//==============================================
//
//パーティクルのビルボード(particle.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _particle_H_
#define _particle_H_

#include"billboard.h"

#define MAX_particle (4)

//**********************************//
//パーティクルのビルボードクラスの定義//
//**********************************//
class CParticle : public CBillboard
{
public:	//アクセス可能

	CParticle();									//コンストラクタ
	virtual~CParticle();							//デストラクタ

	//メンバ関数
	HRESULT Init(void);									//初期処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理

	void SetAddMove(float addmove) { m_Addmove = addmove; }

	//静的メンバ関数
	static CParticle *Create(void);					//メモリ生成処理

private: //アクセス(メンバ関数内)

	//メンバ変数
	D3DXVECTOR3 m_move;
	float		m_Addmove;
	int			m_nLife;								//体力
};

#endif
