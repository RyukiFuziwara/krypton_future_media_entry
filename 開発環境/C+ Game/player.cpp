//==============================================
//
//オブジェクトX(player.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"player.h"
#include"texture.h"
#include"motion.h"
#include"effect.h"
#include"file.h"
#include"score.h"
#include"block.h"
#include"sound.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//位置Yの初期値
#define PARTICLE_INIT		(D3DXVECTOR3(10.0f,10.0f,0.0f))		//位置Yの初期値
#define COLISION			(D3DXVECTOR3(10.0f,40.0f,10.0f))	//位置Yの初期値
#define GRAVITY				(-0.98f)							//重力
#define FRAME				(6)									//フレーム(0.1秒)
#define NUM_PARTICLE		(4)									//パーティクル数
#define NUM_RAMDOM			((float)(rand() % 10) / 10.0f))		//0.1から1.0のランダム
#define JUMP				(40.0f)								//ジャンプ量

CPlayer::CONTROL CPlayer::m_con = CONTROL_P1;
CPlayer::CONTROL CPlayer::m_conTemp = CPlayer::m_con;
bool CPlayer::m_change = false;
bool CPlayer::m_bAction = false;
bool CPlayer::m_bDamage = false;
int CPlayer::m_nOpeCnt = 0;
//==============================================
//コンストラクタ
//==============================================
CPlayer::CPlayer()
{
	//初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 1750.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//角度
	m_move = VECTOR_INIT;	//大きさ
	m_bJump = true;
	m_bmove = false;
	m_nOpeCnt = 0;
	m_nCntEfe = 0;
}
//==============================================
//デスストラクタ
//==============================================
CPlayer::~CPlayer()
{
	m_con = CONTROL_P1;
	m_conTemp = m_con;
}
//==============================================
//プレイヤーの初期化処理
//==============================================
HRESULT CPlayer::Init(void)
{
	const char *pFileName[] =
	{
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_body.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_head.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_RightArm.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_RightHand.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_LeftArm.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_LeftHand.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_RightThigh.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_RightLeg.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_LeftThigh.x",
		"data\\MODEL\\CHARACTER\\PLAYER\\MIKU\\miku_LeftLeg.x"
	};

	for (int nCntParts = 0; nCntParts < PLAYER_MODEL_PARTS; nCntParts++,m_nNumModel++)
	{
		m_apModel[nCntParts] = CModel::Create(pFileName[nCntParts]);
	}

	m_apModel[0]->SetOffSet(D3DXVECTOR3(0.0f,18.0f,0.0f));	//胴体
	m_apModel[1]->SetOffSet(D3DXVECTOR3(0.0f,10.0f,0.0f));	//頭
	m_apModel[2]->SetOffSet(D3DXVECTOR3(-2.7f,8.7f,0.0f));	//右腕
	m_apModel[3]->SetOffSet(D3DXVECTOR3(-6.5f,0.0f,0.0f));	//右手
	m_apModel[4]->SetOffSet(D3DXVECTOR3(2.7f,8.7f,0.0f));	//左腕
	m_apModel[5]->SetOffSet(D3DXVECTOR3(6.5f,0.0f,0.0f));	//左手
	m_apModel[6]->SetOffSet(D3DXVECTOR3(-3.0f,0.0f,0.0f));	//右脛
	m_apModel[7]->SetOffSet(D3DXVECTOR3(-0.2f,-9.0f,0.0f));	//右足
	m_apModel[8]->SetOffSet(D3DXVECTOR3(3.0f,0.0f,0.0f));	//左脛
	m_apModel[9]->SetOffSet(D3DXVECTOR3(0.2f,-9.0f,0.0f));	//左足

	m_apModel[0]->SetParent(NULL);			//胴体
	m_apModel[1]->SetParent(m_apModel[0]);	//頭
	m_apModel[2]->SetParent(m_apModel[0]);	//右腕
	m_apModel[3]->SetParent(m_apModel[2]);	//右手
	m_apModel[4]->SetParent(m_apModel[0]);	//左腕
	m_apModel[5]->SetParent(m_apModel[4]);	//左手
	m_apModel[6]->SetParent(m_apModel[0]);	//右脛
	m_apModel[7]->SetParent(m_apModel[6]);	//右足
	m_apModel[8]->SetParent(m_apModel[0]);	//左脛
	m_apModel[9]->SetParent(m_apModel[8]);	//左足

	//モーション設定
	pMotion = new CMotion;
	pMotion->SetModel(m_apModel,m_nNumModel);
	
	CFile::MotionLoad("data\\FILE\\TXT\\motion_miku.txt", pMotion);

	pMotion->Set(MOTIONTYPE_NEUTRAL);

	//タイプ設定
	SetType(TYPE_PLAYER);

	m_posTemp = m_pos;

	return S_OK;
}
//==============================================
//プレイヤーの終了処理
//==============================================
void CPlayer::Uninit(void)
{
	//メモリ開放
	delete pMotion;
	pMotion = NULL;

	//終了処理
	for (int nCntParts = 0; nCntParts < PLAYER_MODEL_PARTS; nCntParts++)
	{
		m_apModel[nCntParts]->Uninit();
	}

	//解放処理
	CObject::Release();
}
//==============================================
//プレイヤーのメモリ生成処理
//==============================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pplayer;	//Xobjのインスタンス生成

	//メモリ生成
	pplayer = new CPlayer;

	if (pplayer != NULL)
	{
		//初期化処理
		pplayer->Init();
	}

	return pplayer;
}
//==============================================
//プレイヤーの更新処理
//==============================================
void CPlayer::Update(void)
{
	//行動処理
	Action();

	if (m_con != m_conTemp)
	{
		m_nOpeCnt = 0;

		if (m_con == CONTROL_P2 || m_con != CONTROL_P2 && m_conTemp == CONTROL_P2)
		{
			if (GetType() == TYPE_PLAYER_R)
			{
				SetType(TYPE_PLAYER);
			}
			else if (GetType() == TYPE_PLAYER)
			{
				SetType(TYPE_PLAYER_R);
			}

			m_change = true;
		}
	}
	else
	{
		m_nOpeCnt++;
	}

	if (GetType() == TYPE_PLAYER_R)
	{
		m_conTemp = m_con;
	}

	//重力
	m_move.y += GRAVITY;

	//移動量代入
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//地面
	if (m_pos.y <= 0.0f)
	{
		m_bJump = true;
		m_pos.y = 0.0f;
	}

	//移動量減衰
	m_move.x += (0.0f - m_move.x) * 1.0f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 1.0f;

	//モーション更新処理
	pMotion->Update();

	//モーション設定
	if (pMotion->GetTypeTemp() == MOTIONTYPE_JUMP && pMotion->IsFinish() == true)
	{
		pMotion->Set(MOTIONTYPE_LAND);
	}
	else if (MotionType == MOTIONTYPE_NEUTRAL)
	{//待機
		pMotion->Set(MOTIONTYPE_NEUTRAL);
	}
	else if(MotionType == MOTIONTYPE_MOVE)
	{//走り
		pMotion->Set(MOTIONTYPE_MOVE);

		m_nCntEfe++;

		if (m_nCntEfe >= FRAME)
		{
			//エフェクトの生成
			CEffect *pEffect;
			pEffect = CEffect::Create();
			pEffect->SetPos(m_pos, SCALE_INIT);
			pEffect->SetCol(D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.0f), 0.0f);

			m_nCntEfe = 0;
		}
	}
	else if (MotionType == MOTIONTYPE_JUMP)
	{//ジャンプ
		pMotion->Set(MOTIONTYPE_JUMP);
	}
}
//==============================================
//プレイヤーの描画処理
//==============================================
void CPlayer::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	D3DXMATRIX	 mtxRot, mtxTrans;		//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

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
	for (int nCntParts = 0; nCntParts < PLAYER_MODEL_PARTS; nCntParts++)
	{
		m_apModel[nCntParts]->Draw();
	}
}
//==============================================
//プレイヤーの行動処理
//==============================================
void CPlayer::Action(void)
{
	//キーボード・キーパッドの情報を取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (GetType() == TYPE_PLAYER_R || m_con == CONTROL_ALL)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyPad->GetPress(CInputKeyPad::JOYKEY_LEFT) == true)
		{//Aキーを押した時

			MotionType = MOTIONTYPE_MOVE;
			m_apModel[0]->SetDirection(-1.57f);

			m_rot.y += (1.0f / (m_posTemp.z * 0.1f));

			//右に進む
			m_move.x += sinf((D3DX_PI * 0.5f) + m_rot.y) * 10;
			m_move.z += cosf((D3DX_PI * 0.5f) + m_rot.y) * 10;

			if (m_rot.y >= 3.14f)
			{
				m_rot.y = -3.14f;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyPad->GetPress(CInputKeyPad::JOYKEY_RIGHT) == true)
		{//Dキーを押した時

			MotionType = MOTIONTYPE_MOVE;
			m_apModel[0]->SetDirection(1.57f);

			m_rot.y -= (1.0f / (m_posTemp.z * 0.1f));

			//左に進む
			m_move.x -= sinf((D3DX_PI * 0.5f) + m_rot.y) * 10;
			m_move.z -= cosf((D3DX_PI * 0.5f) + m_rot.y) * 10;

			if (m_rot.y <= -3.14f)
			{
				m_rot.y = 3.14f;
			}
		}
		else
		{
			MotionType = MOTIONTYPE_NEUTRAL;
			m_apModel[0]->SetDirection(0.0f);
		}

		if ((CActiongauge::GetGauge() + ACTION_COST) > 0)
		{
			//弾発射
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_B) == true)
			{//スペースキーを押した時

				if (CBlock::Collision(&m_pos, VECTOR_INIT, &m_move, m_scale, 80.0f, COLISION.y, true) == true)
				{
					//BGM設定
					CManager::GetSound()->PlaySound(SOUND_LABEL_ATTACK);

					m_bAction = true;
				}
			}

			//ジャンプ
			if (pInputKeyboard->GetTrigger(DIK_UPARROW) == true && m_bJump == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true && m_bJump == true)
			{//Jキーを押した時

				//BGM設定
				CManager::GetSound()->PlaySound(SOUND_LABEL_JUMP);

				m_bAction = true;
				m_bJump = false;
				m_move.y += JUMP;
				MotionType = MOTIONTYPE_JUMP;
			}
		}

		if (GetType() == TYPE_PLAYER_R)
		{
			//プレイヤー切り替え
			if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_LEFT_SHOULDER) == true)
			{//Qキーを押した時

				m_con = CONTROL_P1;
			}
			else if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_RIGHT_SHOULDER) == true)
			{//Wキーを押した時

				m_con = CONTROL_P2;
			}
			else if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_Y) == true)
			{//Eキーを押した時

				m_con = CONTROL_ALL;
			}
		}
	}
}
//==============================================
//プレイヤーの当たり判定処理
//==============================================
bool CPlayer::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 scale, float fWidth, float fHeight)
{
	CObject *pObj;

	//オブジェクトの先頭を取得
	pObj = CObject::GetTop();

	while (pObj != NULL)
	{//メモリがあるとき

		//次のオブジェクトを保存しておく
		CObject *pObjectNext = pObj->GetNext();

		TYPE typeObj;

		typeObj = pObj->GetType();

		if (typeObj == TYPE_PLAYER || typeObj == TYPE_PLAYER_R)
		{//オブジェクトがブロックのとき

			//オブジェクトをプレイヤーにキャスト
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pObj);

			if (pPos->x + (scale.x * fWidth) >= pPlayer->GetPos().x - pPlayer->GetScale().x * COLISION.x
				&& pPos->x - (scale.x * fWidth) <= pPlayer->GetPos().x + pPlayer->GetScale().x * COLISION.x
				&& pPos->y + (scale.y * fHeight) >= pPlayer->GetPos().y - pPlayer->GetScale().y * COLISION.y
				&& pPos->y - (scale.y * fHeight) <= pPlayer->GetPos().y + pPlayer->GetScale().y * COLISION.y
				&& pPos->z + (scale.z * fHeight) >= pPlayer->GetPos().z - pPlayer->GetScale().z * COLISION.z
				&& pPos->z - (scale.z * fHeight) <= pPlayer->GetPos().z + pPlayer->GetScale().z * COLISION.z)
			{//ブロックの範囲内

				m_bDamage = true;

				//BGM設定
				CManager::GetSound()->PlaySound(SOUND_LABEL_HIT);

				return true;
			}
		}

		//次のオブジェクトにする
		pObj = pObjectNext;
	}

	return false;
}