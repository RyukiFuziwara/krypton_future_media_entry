//==============================================
//
//タイトル(title.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "title.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "object3D.h"
#include "cylinder.h"
#include "block.h"
#include "file.h"
#include "player.h"
#include "manager.h"
#include "sound.h"

#define TITLE_UI_SCALE		( D3DXVECTOR3(300.0f, 90.0f, 0.0f))		//スコアランクUI
#define ENTER_UI_SCALE		( D3DXVECTOR3(200.0f, 100.0f, 0.0f))	//今回のスコアUI
#define CONTROL_UI_SCALE	( D3DXVECTOR3(640.0f, 360.0f, 0.0f))	//操作画面の大きさ
//==============================================
//コンストラクタ
//==============================================
CTitle::CTitle()
{
	m_bCon = false;
}
//==============================================
//デスストラクタ
//==============================================
CTitle::~CTitle()
{

}
//==============================================
//タイトルの初期化処理
//==============================================
HRESULT CTitle::Init(void)
{
	//オブジェクトの生成処理
	CObject *pObject[MAX_OBJECT] = {};										//オブジェクトのインスタンスを生成

	pObject[0] = CObject3D::Create();										//3Dオブジェクト生成処理
	pObject[1] = CCylinder::Create();										//シリンダー生成処理
	pObject[2] = CFile::ObjectLoad<CBlock>("data\\FILE\\CSV\\block.csv");	//ブロック生成処理	

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		Obj2D[nCnt] = new CObject2D;
	}

	if (Obj2D != NULL)
	{
		Obj2D[0] = CObject2D::Create();
		Obj2D[0]->SetPos(D3DXVECTOR3(640.0f, 160.0f, 0.0f), TITLE_UI_SCALE);

		Obj2D[1] = CObject2D::Create();
		Obj2D[1]->SetPos(D3DXVECTOR3(640.0f,560.0f, 0.0f), ENTER_UI_SCALE);

		//テクスチャ設定
		CTexture *pTexture = CManager::GetTexture();
		Obj2D[0]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_TITLE));
		Obj2D[1]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_ENTER));
	}

	//BGM設定
	CManager::GetSound()->PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}
//==============================================
//タイトルの終了処理
//==============================================
void CTitle::Uninit(void)
{	
	CObject::ReleaseAll();
}
//==============================================
//タイトルの生成処理
//==============================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle;

	//メモリ生成
	pTitle = new CTitle;

	if (pTitle != NULL)
	{
		pTitle->Init();
	}

	return pTitle;
}
//==============================================
//タイトルの更新処理
//==============================================
void CTitle::Update(void)
{
	//キーボードの情報を取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (m_bCon == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true)
		{//ENTERキーを押した時

			CFade::SetFade(CFade::FADE::FADE_OUT);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true)
	{//ENTERキーを押した時

		Obj2D[2] = CObject2D::Create();
		Obj2D[2]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f), CONTROL_UI_SCALE);

		//テクスチャ設定
		CTexture *pTexture = CManager::GetTexture();
		Obj2D[2]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_CONTROL));

		//BGM設定
		CManager::GetSound()->PlaySound(SOUND_LABEL_BUTTON);

		m_bCon = true;
		
	}

	if (CFade::GetbNext() == true)
	{
		Uninit();
		CManager::SetMode(CScene::MODE_GAME);
	}
}
//==============================================
//タイトルの描画処理
//==============================================
void CTitle::Draw(void)
{

}