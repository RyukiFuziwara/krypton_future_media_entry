//==============================================
//
//オブジェクトX(enemy.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"enemy.h"
#include"player.h"
#include"enemyattack.h"
#include"particle.h"
#include"texture.h"
#include"motion.h"
#include"score.h"
#include"time.h"
#include"file.h"
#include"rock.h"
#include"sound.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))	//位置Yの初期値
#define SCALE				(40.0f)							//大きさ
#define ATTACK_COUNT		(30)							//攻撃間隔
#define LIFE				(6)								//体力
#define PARTICLE_POS_HEIGHT	(D3DXVECTOR3(0.0f,200.0f,0.0f))	//パーティクル高さ補正
#define MAX_HEIGHT			(5.0f)							//高さ
#define MAX_WIDTH			(5.0f)							//幅
#define ATTACK_SCALE		(D3DXVECTOR3(4.0f, 4.0f, 4.0f))	//攻撃の大きさ
#define PARTICLE_NUM		(4)								//パーティクルの数
#define ROCK_SCALE_ONE		(D3DXVECTOR3(0.5f,0.5f,0.5f))	//岩の大きさ１
#define ROCK_SCALE_TWO		(D3DXVECTOR3(1.0f,1.0f,1.0f))	//岩の大きさ２
#define ULT_STACK_ONE		(1)								//必殺の発動タイミング１
#define ULT_STACK_TWO		(5)								//必殺の発動タイミング２
#define ULT_STACK_THREE		(10)							//必殺の発動タイミング３
#define ULT_STACK_FOUR		(15)							//必殺の発動タイミング４
#define ULT_NUM_THREE		(117)							//必殺３の数
#define ULT_NUM_FOUR		(39)							//必殺４の数


