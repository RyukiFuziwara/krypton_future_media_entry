//==============================================
//
//パーティクルのビルボード(particle.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"particle.h"
#include"texture.h"

//****************//
//   マクロ定義   //
//****************//
#define MAX_LIFE (50)
#define ADD_MOVE_INIT (4.0f)

//==============================================
//コンストラクタ
//==============================================
CParticle::CParticle()
{
	//初期設定
	m_Addmove = ADD_MOVE_INIT;
	m_nLife = MAX_LIFE;
}
//==============================================
//デスストラクタ
//==============================================
CParticle::~CParticle()
{

}
//==============================================
//パーティクルのビルボードの初期化処理
//==============================================
HRESULT CParticle::Init(void)
{
	CBillboard::Init();

	//テクスチャ取得
	CTexture *pTexture = CManager::GetTexture();

	//移動量設定
	m_move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 8 - 4);
	m_move.y = cosf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 8 - 4);
	m_move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 8 - 4);

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),0.0f);

	//タイプ設定
	SetType(TYPE_PARTICLE);

	return S_OK;
}
//==============================================
//パーティクルのビルボードの終了処理
//==============================================
void CParticle::Uninit(void)
{
	//終了処理
	CBillboard::Uninit();
}
//==============================================
//パーティクルのビルボードのメモリ生成処理
//==============================================
CParticle *CParticle::Create(void)
{
	CParticle *pParticle;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pParticle = new CParticle;

	if (pParticle != NULL)
	{
		//初期化処理
		pParticle->Init();

		//テクスチャ設定
		CTexture *pTexture = CManager::GetTexture();
		pParticle->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_EFFECT));
	}

	return pParticle;
}
//==============================================
//パーティクルのビルボードの更新処理
//==============================================
void CParticle::Update(void)
{
	D3DXVECTOR3 pos;

	m_nLife--;

	if (m_nLife <= 0)
	{//寿命がなくなったとき

		//終了処理
		Uninit();
	}
	else
	{
		
		if (m_nLife >= MAX_LIFE)
		{
			//位置取得
			pos = GetPos();
		}
		else
		{
			//色設定
			SetCol(GetCol(), ((float)m_nLife / (float)MAX_LIFE));

			//位置取得
			pos = GetPos();

			//移動量代入
			pos.x += m_move.x * m_Addmove;
			pos.y += m_move.y * m_Addmove;
			pos.z += m_move.z * m_Addmove;

			//移動量減衰
			m_move.x += (0.0f - m_move.x) * 0.3f;
			m_move.y += (0.0f - m_move.y) * 0.3f;
			m_move.z += (0.0f - m_move.z) * 0.3f;
		}

		//位置設定
		SetPos(pos,GetScale());
	}
}
//==============================================
//パーティクルのビルボードの描画処理
//==============================================
void CParticle::Draw(void)
{
	//描画処理
	CBillboard::Draw();
}