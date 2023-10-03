//==============================================
//
//ブロック(block.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"block.h"
#include"texture.h"
#include"texture.h"
#include"file.h"
#include"enemy.h"
#include"effect.h"
#include"particle.h"

#define MAX_WIDTH (30.0f)
#define MAX_HEIGHT (30.0f)
#define PARTICLE_INIT		(D3DXVECTOR3(50.0f,50.0f,0.0f))		//位置Yの初期値

int CBlock::m_nDest = 0;
//==============================================
//コンストラクタ
//==============================================
CBlock::CBlock()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 3;
}
//==============================================
//デスストラクタ
//==============================================
CBlock::~CBlock()
{

}
//==============================================
//ブロックの初期化処理
//==============================================
HRESULT CBlock::Init(void)
{
	SetFile("data\\MODEL\\ORNAMENT\\block.x");

	//初期化処理
	CObjX::Init();

	//タイプ設定
	SetType(TYPE_BLOCK);

	return S_OK;
}
//==============================================
//ブロックの終了処理
//==============================================
void CBlock::Uninit(void)
{
	//終了処理
	CObjX::Uninit();
}
//==============================================
//ブロックのメモリ生成処理
//==============================================
CBlock *CBlock::Create(void)
{
	CBlock *pblock;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pblock = new CBlock;

	if (pblock != NULL)
	{
		//初期化処理
		pblock->Init();
	}

	return pblock;
}
//==============================================
//ブロックの更新処理
//==============================================
void CBlock::Update(void)
{
	if (m_bsmash == true)
	{
		if ((m_nCnt % 4) == 0)
		{
			//エフェクトの生成
			CEffect *pEffect;
			pEffect = CEffect::Create();
			pEffect->SetPos(m_pos, SCALE_INIT * 3.0f);
			pEffect->SetCol(D3DXCOLOR(0.6f, 0.4f, 0.4f, 0.0f), 0.0f);
		}

		m_nCnt++;

		m_rot.z += 0.2f;
		SetRot(m_rot);

		m_move.x += 20.0f * sinf(GetRot().y);
		m_move.y += 2.5f;
		m_move.z += 20.0f * cosf(GetRot().y);

		m_pos += m_move;
		SetPos(m_pos, m_scale);

		m_move.x += (0.0f - m_move.x) * 1.0f;
		m_move.y += (0.0f - m_move.y) * 1.0f;
		m_move.z += (0.0f - m_move.z) * 1.0f;

		if (CEnemy::Collision(&m_pos, &m_move, m_scale, MAX_WIDTH, MAX_HEIGHT) == true)
		{
			for (int nCntPar = 0; nCntPar < 18; nCntPar++)
			{
				CParticle *pParticle;
				pParticle = CParticle::Create();
				pParticle->SetPos(m_pos, D3DXVECTOR3(200.0f, 200.0f, 200.0f));
				pParticle->SetCol(D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f), 0.0f);
				pParticle->SetAddMove(40.0f);
			}

			m_nDest++;

			Uninit();
		}
	}
	else if(m_nLife <= 0)
	{
		for (int nCntpar = 0; nCntpar < 16; nCntpar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(GetPos(), PARTICLE_INIT);
			pParticle->SetCol(D3DXCOLOR(0.8f, 0.5f, 0.4f, 0.0f), 0.0f);
		}

		m_nDest++;

		Uninit();
	}

	if (m_nDest >= 8)
	{
		CFile::ObjectLoad<CBlock>("data\\FILE\\CSV\\block.csv");//ブロック生成処理

		m_nDest = 0;
	}
}
//==============================================
//ブロックの描画処理
//==============================================
void CBlock::Draw(void)
{
	//描画処理
	CObjX::Draw();
}
//==============================================
//ブロックの当たり判定処理
//==============================================
bool CBlock::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove,D3DXVECTOR3 scale, float fWidth, float fHeight,bool bflag)
{
	CObject *pObj;

	//オブジェクトの先頭を取得
	pObj = CObject::GetTop();

	while (pObj != NULL)
	{//メモリがあるとき

		//次のオブジェクトを保存しておく
		CObject *pObjectNext = pObj->GetNext();

		TYPE typObje;

		typObje = pObj->GetType();

		if (typObje == TYPE_BLOCK)
		{//オブジェクトがブロックのとき

			//オブジェクトをブロックにキャスト
			CBlock *pObjblock = dynamic_cast<CBlock*>(pObj);

			if (pPos->x + (scale.x * fWidth) >= pObjblock->GetPos().x + sinf(pObjblock->GetRot().y) - (pObjblock->GetScale().x * MAX_WIDTH)
				&& pPos->x - (scale.x * fWidth) <= pObjblock->GetPos().x + sinf(pObjblock->GetRot().y) + (pObjblock->GetScale().x * MAX_WIDTH)
				&& pPos->y + (scale.y * fHeight) >= pObjblock->GetPos().y + sinf(pObjblock->GetRot().y) - (pObjblock->GetScale().y * MAX_HEIGHT)
				&& pPos->y - (scale.y * fHeight) <= pObjblock->GetPos().y + sinf(pObjblock->GetRot().y) + (pObjblock->GetScale().y * MAX_HEIGHT)
				&& pPos->z + (scale.z * fHeight) >= pObjblock->GetPos().z + cosf(pObjblock->GetRot().y) - (pObjblock->GetScale().z * MAX_HEIGHT)
				&& pPos->z - (scale.z * fHeight)<= pObjblock->GetPos().z  + cosf(pObjblock->GetRot().y) + (pObjblock->GetScale().z * MAX_HEIGHT))
			{//ブロックの範囲内

				if (bflag == true)
				{
					pObjblock->m_bsmash = true;
				}
				else
				{
					pObjblock->m_nLife--;
				}

				return true;
			}
		}

		pObj = pObjectNext;
	}

 	return false;
}