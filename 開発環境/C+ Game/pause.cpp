//==============================================
//
//ポーズ(pause.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "object3D.h"
#include "cylinder.h"
#include "block.h"
#include "file.h"
#include "player.h"

bool CPause::m_bPause = false;
//==============================================
//コンストラクタ
//==============================================
CPause::CPause()
{
}
//==============================================
//デスストラクタ
//==============================================
CPause::~CPause()
{

}
//==============================================
//ポーズの初期化処理
//==============================================
HRESULT CPause::Init(void)
{
	return S_OK;
}
//==============================================
//ポーズの終了処理
//==============================================
void CPause::Uninit(void)
{
	CScene::Uninit();
}
//==============================================
//ポーズの生成処理
//==============================================
CPause *CPause::Create(void)
{
	CPause *pPause;

	//メモリ生成
	pPause = new CPause;

	if (pPause != NULL)
	{
		pPause->Init();
	}

	return pPause;
}
//==============================================
//ポーズの更新処理
//==============================================
void CPause::Update(void)
{
	//キーボードの情報を取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_START) == true)
	{//ENTERキーを押した時

		if (m_bPause == false)
		{
			m_bPause = true;
		}
		else if (m_bPause == true)
		{
			m_bPause = false;
		}
	}
}
//==============================================
//ポーズの描画処理
//==============================================
void CPause::Draw(void)
{

}