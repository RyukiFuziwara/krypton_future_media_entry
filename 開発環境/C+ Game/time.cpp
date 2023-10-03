//==============================================
//
//タイム(Time.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"time.h"
#include"texture.h"

//****************//
//   マクロ定義   //
//****************//
#define	SECOND_FLAME	(120)
#define SCALE			(D3DXVECTOR3(30.0f, 60.0f, 0.0f))		//大きさの初期値


//静的メンバ変数宣言
CTime *CTime::m_apTime[MAX_NUM_TIME] = {};
int CTime::m_AgtNum = 0;
int CTime::m_nTime = 0;
int CTime::m_nTimeFlame = SECOND_FLAME;
//==============================================
//コンストラクタ
//==============================================
CTime::CTime()
{

}
//==============================================
//デスストラクタ
//==============================================
CTime::~CTime()
{
	m_AgtNum = 0;
}
//==============================================
//タイムの初期化処理
//==============================================
HRESULT CTime::Init(void)
{
	//初期化処理
	CUI::Init();

	//タイプ設定
	SetType(TYPE_TIME);

	//タイムの総数
	m_AgtNum++;

	//位置設定
	CTime::SetPos(D3DXVECTOR3((560.0f + (50.0f * m_AgtNum)), 30.0f, 0.0f), SCALE);

	return S_OK;
}
//==============================================
//タイムの終了処理
//==============================================
void CTime::Uninit(void)
{
	//終了処理
	CUI::Uninit();
}
//==============================================
//タイムのメモリ生成処理
//==============================================
CTime *CTime::Create(void)
{
	//テクスチャ取得
	CTexture *pTexture = CManager::GetTexture();

	for (int nCount = 0; nCount < MAX_NUM_TIME; nCount++)
	{
		//メモリ生成
		m_apTime[nCount] = new CTime;

		if (m_apTime[nCount] != NULL)
		{
			//初期化処理
			m_apTime[nCount]->Init();

			//テクスチャ設定
			m_apTime[nCount]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_NUMBER));
		}
	}

	//初期値設定
	SetNum(90);

	return *m_apTime;
}
//==============================================
//タイムの更新処理
//==============================================
void CTime::Update(void)
{
	m_nTimeFlame--;

	if (m_nTimeFlame == 0)
	{//フレームが0になったとき

		//一秒減る
		AddNum(-1);

		//フレーム再設定
		m_nTimeFlame = SECOND_FLAME;
	}
}
//==============================================
//タイムの描画処理
//==============================================
void CTime::Draw(void)
{
	//描画処理
	CUI::Draw();
}
//==============================================
//タイムの設定処理
//==============================================
void CTime::SetNum(int nTime)
{
	int aTexU[MAX_NUM_TIME];
	int nCntTime;

	//タイム設定
	m_nTime = nTime;

	aTexU[0] = m_nTime % 100 / 10;
	aTexU[1] = m_nTime % 10;

	for (nCntTime = 0; nCntTime < MAX_NUM_TIME; nCntTime++)
	{
		//テクスチャ座標設定
		m_apTime[nCntTime]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 1.0f), 10);
	}
}
//==============================================
//タイムの加算処理
//==============================================
void CTime::AddNum(int nValue)
{
	int aTexU[MAX_NUM_TIME];
	int nCntTime;

	//タイム加算
	m_nTime += nValue;

	aTexU[0] = m_nTime % 100 / 10;
	aTexU[1] = m_nTime % 10;

	for (nCntTime = 0; nCntTime < MAX_NUM_TIME; nCntTime++)
	{
		//テクスチャ座標設定
		m_apTime[nCntTime]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 1.0f), 10);
	}
}