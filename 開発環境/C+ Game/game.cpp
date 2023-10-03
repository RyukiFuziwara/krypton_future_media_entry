//==============================================
//
//ゲーム(game.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"game.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"score.h"
#include"time.h"
#include"object3D.h"
#include"player.h"
#include"enemy.h"
#include"object.h"
#include"cylinder.h"
#include"block.h"
#include"file.h"
#include"actiongauge.h"
#include"opegauge.h"

#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//位置Yの初期値
//==============================================
//コンストラクタ
//==============================================
CGame::CGame()
{
}
//==============================================
//デスストラクタ
//==============================================
CGame::~CGame()
{

}
//==============================================
//ゲームの初期化処理
//==============================================
HRESULT CGame::Init(void)
{
	//オブジェクトの生成処理
	CObject *pObject[MAX_OBJECT] = {};											//オブジェクトのインスタンスを生成

	pObject[0] = CObject3D::Create();											//3Dオブジェクト生成処理
	pObject[1] = CCylinder::Create();											//シリンダー生成処理

	pObject[2] = CPlayer::Create();											//プレイヤー生成処理
	pObject[2]->SetType(CObject::TYPE_PLAYER_R);								//プレイヤータイプ処理

	CPlayer *pPlayer;
	pPlayer = CPlayer::Create();											//プレイヤー生成処理
	pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 1050.0f), VECTOR_INIT);				//位置設定処理
	pObject[3] = pPlayer;

	pObject[4] = CEnemy::Create();											//敵生成処理

	pObject[5] = CFile::ObjectLoad<CBlock>("data\\FILE\\CSV\\block.csv");		//ブロック生成処理

	CScore *pScore = CScore::Create();											//スコア生成処理
	pScore->SetPosOrg(D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	pObject[6] = pScore;

	pObject[7] = CTime::Create();												//タイム生成処理

	pObject[8] = CActiongauge::Create();										//アクションゲージ生成処理

	COpegauge *pGauge;
	pGauge = COpegauge::Create();
	pObject[9] = pGauge;														//アクションゲージ生成処理
	m_obj = pGauge;

	CScene::Init();

	//BGM設定
	CManager::GetSound()->PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}
//==============================================
//ゲームの終了処理
//==============================================
void CGame::Uninit(void)
{
	CScene::Uninit();

	//全開放処理
	CObject2D::ReleaseAll();
}
//==============================================
//ゲームの生成処理
//==============================================
CGame *CGame::Create(void)
{
	CGame *pGame;

	//メモリ生成
	pGame = new CGame;

	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}
//==============================================
//ゲームの更新処理
//==============================================
void CGame::Update(void)
{
	CScene::Update();

	if (CTime::GetNum() <= 0 || CEnemy::GetFormType() == CEnemy::BOSS_FORM_MAX || m_obj->GetLife() == 0)
	{
		Uninit();

		CBlock::InitDest();

		CManager::SetMode(CScene::MODE_RESULT);

		CManager::GetSound()->StopSound();
	}
}
//==============================================
//ゲームの描画処理
//==============================================
void CGame::Draw(void)
{

}