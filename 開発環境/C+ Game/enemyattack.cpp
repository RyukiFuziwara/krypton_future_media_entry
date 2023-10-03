//==============================================
//
//敵の攻撃の攻撃(Enemyattack.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"enemyattack.h"
#include"texture.h"
#include"motion.h"
#include"player.h"
#include"object3D.h"
#include"particle.h"
#include"block.h"
#include"score.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//位置Yの初期値
#define SCALE				(4.0f)								//大きさ
#define PARTICLE_SCALE		(D3DXVECTOR3(50.0f, 50.0f, 50.0f))	//パーティクルの大きさ
#define PARTICLE_NUM		(4)									//パーティクルの数
#define MOVE				(15.0f)								//移動量
#define COLOR				(D3DXCOLOR(0.2f, 0.4f, 0.8f, 1.0f)) //色

//==============================================
//コンストラクタ
//==============================================
CEnemyattack::CEnemyattack()
{
	//初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度
	m_scale = D3DXVECTOR3(SCALE, SCALE, SCALE);
	m_bRotInit = false;
}
//==============================================
//デスストラクタ
//==============================================
CEnemyattack::~CEnemyattack()
{

}
//==============================================
//敵の攻撃の初期化処理
//==============================================
HRESULT CEnemyattack::Init(void)
{
	m_apModel = CModel::Create("data\\MODEL\\CHARACTER\\ENEMY\\slime.x");

	m_apModel->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//胴体
	m_apModel->SetParent(NULL);							//胴体

	//タイプ設定
	SetType(TYPE_ENEMY);

	return S_OK;
}
//==============================================
//敵の攻撃の終了処理
//==============================================
void CEnemyattack::Uninit(void)
{
	if (m_apModel != NULL)
	{
		m_apModel->Uninit();
	}

	//解放処理
	CObject::Release();
}
//==============================================
//敵の攻撃のメモリ生成処理
//==============================================
CEnemyattack *CEnemyattack::Create(void)
{
	CEnemyattack *pEnemyattack;	//Xobjのインスタンス生成

	//メモリ生成
	pEnemyattack = new CEnemyattack;

	if (pEnemyattack != NULL)
	{
		//初期化処理
		pEnemyattack->Init();
	}

	return pEnemyattack;
}
//==============================================
//敵の攻撃の更新処理
//==============================================
void CEnemyattack::Update(void)
{
	CObject *pObj;

	//オブジェクトの先頭を取得
	pObj = GetTop();

	while (pObj != NULL)
	{//メモリがあるとき

		//次のオブジェクトを保存しておく
		CObject *pObjectNext = pObj->GetNext();

		CObject::TYPE type;

		type = pObj->GetType();

		if (type == CObject::TYPE_PLAYER_R)
		{//オブジェクトが注視点プレイヤーのとき

			//オブジェクトをプレイヤーにキャスト
			CPlayer *pObjX = dynamic_cast<CPlayer*>(pObj);

			if (m_bRotInit == false)
			{
				m_rot.y = pObjX->GetRot().y;
				m_bRotInit = true;
			}
		
			m_move.x += sinf(m_rot.y) * MOVE;
			m_move.z += cosf(m_rot.y) * MOVE;

			m_pos.x += m_move.x;
			m_pos.z += m_move.z;

			//移動量減衰
			m_move.x += (0.0f - m_move.x) * 1.0f;
			m_move.z += (0.0f - m_move.z) * 1.0f;

			SetPos(m_pos,m_scale);
			
			break;
		}

		//次のオブジェクトにする
		pObj = pObjectNext;
	}

	if ((CObject3D::CollisionStage(m_pos)) == true 
		|| (CBlock::Collision(&m_pos, VECTOR_INIT, &m_move, m_scale, 10.0f, 10.0f, false)) == true)
	{
		for (int nCntPar = 0; nCntPar < PARTICLE_NUM; nCntPar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(m_pos, PARTICLE_SCALE);
			pParticle->SetCol(COLOR, 0.0f);
		}

		Uninit();
	}
	else if(CPlayer::Collision(&m_pos,m_scale,10.0f,10.0f)== true)
	{
		CScore::AddNum(-100);

		for (int nCntPar = 0; nCntPar < PARTICLE_NUM; nCntPar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(m_pos, PARTICLE_SCALE);
			pParticle->SetCol(COLOR, 0.0f);
		}

		Uninit();
	}
}
//==============================================
//敵の攻撃の描画処理
//==============================================
void CEnemyattack::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	CTexture *pTexture = CManager::GetTexture();
	D3DXMATRIX	 mtxRot, mtxTrans, mtxScall;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//拡縮を反映
	D3DXMatrixScaling(&mtxScall, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScall);

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
	m_apModel->Draw();
}