//静的メンバ変数宣言
CLife *CEnemy::m_pLife = NULL;
int CEnemy::m_Form = NULL;
//==============================================
//コンストラクタ
//==============================================
CEnemy::CEnemy()
{
	//初期設定
	m_pos = VECTOR_INIT;						//位置
	m_rot = VECTOR_INIT;						//角度
	m_scale = D3DXVECTOR3(SCALE, SCALE, SCALE);	//大きさ
	m_nAttackCount = ATTACK_COUNT;				//攻撃間隔
	m_UltStack = 1;								//必殺スタック
	m_nNum = -1;								//ボス数
	m_Form = BOSS_FORM_ONE;						//ボス形態
	m_bDefeat = false;							//撃破フラグ
}
//==============================================
//デスストラクタ
//==============================================
CEnemy::~CEnemy()
{

}
//==============================================
//敵の初期化処理
//==============================================
HRESULT CEnemy::Init(void)
{
	for (int nCntParts = 0; nCntParts < ENEMY_MODEL_PARTS; nCntParts++, m_nNumModel++,m_nNum++)
	{
		if (nCntParts == 0)
		{
			m_apModel[nCntParts] = CModel::Create("data\\MODEL\\CHARACTER\\ENEMY\\slime_boss.x");
		}
		else
		{
			m_apModel[nCntParts] = CModel::Create("data\\MODEL\\CHARACTER\\ENEMY\\slime.x");
		}
	}

	//オフセット
	m_apModel[0]->SetOffSet(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//頭(下)
	m_apModel[1]->SetOffSet(D3DXVECTOR3(0.0f, 10.0f, 0.0f));	//頭(中)
	m_apModel[2]->SetOffSet(D3DXVECTOR3(0.0f, 10.0f, 0.0f));	//頭(上)

	//親子関係
	m_apModel[0]->SetParent(NULL);			//胴体
	m_apModel[1]->SetParent(m_apModel[0]);	//頭
	m_apModel[2]->SetParent(m_apModel[1]);	//右腕

	//タイプ設定
	SetType(TYPE_ENEMY_BOSS);

	//モーション設定
	pMotion = new CMotion;
	pMotion->SetModel(m_apModel, m_nNumModel);
	CFile::MotionLoad("data\\FILE\\TXT\\motion_slime.txt", pMotion);
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	//ライフ生成
	m_pLife = CLife::Create();
	m_pLife->Set(LIFE);
	m_nLifeTemp = LIFE;

	return S_OK;
}
//==============================================
//敵の終了処理
//==============================================
void CEnemy::Uninit(void)
{
	//メモリ開放
	delete pMotion;
	pMotion = NULL;

	for (int nCntNum = 0; nCntNum < ENEMY_MODEL_PARTS; nCntNum++)
	{
		m_apModel[nCntNum]->Uninit();
	}

	//解放処理
	CObject::Release();
}
//==============================================
//敵のメモリ生成処理
//==============================================
CEnemy *CEnemy::Create(void)
{
	CEnemy *penemy;	//Xobjのインスタンス生成

	//メモリ生成
	penemy = new CEnemy;

	if (penemy != NULL)
	{
		//初期化処理
		penemy->Init();
	}

	return penemy;
}
//==============================================
//敵の更新処理
//==============================================
void CEnemy::Update(void)
{
	if (pMotion != NULL)
	{
		//モーション更新処理
		pMotion->Update();
	}

	//攻撃処理
	Attack();

	//重力
	m_movey -= 0.098f;
	m_apModel[0]->AddPos(D3DXVECTOR3(0.0f,m_movey,0.0f));
	m_movey += (0.0f - m_movey) * 0.1f;

	if (m_apModel[0]->GetPos().y <= 0.0f)
	{
		m_apModel[0]->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	if (pMotion->GetType() == MOTIONTYPE_MOVE && pMotion->IsFinish() == true)
	{
		pMotion->Set(MOTIONTYPE_NEUTRAL);
	}

	//体力管理
	if ((m_pLife->Get() % 2) == 0 && m_nLifeTemp != m_pLife->Get())
	{
		//BGM設定
		CManager::GetSound()->PlaySound(SOUND_LABEL_ENEMYDEST);

		//撃破処理
		Defeat();
		m_nLifeTemp = m_pLife->Get();
	}
}
//==============================================
//敵の描画処理
//==============================================
void CEnemy::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	CTexture *pTexture = CManager::GetTexture();
	D3DXMATRIX	 mtxRot, mtxTrans,mtxScall;			//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//拡縮を反映
	D3DXMatrixScaling(&mtxScall, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxScall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//描画処理
	for (int nCntParts = 0; nCntParts < m_nNum + 1; nCntParts++)
	{
		m_apModel[nCntParts]->Draw();
	}
}
//==============================================
//敵の攻撃処理
//==============================================
void CEnemy::Attack(void)
{
	//オブジェクトの先頭を取得
	CObject *pObj = CObject::GetTop();;

	while (pObj != NULL)
	{//メモリがあるとき

		//次のオブジェクトを保存しておく
		CObject *pObjectNext = pObj->GetNext();

		CObject::TYPE type = pObj->GetType();;

		if (type == CObject::TYPE_PLAYER_R)
		{//オブジェクトが注視点プレイヤーのとき

			//オブジェクトをプレイヤーにキャスト
			CPlayer *pObjX = dynamic_cast<CPlayer*>(pObj);

			//プレイヤーの向きを取得
			m_rot.y = pObjX->GetRot().y;
		}

		//次のオブジェクトにする
		pObj = pObjectNext;
	}

	//攻撃カウントダウン
	m_nAttackCount--;

	if (m_nAttackCount == 0)
	{//攻撃タイミング

		//必殺スタック
		m_UltStack++;

		//敵生成
		CEnemyattack *Enemyattack;
		Enemyattack = CEnemyattack::Create();
		Enemyattack->SetPos(m_pos,ATTACK_SCALE);

		if ((m_UltStack % ULT_STACK_ONE) == 0)
		{//通常必殺

			if (m_Form >= BOSS_FORM_THREE)
			{
				CRock *pRock;
				pRock = CRock::Create();
				pRock->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), ROCK_SCALE_ONE);
			}

			for (int nCntRock = 0; nCntRock < PARTICLE_NUM; nCntRock++)
			{
				CRock *pRock;
				pRock = CRock::Create();
				pRock->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), ROCK_SCALE_ONE);
				pRock->SetRot(D3DXVECTOR3(pRock->GetRot().x, (float)(rand() % 629 - 314) / 100.0f, 0.0f));
			}
		}

		if ((m_UltStack % ULT_STACK_THREE) == 0)
		{//必殺(輪)

			if (m_Form >= BOSS_FORM_TWO)
			{
				//BGM設定
				CManager::GetSound()->PlaySound(SOUND_LABEL_ENEMYULT);

				pMotion->Set(MOTIONTYPE_MOVE);

				for (int nCntRock = 0; nCntRock < ULT_NUM_THREE; nCntRock++)
				{
					CRock *pRock;
					pRock = CRock::Create();
					pRock->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), ROCK_SCALE_ONE);
				}
			}
		}

		if ((m_UltStack % ULT_STACK_FOUR) == 0)
		{//必殺(輪)

			//BGM設定
			CManager::GetSound()->PlaySound(SOUND_LABEL_ENEMYULT);

			pMotion->Set(MOTIONTYPE_MOVE);

			for (int nCntRock = 0; nCntRock < ULT_NUM_FOUR; nCntRock++)
			{
				CRock *pRock;
				pRock = CRock::Create();
				pRock->SetPos(D3DXVECTOR3(m_pos.x,150.0f,m_pos.z), ROCK_SCALE_TWO);
			}

			m_UltStack = 0;
		}

		//攻撃カウント設定
		m_nAttackCount = ATTACK_COUNT;
	}
	else if ((m_nAttackCount % ULT_STACK_TWO) == 0)
	{
		if (m_Form >= BOSS_FORM_THREE)
		{
			CRock *pRock;
			pRock = CRock::Create();
			pRock->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), ROCK_SCALE_ONE);
		}
	}

}
//==============================================
//敵の撃破処理
//==============================================
void CEnemy::Defeat(void)
{
	CScore::AddNum(200 * CTime::GetNum());

	m_Form++;

 	if (m_nNum > 0)
	{
		for (int nCntNum = 1; nCntNum < m_nNum; nCntNum++)
		{
			m_apModel[nCntNum]->SetParent(m_apModel[nCntNum - 1]);
		}

		for (int nCntPar = 0; nCntPar < PARTICLE_NUM * 3; nCntPar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(m_pos + PARTICLE_POS_HEIGHT, D3DXVECTOR3(300.0f, 300.0f, 300.0f));
			pParticle->SetCol(D3DXCOLOR(0.4f, 0.4f, 0.2f, 1.0f), 0.0f);
			pParticle->SetAddMove(40.0f);
		}

		pMotion->SetModel(m_apModel, --m_nNumModel);

		m_apModel[0]->SetOffSet(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_bDefeat = true;
	}	

	m_nNum--;

	if (m_nNum == -1)
	{
		for (int nCntPar = 0; nCntPar < PARTICLE_NUM * 5; nCntPar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(m_pos + PARTICLE_POS_HEIGHT, D3DXVECTOR3(400.0f, 400.0f, 400.0f));
			pParticle->SetCol(D3DXCOLOR(0.4f, 0.4f, 0.8f, 1.0f), 0.0f);
			pParticle->SetAddMove(40.0f);
		}

		Uninit();
	}
}
//==============================================
//敵の当たり判定処理
//==============================================
bool CEnemy::Collision(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pMove, D3DXVECTOR3 scale, float fWidth, float fHeight)
{
	CObject *pObj;

	//オブジェクトの先頭を取得
	pObj = CObject::GetTop();

	while (pObj != NULL)
	{//メモリがあるとき

	 //次のオブジェクトを保存しておく
		CObject *pObjectNext = pObj->GetNext();

		TYPE typObje;

		typObje = pObj->GetType();

		if (typObje == TYPE_ENEMY_BOSS)
		{//オブジェクトが敵のとき

		 //オブジェクトを敵にキャスト
			CEnemy *pObjenemy = dynamic_cast<CEnemy*>(pObj);

			if (pPos->x + (scale.x * fWidth) >= pObjenemy->GetPos().x + sinf(pObjenemy->GetRot().y) - (pObjenemy->GetScale().x * MAX_WIDTH)
				&& pPos->x - (scale.x * fWidth) <= pObjenemy->GetPos().x + sinf(pObjenemy->GetRot().y) + (pObjenemy->GetScale().x * MAX_WIDTH)
				&& pPos->z + (scale.z * fHeight) >= pObjenemy->GetPos().z + cosf(pObjenemy->GetRot().y) - (pObjenemy->GetScale().z * MAX_HEIGHT)
				&& pPos->z - (scale.z * fHeight) <= pObjenemy->GetPos().z + cosf(pObjenemy->GetRot().y) + (pObjenemy->GetScale().z * MAX_HEIGHT))
			{//敵の範囲内

				//BGM設定
				CManager::GetSound()->PlaySound(SOUND_LABEL_ENEMYHIT);

				m_pLife->Sub(-1);

				return true;
			}
		}

		pObj = pObjectNext;
	}

	return false;
}