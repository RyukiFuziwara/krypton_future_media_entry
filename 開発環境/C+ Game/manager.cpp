//==============================================
//
//マネージャー(manager.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"camera.h"
#include"light.h"
#include"texture.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"pause.h"

//****************//
//   マクロ定義   //
//****************//

//静的メンバ宣言
CTexture *CManager::m_pTexture = NULL;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputKeyPad *CManager::m_pInputKeyPad = NULL;
CSound *CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CScene *CManager::m_pScene = NULL;
CFade  *CScene::m_pfade = NULL;
CScene::MODE CScene::m_mode = CScene::MODE_TITLE;
//==============================================
//コンストラクタ
//==============================================
CManager::CManager()
{
	
}
//==============================================
//デスストラクタ
//==============================================
CManager::~CManager()
{

}
//==============================================
//初期化処理
//==============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pRenderer = new CRenderer;			//レンダーのインスタンスを生成

	if (m_pRenderer != NULL)
	{//メモリ確保できているとき

		//初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//初期化処理が失敗したとき8 ji
			return -1;
		}
	}

	m_pInputKeyboard = new CInputKeyboard;	//キーボードのインスタンスを生成

 	if (m_pInputKeyboard != NULL)
	{//メモリ確保できているとき

		//キーボードの初期化処理
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//初期化処理が失敗したとき
			return E_FAIL;
		}
	}

	m_pInputKeyPad = new CInputKeyPad;	//キーボードのインスタンスを生成

	if (m_pInputKeyPad != NULL)
	{//メモリ確保できているとき

	 //キーパッドの初期化処理
		if (FAILED(m_pInputKeyPad->Init(hInstance, hWnd)))
		{//初期化処理が失敗したとき
			return E_FAIL;
		}
	}

	m_pSound = new CSound;	//サウンドのインスタンスを生成

	if (m_pSound != NULL)
	{//メモリ確保できているとき

		//サウンドの初期化処理
		if (FAILED(m_pSound->Init(hWnd)))
		{//初期化処理が失敗したとき
			return E_FAIL;
		}
	}

	m_pCamera = new CCamera;	//カメラのインスタンスを生成

	if (m_pCamera != NULL)
	{//メモリ確保できているとき

	 //カメラの初期化処理
		if (FAILED(m_pCamera->Init()))
		{//初期化処理が失敗したとき
			return E_FAIL;
		}
	}

	m_pLight = new CLight;	//ライトのインスタンスを生成

	if (m_pLight != NULL)
	{//メモリ確保できているとき

	 //カメラの初期化処理
		if (FAILED(m_pLight->Init()))
		{//初期化処理が失敗したとき
			return E_FAIL;
		}
	}

	//テクスチャ読み込み
	m_pTexture = new CTexture;
	m_pTexture->Load();

	m_pScene = CScene::Create(CScene::MODE_TITLE);

	return S_OK;
}
//==============================================
//終了処理
//==============================================
void CManager::Uninit(void)
{
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}

	//キーボードの終了処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//キーパッドの終了処理
	if (m_pInputKeyPad != NULL)
	{
		m_pInputKeyPad->Uninit();

		delete m_pInputKeyPad;
		m_pInputKeyPad = NULL;
	}

	//レンダーの終了処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//サウンドの終了処理
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//カメラの終了処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//ライトの終了処理
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	//テクスチャの破棄
	m_pTexture->Unload();
	m_pTexture = NULL;
}
//==============================================
//更新処理
//==============================================
void CManager::Update(void)
{
	//キーボードの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//キーパッドの更新処理
	if (m_pInputKeyPad!= NULL)
	{
		m_pInputKeyPad->Update();
	}

	//レンダーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//カメラの更新処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//ライトの更新処理
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	if (m_pScene != NULL)
	{
		m_pScene->Update();
	}
}
//==============================================
//描画処理
//==============================================
void CManager::Draw(int nCount)
{
	//レンダーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->SetFPS(nCount);

		m_pRenderer->Draw();
	}

	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}
}
//==============================================
//モードの取得処理
//==============================================
void CManager::SetMode(CScene::MODE mode)
{
	//サウンド停止
	m_pSound->StopSound();

	//破棄
	delete m_pScene;
	m_pScene = NULL;

	//シーン生成
	m_pScene = CScene::Create(mode);
}
//==============================================
//モードの取得処理
//==============================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}
//==============================================
//レンダラー取得処理
//==============================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//==============================================
//キーボード取得処理
//==============================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//==============================================
//キーパッド取得処理
//==============================================
CInputKeyPad *CManager::GetInputKeyPad(void)
{
	return m_pInputKeyPad;
}
//==============================================
//カメラ取得処理
//==============================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}
//==============================================
//テクスチャ取得処理
//==============================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}
//==============================================
//サウンドの取得処理
//==============================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}
//==============================================
//コンストラクタ
//==============================================
CScene::CScene()
{

}
//==============================================
//デスストラクタ
//==============================================
CScene::~CScene()
{

}
//==============================================
//シーンの初期化処理
//==============================================
HRESULT CScene::Init()
{	
	//シーン生成
	CPause *pPause = CPause::Create();
	m_pPause = pPause;

	return S_OK;
}
//==============================================
//シーンの終了処理
//==============================================
void CScene::Uninit()
{
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();

		//破棄
		delete m_pPause;
		m_pPause = NULL;
	}
}
//==============================================
//シーンの生成処理
//==============================================
CScene *CScene::Create(CScene::MODE mode)
{
	CScene *pScene;

	//メモリ生成
	pScene = new CScene;

	if (pScene != NULL)
	{
		//モードを設定
		m_mode = mode;

		switch (m_mode)
		{
		case MODE_TITLE:

			pScene = CTitle::Create();

			break;

		case MODE_GAME:

			pScene = CGame::Create();

			break;

		case MODE_RESULT:

			pScene = CResult::Create();

			break;
		}

		m_pfade = new CFade;

		if (m_pfade != NULL)
		{
			m_pfade->Init();
			m_pfade->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		}
	}
	
	return pScene;
}
//==============================================
//シーンの更新処理
//==============================================
void CScene::Update()
{
	if (m_pPause != NULL)
	{
		m_pPause->Update();
	}
}
//==============================================
//シーンの描画処理
//==============================================
void CScene::Draw()
{

}