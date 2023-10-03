//==============================================
//
//エフェクトのビルボード(effect.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"effect.h"
#include"texture.h"

//****************//
//   マクロ定義   //
//****************//
#define MAX_LIFE (20)

//==============================================
//コンストラクタ
//==============================================
CEffect::CEffect()
{
	//初期設定
	m_nLife = MAX_LIFE;
}
//==============================================
//デスストラクタ
//==============================================
CEffect::~CEffect()
{

}
//==============================================
//エフェクトのビルボードの初期化処理
//==============================================
HRESULT CEffect::Init(void)
{
	//初期化処理
	CBillboard::Init();

	//エラーの設定
	SetType(TYPE_EFFECT);

	//初期設定
	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);

	return S_OK;
}
//==============================================
//エフェクトのビルボードの終了処理
//==============================================
void CEffect::Uninit(void)
{
	//終了処理
	CBillboard::Uninit();
}
//==============================================
//エフェクトのビルボードのメモリ生成処理
//==============================================
CEffect *CEffect::Create(void)
{
	CEffect *pEffect;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		//初期化処理
		pEffect->Init();

		//テクスチャ設定
		CTexture *pTexture = CManager::GetTexture();
		pEffect->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_EFFECT));
	}

	return pEffect;
}
//==============================================
//エフェクトのビルボードの更新処理
//==============================================
void CEffect::Update(void)
{
	//色設定
	SetCol(GetCol(), ((float)m_nLife / (float)MAX_LIFE));

	m_nLife--;

	if (m_nLife <= 0)
	{//寿命がなくなったとき

		//終了処理
		Uninit();
	}
}
//==============================================
//エフェクトのビルボードの描画処理
//==============================================
void CEffect::Draw(void)
{
	//描画処理
	CBillboard::Draw();
}