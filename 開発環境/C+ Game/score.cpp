//==============================================
//
//ライフ(Score.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"score.h"
#include"texture.h"

//****************//
//   マクロ定義   //
//****************//
#define POS		(D3DXVECTOR3(30.0f, 50.0f, 0.0f))		//位置の初期値
#define SCALE	(D3DXVECTOR3(20.0f, 40.0f, 0.0f))		//大きさの初期値

//静的メンバ変数宣言
CScore *CScore::m_apScore[MAX_NUM_SCORE] = {};
int CScore::m_AgtNum = 0;
int CScore::m_nScore = 0;
//==============================================
//コンストラクタ
//==============================================
CScore::CScore()
{
	m_pos = POS;
}
//==============================================
//デスストラクタ
//==============================================
CScore::~CScore()
{
	m_AgtNum = 0;
}
//==============================================
//ライフの初期化処理
//==============================================
HRESULT CScore::Init(void)
{
	//初期化処理
	CUI::Init();

	//タイプ設定
	SetType(TYPE_SCORE);

	//ライフの総数
	m_AgtNum++;

	//位置設定
	CScore::SetPos(D3DXVECTOR3((m_pos.x + (30.0f * m_AgtNum)), m_pos.y, 0.0f), SCALE);

	return S_OK;
}
//==============================================
//ライフの終了処理
//==============================================
void CScore::Uninit(void)
{
	//終了処理
	CUI::Uninit();
}
//==============================================
//ライフのメモリ生成処理
//==============================================
CScore *CScore::Create(void)
{
	//テクスチャの取得
	CTexture *pTexture = CManager::GetTexture();

	for (int nCount = 0; nCount < MAX_NUM_SCORE; nCount++)
	{
		//メモリ生成
		m_apScore[nCount] = new CScore;

		if (m_apScore[nCount] != NULL)
		{
			//初期化処理
			m_apScore[nCount]->Init();

			//テクスチャ設定
			m_apScore[nCount]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_NUMBER));
		}
	}

	//ライフの初期値設定
	SetNum(0);

	return *m_apScore;
}
//==============================================
//ライフの更新処理
//==============================================
void CScore::Update(void)
{
	if (m_bChange == true)
	{
		//位置設定
		CScore::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), SCALE);

		m_AgtNum++;

		m_bChange = false;
	}
	else if (m_AgtNum > 0)
	{
		CObject *pObj = this;

		//オブジェクトをプレイヤーにキャスト
		CScore *pScore = dynamic_cast<CScore*>(pObj->GetPrev());

		m_pos = D3DXVECTOR3(pScore->m_pos.x + 30.0f, pScore->m_pos.y, 0.0f);

		//位置設定
		CScore::SetPos(D3DXVECTOR3(m_pos.x,m_pos.y, 0.0f), SCALE);

		m_AgtNum++;

		if (m_AgtNum == MAX_NUM_SCORE)
		{
			m_AgtNum = 0;
		}
	}
}
//==============================================
//ライフの描画処理
//==============================================
void CScore::Draw(void)
{
	//描画処理
	CUI::Draw();
}
//==============================================
//ライフの設定処理
//==============================================
void CScore::SetNum(int nScore)
{
	int aTexU[MAX_NUM_SCORE];
	int nCntScore;

	//ライフの設定
	m_nScore = nScore;

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10;

	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		//テクスチャ座標設定
		m_apScore[nCntScore]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f),10);
	}
}
//==============================================
//ライフの加算処理
//==============================================
void CScore::AddNum(int nValue)
{
	int aTexU[MAX_NUM_SCORE];
	int nCntScore;

	//ライフ加算
	m_nScore += nValue;

	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10;

	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		//テクスチャ座標設定
 		m_apScore[nCntScore]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f), 10);
	}
}
void CScore::SetPosOrg(D3DXVECTOR3 pos)
{
	//桁数初期化
	m_AgtNum = 0;

	//位置変更
	m_pos = pos;

	m_bChange = true;
}