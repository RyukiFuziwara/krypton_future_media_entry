//==============================================
//
//リザルト(result.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "result.h"
#include "Input.h"
#include "texture.h"
#include "score.h"
#include "file.h"
#include "manager.h"
#include "sound.h"

#define MAX_2DOBJECT	(8)									//2Dポリゴンの最大数
#define MAX_RANKING		(3)									//ランキングの数
#define RESULT_UI_SCALE	(D3DXVECTOR3(250.0f, 90.0f, 0.0f))	//リザルトUI
#define NUM_UI_SCALE	(D3DXVECTOR3(50.0f, 50.0f, 0.0f))	//順位UI
#define FRAME_UI_SCALE	(D3DXVECTOR3(190.0f, 200.0f, 0.0f))	//フレームUI
#define RANK_UI_SCALE	(D3DXVECTOR3(150.0f, 70.0f, 0.0f))	//スコアランクUI
#define YOUR_UI_SCALE	(D3DXVECTOR3(170.0f, 70.0f, 0.0f))	//今回のスコアUI
#define SCORE_UI_SCALE	(D3DXVECTOR3(940.0f,440.0f,0.0f))	//今回のスコア
#define RANK_SORT		(4)									//ソート数
//==============================================
//コンストラクタ
//==============================================
CResult::CResult()
{
}
//==============================================
//デスストラクタ
//==============================================
CResult::~CResult()
{

}
//==============================================
//リザルトの初期化処理
//==============================================
HRESULT CResult::Init(void)
{
	//テクスチャ設定
	CTexture *pTexture = CManager::GetTexture();

	//インスタンス生成
	Obj2D = new CObject2D;

	if (Obj2D != NULL)
	{
		//各設定
		Obj2D = CObject2D::Create();
		Obj2D->Init();
		Obj2D->SetPos(D3DXVECTOR3(640.0f, 100.0f, 0.0f), RESULT_UI_SCALE);
		Obj2D->BindTexture(pTexture->GetAddress(1));
	}

	//オブジェクトの生成処理
	CObject2D *pObject2D[MAX_2DOBJECT] = {};	//オブジェクトのインスタンスを生成

	pObject2D[0] = CObject2D::Create();			//枠UI
	pObject2D[0]->SetPos(D3DXVECTOR3(240.0f, 440.0f, 0.0f), FRAME_UI_SCALE);
	pObject2D[0]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_FLAME));

	pObject2D[1] = CObject2D::Create();			//枠UI
	pObject2D[1]->SetPos(D3DXVECTOR3(1040.0f, 440.0f, 0.0f), FRAME_UI_SCALE);
	pObject2D[1]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_FLAME));

	pObject2D[2] = CObject2D::Create();			//ランキングUI
	pObject2D[2]->SetPos(D3DXVECTOR3(240.0f, 200.0f, 0.0f), RANK_UI_SCALE);
	pObject2D[2]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_RANKING));

	pObject2D[3] = CObject2D::Create();			//今回のスコアUI
	pObject2D[3]->SetPos(D3DXVECTOR3(1040.0f, 200.0f, 0.0f), YOUR_UI_SCALE);
	pObject2D[3]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_YOURSCORE));
	
	pObject2D[4] = CObject2D::Create();			//今回のライフUI
	pObject2D[4]->SetPos(D3DXVECTOR3(110.0f, 340.0f, 0.0f), NUM_UI_SCALE);
	pObject2D[4]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_FIRST));

	pObject2D[5] = CObject2D::Create();			//今回のライフUI
	pObject2D[5]->SetPos(D3DXVECTOR3(110.0f, 440.0f, 0.0f), NUM_UI_SCALE);
	pObject2D[5]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_SECOND));

	pObject2D[6] = CObject2D::Create();			//今回のライフUI
	pObject2D[6]->SetPos(D3DXVECTOR3(110.0f, 540.0f, 0.0f), NUM_UI_SCALE);
	pObject2D[6]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_THIRD));

	int nScore = CScore::GetNum();
	CScore *pScore = CScore::Create();
	pScore->SetNum(nScore);
	pScore->SetPosOrg(SCORE_UI_SCALE);
	pObject2D[7] = pScore;

	RankSort(nScore);
	
	return S_OK;
}
//==============================================
//リザルトの終了処理
//==============================================
void CResult::Uninit(void)
{
	CObject::ReleaseAll();
}
//==============================================
//リザルトの生成処理
//==============================================
CResult *CResult::Create(void)
{
	CResult *pResult;

	//メモリ生成
	pResult = new CResult;

	if (pResult != NULL)
	{
		pResult->Init();
	}

	return pResult;
}
//==============================================
//リザルトの更新処理
//==============================================
void CResult::Update(void)
{
	//キーボードの情報を取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true)
	{//ENTERキーを押した時

		//BGM設定
		CManager::GetSound()->PlaySound(SOUND_LABEL_BUTTON);

		Uninit();

		CManager::SetMode(CScene::MODE_TITLE);
	}
}
//==============================================
//リザルトの描画処理
//==============================================
void CResult::Draw(void)
{
	if (Obj2D != NULL)
	{
		Obj2D->Draw();
	}
}
//==============================================
//リザルトのランキングソート
//==============================================
void CResult::RankSort(int nScore)
{
	int nScoreRank[4];

	bool bChange = false;

	nScoreRank[3] = nScore;

	CFile::RankingLoad("data\\FILE\\BIN\\ranking.bin",&nScoreRank[0]);

	//ソートの処理
	for (int nCount1 = 0; nCount1 < 4 - 1; nCount1++)
	{
		//並び替えをする
		for (int nCount2 = nCount1 + 1; nCount2 < 4; nCount2++)
		{
			if (nScoreRank[nCount2] > nScoreRank[nCount1])
			{
				//現在の比較している数を保存
				int nMax = nScoreRank[nCount1];

				//最大値に置き換える
				nScoreRank[nCount1] = nScoreRank[nCount2];

				//変更した数値を元に戻す
				nScoreRank[nCount2] = nMax;

				bChange = true;
			}
		}
	}

	CScore *pScore[MAX_RANKING];

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		pScore[nCnt] = CScore::Create();

		pScore[nCnt]->SetNum(nScoreRank[nCnt]);

		pScore[nCnt]->SetPosOrg(D3DXVECTOR3(170.0f, 340.0f + (nCnt * 100.0f), 0.0f));
	}

	if (bChange == true)
	{
		CFile::RankingSave("data\\FILE\\BIN\\ranking.bin", &nScoreRank[0]);
	}
}