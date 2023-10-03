//==============================================
//
//ライフ(Life.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"life.h"
#include"texture.h"

//****************//
//   マクロ定義   //
//****************//
#define GAUGE_POS	(D3DXVECTOR3(640.0f,70.0f, 0.0f))		//位置の初期値
#define GAUGE		(D3DXVECTOR3(200.0f,10.0f,0.0f))		//位置の初期値
#define COLOR		(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))		//色
//==============================================
//コンストラクタ
//==============================================
CLife::CLife()
{
	m_nGauge = GAUGE;
	m_nGaugeTemp = m_nGauge;
	m_nLife = 0;
	m_nLifeTemp = 0;
}
//==============================================
//デスストラクタ
//==============================================
CLife::~CLife()
{

}
//==============================================
//ライフの初期化処理
//==============================================
HRESULT CLife::Init(void)
{
	//初期化処理
	CUI::Init();

	//タイプ設定
	SetType(TYPE_LIFE);

	//位置設定
	SetPos(GAUGE_POS,m_nGauge);

	return S_OK;
}
//==============================================
//ライフの終了処理
//==============================================
void CLife::Uninit(void)
{
	//終了処理
	CUI::Uninit();
}
//==============================================
//ライフのメモリ生成処理
//==============================================
CLife *CLife::Create(void)
{
	CLife *pLife;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pLife = new CLife;

	if (pLife != NULL)
	{
		//初期化処理
		pLife->Init();

		pLife->SetCol(COLOR,0.0f);
	}

	return pLife;
}
//==============================================
//ライフの更新処理
//==============================================
void CLife::Update(void)
{
	
}
//==============================================
//ライフの描画処理
//==============================================
void CLife::Draw(void)
{
	//描画処理
	CUI::Draw();
}
//==============================================
//ライフの設定処理
//==============================================
void CLife::Set(int life)
{
	m_nLife = life;

	m_nLifeTemp = m_nLife;
}
//==============================================
//ライフの減算処理
//==============================================
void CLife::Sub(int nValue)
{
	m_nLife += nValue;

 	float gauge = m_nGaugeTemp.x / (float)m_nLifeTemp;

	m_nGauge.x -= gauge * 2.0f;

  	SetGauge(m_nGauge.x);
}