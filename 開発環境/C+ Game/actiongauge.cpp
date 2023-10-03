//==============================================
//
//アクションゲージ(actiongauge.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"actiongauge.h"
#include"texture.h"
#include"player.h"

//****************//
//   マクロ定義   //
//****************//
#define GAUGE_POS		(D3DXVECTOR3(170.0f,130.0f, 0.0f))		//位置の初期値
#define GAUGE			(D3DXVECTOR3(150.0f,20.0f,0.0f))		//位置の初期値
#define MAX_GAUGE		(600)									//ゲージ値の初期値
#define COLOR			(D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f))		//色


//静的メンバ変数宣言
int CActiongauge::m_nActiongauge = 0;
int CActiongauge::m_nActiongaugeTemp = 0;
//==============================================
//コンストラクタ
//==============================================
CActiongauge::CActiongauge()
{
	m_nGauge = GAUGE;
	m_nGaugeTemp = m_nGauge;
}
//==============================================
//デスストラクタ
//==============================================
CActiongauge::~CActiongauge()
{

}
//==============================================
//ライフの初期化処理
//==============================================
HRESULT CActiongauge::Init(void)
{
	//初期化処理
	CGauge::Init();

	//タイプ設定
	SetType(TYPE_GAUGE);

	//位置設定
	SetPos(GAUGE_POS, m_nGauge);

	Set(MAX_GAUGE);

	return S_OK;
}
//==============================================
//ライフの終了処理
//==============================================
void CActiongauge::Uninit(void)
{
	//終了処理
	CGauge::Uninit();
}
//==============================================
//ライフのメモリ生成処理
//==============================================
CActiongauge *CActiongauge::Create(void)
{
	CActiongauge *pActionGauge;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pActionGauge = new CActiongauge;

	if (pActionGauge != NULL)
	{
		//初期化処理
		pActionGauge->Init();

		pActionGauge->SetCol(COLOR, 0.0f);
	}

	return pActionGauge;
}
//==============================================
//ライフの更新処理
//==============================================
void CActiongauge::Update(void)
{
	if ((CPlayer::GetAction()) == true)
	{
		CPlayer::SetAction(false);
		AddSub(ACTION_COST);
	}
	if (m_nActiongauge < MAX_GAUGE )
	{
		if (CPlayer::GetCon() != CPlayer::CONTROL_ALL)
		{
			AddSub(HEAL_VALUE * 2);
		}
		else
		{
			AddSub(HEAL_VALUE);
		}
	}
}
//==============================================
//ライフの描画処理
//==============================================
void CActiongauge::Draw(void)
{
	//描画処理
	CGauge::Draw();
}
//==============================================
//ライフの設定処理
//==============================================
void CActiongauge::Set(int Actiongauge)
{
	m_nActiongauge = Actiongauge;

	m_nActiongaugeTemp = m_nActiongauge;
}
//==============================================
//ライフの減算処理
//==============================================
void CActiongauge::AddSub(int nValue)
{
	if (m_nActiongauge + nValue > 0)
	{
		m_nActiongauge += nValue;

		float gauge = m_nGaugeTemp.x / (float)m_nActiongaugeTemp;

		m_nGauge.x += gauge * 2.0f * nValue;

		SetGauge(m_nGauge.x);
	}
}