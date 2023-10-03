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
#include"opegauge.h"
#include"texture.h"
#include"player.h"
#include"life.h"

//****************//
//   マクロ定義   //
//****************//
#define GAUGE_POS		(D3DXVECTOR3(640.0f,650.0f, 0.0f))		//位置の初期値
#define GAUGE			(D3DXVECTOR3(400.0f,20.0f,0.0f))		//位置の初期値
#define MAX_GAUGE		(1200)									//ゲージ値の初期値
#define COLOR			(D3DXCOLOR(0.0f, 1.0f, 0.5f, 1.0f))		//色

//静的メンバ変数宣言
int COpegauge::m_nOpegauge = 0;
int COpegauge::m_nOpegaugeTemp = 0;
//==============================================
//コンストラクタ
//==============================================
COpegauge::COpegauge()
{
	m_nGauge = GAUGE;
	m_nGaugeTemp = m_nGauge;
	m_nLife = 1;
}
//==============================================
//デスストラクタ
//==============================================
COpegauge::~COpegauge()
{

}
//==============================================
//ライフの初期化処理
//==============================================
HRESULT COpegauge::Init(void)
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
void COpegauge::Uninit(void)
{
	//終了処理
	CGauge::Uninit();
}
//==============================================
//ライフのメモリ生成処理
//==============================================
COpegauge *COpegauge::Create(void)
{
	COpegauge *pOpeGauge;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pOpeGauge = new COpegauge;

	if (pOpeGauge != NULL)
	{
		//初期化処理
		pOpeGauge->Init();

		pOpeGauge->SetCol(COLOR, 0.0f);
	}

	return pOpeGauge;
}
//==============================================
//ライフの更新処理
//==============================================
void COpegauge::Update(void)
{
	if (CPlayer::GetOperation() > 375 && CPlayer::GetCon() != CPlayer::CONTROL_ALL)
	{
		AddSub(-1);
	}

	if(CPlayer::GetDamage() == true)
	{
		AddSub(-40);
		CPlayer::SetDamage(false);
	}
}
//==============================================
//ライフの描画処理
//==============================================
void COpegauge::Draw(void)
{
	//描画処理
	CGauge::Draw();
}
//==============================================
//ライフの設定処理
//==============================================
void COpegauge::Set(int Opegauge)
{
	m_nOpegauge = Opegauge;

	m_nOpegaugeTemp = m_nOpegauge;
}
//==============================================
//ライフの減算処理
//==============================================
void COpegauge::AddSub(int nValue)
{
	if (m_nOpegauge + nValue >= 0)
	{
		m_nOpegauge += nValue;

		float gauge = m_nGaugeTemp.x / (float)m_nOpegaugeTemp;

		m_nGauge.x += gauge * 2.0f * nValue;

		SetGauge(m_nGauge.x);
	}
	else
	{
		m_nOpegauge += MAX_GAUGE;

		float gauge = m_nGaugeTemp.x / (float)m_nOpegaugeTemp;

		m_nGauge.x += gauge * 2.0f * MAX_GAUGE;

		SetGauge(m_nGauge.x);

		m_nLife--;
	}
}