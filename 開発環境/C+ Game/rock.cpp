//==============================================
//
//岩(rock.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"rock.h"
#include"texture.h"
#include"texture.h"
#include"file.h"
#include"enemy.h"
#include"effect.h"
#include"particle.h"
#include"object3D.h"
#include"player.h"
#include"score.h"
#include"block.h"

#define MAX_WIDTH			(30.0f)
#define MAX_HEIGHT			(30.0f)
#define PARTICLE_INIT		(D3DXVECTOR3(40.0f,40.0f,0.0f))		//位置Yの初期値

D3DXVECTOR3 CRock::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//==============================================
//コンストラクタ
//==============================================
CRock::CRock()
{
	m_spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntEfe = 0;
}
//==============================================
//デスストラクタ
//==============================================
CRock::~CRock()
{

}
//==============================================
//岩の初期化処理
//==============================================
HRESULT CRock::Init(void)
{
	SetFile("data\\MODEL\\ORNAMENT\\rock.x");

	//初期化処理
	CObjX::Init();

	SetRot(m_rot);
	m_rot.y += 0.16f;

	//移動量設定
	m_move.x = sinf(m_rot.y) * 15.0f;
	m_move.z = cosf(m_rot.y) * 15.0f;

	//タイプ設定
	SetType(TYPE_ROCK);

	return S_OK;
}
//==============================================
//岩の終了処理
//==============================================
void CRock::Uninit(void)
{
	//終了処理
	CObjX::Uninit();
}
//==============================================
//岩のメモリ生成処理
//==============================================
CRock *CRock::Create(void)
{
	CRock *prock;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	prock = new CRock;

	if (prock != NULL)
	{
		//初期化処理
		prock->Init();
	}

	return prock;
}
//==============================================
//岩の更新処理
//==============================================
void CRock::Update(void)
{
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	m_spin.x += 0.08f;

	SetRot(D3DXVECTOR3(m_spin.x, m_rot.y, 0.0f));

	SetPos(m_pos, m_scale);

	m_nCntEfe++;

	//発生制限
	if (m_nCntEfe >= 18)
	{
		CParticle *pParticle;
		pParticle = CParticle::Create();
		pParticle->SetPos(m_pos, PARTICLE_INIT);
		pParticle->SetCol(D3DXCOLOR(0.2f, 0.1f, 0.0f, 0.0f), 0.0f);

		m_nCntEfe = 0;
	}

	//ステージ当たり判定
	if ((CObject3D::CollisionStage(m_pos)) == true)
	{
		for (int nCntpar = 0; nCntpar < 8; nCntpar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(m_pos, PARTICLE_INIT);
			pParticle->SetCol(D3DXCOLOR(0.8f, 0.8f, 0.4f, 0.0f), 0.0f);
		}

		Uninit();
	}
	//プレイヤーの当たり判定
	else if ((CPlayer::Collision(&m_pos, GetScale(), PARTICLE_INIT.x, PARTICLE_INIT.y)) == true)
	{
		CScore::AddNum(-200);

		for (int nCntpar = 0; nCntpar < 16; nCntpar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(GetPos(), PARTICLE_INIT);
			pParticle->SetCol(D3DXCOLOR(0.8f, 0.5f, 0.4f, 0.0f), 0.0f);
		}

		Uninit();
	}
	//ブロックの当たり判定
	else if ((CBlock::Collision(&m_pos,D3DXVECTOR3(0.0f,0.0f,0.0f), &m_move,GetScale(), PARTICLE_INIT.x, PARTICLE_INIT.y, false)) == true)
	{
		for (int nCntpar = 0; nCntpar < 16; nCntpar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(GetPos(), PARTICLE_INIT);
			pParticle->SetCol(D3DXCOLOR(0.8f, 0.5f, 0.4f, 0.0f), 0.0f);
		}

		Uninit();
	}
}
//==============================================
//岩の描画処理
//==============================================
void CRock::Draw(void)
{
	//描画処理
	CObjX::Draw();
}
