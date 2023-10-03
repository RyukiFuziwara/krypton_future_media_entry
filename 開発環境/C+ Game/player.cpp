//==============================================
//
//�I�u�W�F�N�gX(player.cpp)
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
//   �}�N����`   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//�ʒuY�̏����l
#define PARTICLE_INIT		(D3DXVECTOR3(10.0f,10.0f,0.0f))		//�ʒuY�̏����l
#define COLISION			(D3DXVECTOR3(10.0f,40.0f,10.0f))	//�ʒuY�̏����l
#define GRAVITY				(-0.98f)							//�d��
#define FRAME				(6)									//�t���[��(0.1�b)
#define NUM_PARTICLE		(4)									//�p�[�e�B�N����
#define NUM_RAMDOM			((float)(rand() % 10) / 10.0f))		//0.1����1.0�̃����_��
#define JUMP				(40.0f)								//�W�����v��

CPlayer::CONTROL CPlayer::m_con = CONTROL_P1;
CPlayer::CONTROL CPlayer::m_conTemp = CPlayer::m_con;
bool CPlayer::m_change = false;
bool CPlayer::m_bAction = false;
bool CPlayer::m_bDamage = false;
int CPlayer::m_nOpeCnt = 0;
//==============================================
//�R���X�g���N�^
//==============================================
CPlayer::CPlayer()
{
	//�����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 1750.0f);	//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//�p�x
	m_move = VECTOR_INIT;	//�傫��
	m_bJump = true;
	m_bmove = false;
	m_nOpeCnt = 0;
	m_nCntEfe = 0;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CPlayer::~CPlayer()
{
	m_con = CONTROL_P1;
	m_conTemp = m_con;
}
//==============================================
//�v���C���[�̏���������
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

	m_apModel[0]->SetOffSet(D3DXVECTOR3(0.0f,18.0f,0.0f));	//����
	m_apModel[1]->SetOffSet(D3DXVECTOR3(0.0f,10.0f,0.0f));	//��
	m_apModel[2]->SetOffSet(D3DXVECTOR3(-2.7f,8.7f,0.0f));	//�E�r
	m_apModel[3]->SetOffSet(D3DXVECTOR3(-6.5f,0.0f,0.0f));	//�E��
	m_apModel[4]->SetOffSet(D3DXVECTOR3(2.7f,8.7f,0.0f));	//���r
	m_apModel[5]->SetOffSet(D3DXVECTOR3(6.5f,0.0f,0.0f));	//����
	m_apModel[6]->SetOffSet(D3DXVECTOR3(-3.0f,0.0f,0.0f));	//�E��
	m_apModel[7]->SetOffSet(D3DXVECTOR3(-0.2f,-9.0f,0.0f));	//�E��
	m_apModel[8]->SetOffSet(D3DXVECTOR3(3.0f,0.0f,0.0f));	//����
	m_apModel[9]->SetOffSet(D3DXVECTOR3(0.2f,-9.0f,0.0f));	//����

	m_apModel[0]->SetParent(NULL);			//����
	m_apModel[1]->SetParent(m_apModel[0]);	//��
	m_apModel[2]->SetParent(m_apModel[0]);	//�E�r
	m_apModel[3]->SetParent(m_apModel[2]);	//�E��
	m_apModel[4]->SetParent(m_apModel[0]);	//���r
	m_apModel[5]->SetParent(m_apModel[4]);	//����
	m_apModel[6]->SetParent(m_apModel[0]);	//�E��
	m_apModel[7]->SetParent(m_apModel[6]);	//�E��
	m_apModel[8]->SetParent(m_apModel[0]);	//����
	m_apModel[9]->SetParent(m_apModel[8]);	//����

	//���[�V�����ݒ�
	pMotion = new CMotion;
	pMotion->SetModel(m_apModel,m_nNumModel);
	
	CFile::MotionLoad("data\\FILE\\TXT\\motion_miku.txt", pMotion);

	pMotion->Set(MOTIONTYPE_NEUTRAL);

	//�^�C�v�ݒ�
	SetType(TYPE_PLAYER);

	m_posTemp = m_pos;

	return S_OK;
}
//==============================================
//�v���C���[�̏I������
//==============================================
void CPlayer::Uninit(void)
{
	//�������J��
	delete pMotion;
	pMotion = NULL;

	//�I������
	for (int nCntParts = 0; nCntParts < PLAYER_MODEL_PARTS; nCntParts++)
	{
		m_apModel[nCntParts]->Uninit();
	}

	//�������
	CObject::Release();
}
//==============================================
//�v���C���[�̃�������������
//==============================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pplayer;	//Xobj�̃C���X�^���X����

	//����������
	pplayer = new CPlayer;

	if (pplayer != NULL)
	{
		//����������
		pplayer->Init();
	}

	return pplayer;
}
//==============================================
//�v���C���[�̍X�V����
//==============================================
void CPlayer::Update(void)
{
	//�s������
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

	//�d��
	m_move.y += GRAVITY;

	//�ړ��ʑ��
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//�n��
	if (m_pos.y <= 0.0f)
	{
		m_bJump = true;
		m_pos.y = 0.0f;
	}

	//�ړ��ʌ���
	m_move.x += (0.0f - m_move.x) * 1.0f;
	m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 1.0f;

	//���[�V�����X�V����
	pMotion->Update();

	//���[�V�����ݒ�
	if (pMotion->GetTypeTemp() == MOTIONTYPE_JUMP && pMotion->IsFinish() == true)
	{
		pMotion->Set(MOTIONTYPE_LAND);
	}
	else if (MotionType == MOTIONTYPE_NEUTRAL)
	{//�ҋ@
		pMotion->Set(MOTIONTYPE_NEUTRAL);
	}
	else if(MotionType == MOTIONTYPE_MOVE)
	{//����
		pMotion->Set(MOTIONTYPE_MOVE);

		m_nCntEfe++;

		if (m_nCntEfe >= FRAME)
		{
			//�G�t�F�N�g�̐���
			CEffect *pEffect;
			pEffect = CEffect::Create();
			pEffect->SetPos(m_pos, SCALE_INIT);
			pEffect->SetCol(D3DXCOLOR(0.4f, 0.2f, 0.0f, 0.0f), 0.0f);

			m_nCntEfe = 0;
		}
	}
	else if (MotionType == MOTIONTYPE_JUMP)
	{//�W�����v
		pMotion->Set(MOTIONTYPE_JUMP);
	}
}
//==============================================
//�v���C���[�̕`�揈��
//==============================================
void CPlayer::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	D3DXMATRIX	 mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�`�揈��
	for (int nCntParts = 0; nCntParts < PLAYER_MODEL_PARTS; nCntParts++)
	{
		m_apModel[nCntParts]->Draw();
	}
}
//==============================================
//�v���C���[�̍s������
//==============================================
void CPlayer::Action(void)
{
	//�L�[�{�[�h�E�L�[�p�b�h�̏����擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (GetType() == TYPE_PLAYER_R || m_con == CONTROL_ALL)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyPad->GetPress(CInputKeyPad::JOYKEY_LEFT) == true)
		{//A�L�[����������

			MotionType = MOTIONTYPE_MOVE;
			m_apModel[0]->SetDirection(-1.57f);

			m_rot.y += (1.0f / (m_posTemp.z * 0.1f));

			//�E�ɐi��
			m_move.x += sinf((D3DX_PI * 0.5f) + m_rot.y) * 10;
			m_move.z += cosf((D3DX_PI * 0.5f) + m_rot.y) * 10;

			if (m_rot.y >= 3.14f)
			{
				m_rot.y = -3.14f;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true || pInputKeyPad->GetPress(CInputKeyPad::JOYKEY_RIGHT) == true)
		{//D�L�[����������

			MotionType = MOTIONTYPE_MOVE;
			m_apModel[0]->SetDirection(1.57f);

			m_rot.y -= (1.0f / (m_posTemp.z * 0.1f));

			//���ɐi��
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
			//�e����
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_B) == true)
			{//�X�y�[�X�L�[����������

				if (CBlock::Collision(&m_pos, VECTOR_INIT, &m_move, m_scale, 80.0f, COLISION.y, true) == true)
				{
					//BGM�ݒ�
					CManager::GetSound()->PlaySound(SOUND_LABEL_ATTACK);

					m_bAction = true;
				}
			}

			//�W�����v
			if (pInputKeyboard->GetTrigger(DIK_UPARROW) == true && m_bJump == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true && m_bJump == true)
			{//J�L�[����������

				//BGM�ݒ�
				CManager::GetSound()->PlaySound(SOUND_LABEL_JUMP);

				m_bAction = true;
				m_bJump = false;
				m_move.y += JUMP;
				MotionType = MOTIONTYPE_JUMP;
			}
		}

		if (GetType() == TYPE_PLAYER_R)
		{
			//�v���C���[�؂�ւ�
			if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_LEFT_SHOULDER) == true)
			{//Q�L�[����������

				m_con = CONTROL_P1;
			}
			else if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_RIGHT_SHOULDER) == true)
			{//W�L�[����������

				m_con = CONTROL_P2;
			}
			else if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_Y) == true)
			{//E�L�[����������

				m_con = CONTROL_ALL;
			}
		}
	}
}
//==============================================
//�v���C���[�̓����蔻�菈��
//==============================================
bool CPlayer::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 scale, float fWidth, float fHeight)
{
	CObject *pObj;

	//�I�u�W�F�N�g�̐擪���擾
	pObj = CObject::GetTop();

	while (pObj != NULL)
	{//������������Ƃ�

		//���̃I�u�W�F�N�g��ۑ����Ă���
		CObject *pObjectNext = pObj->GetNext();

		TYPE typeObj;

		typeObj = pObj->GetType();

		if (typeObj == TYPE_PLAYER || typeObj == TYPE_PLAYER_R)
		{//�I�u�W�F�N�g���u���b�N�̂Ƃ�

			//�I�u�W�F�N�g���v���C���[�ɃL���X�g
			CPlayer *pPlayer = dynamic_cast<CPlayer*>(pObj);

			if (pPos->x + (scale.x * fWidth) >= pPlayer->GetPos().x - pPlayer->GetScale().x * COLISION.x
				&& pPos->x - (scale.x * fWidth) <= pPlayer->GetPos().x + pPlayer->GetScale().x * COLISION.x
				&& pPos->y + (scale.y * fHeight) >= pPlayer->GetPos().y - pPlayer->GetScale().y * COLISION.y
				&& pPos->y - (scale.y * fHeight) <= pPlayer->GetPos().y + pPlayer->GetScale().y * COLISION.y
				&& pPos->z + (scale.z * fHeight) >= pPlayer->GetPos().z - pPlayer->GetScale().z * COLISION.z
				&& pPos->z - (scale.z * fHeight) <= pPlayer->GetPos().z + pPlayer->GetScale().z * COLISION.z)
			{//�u���b�N�͈͓̔�

				m_bDamage = true;

				//BGM�ݒ�
				CManager::GetSound()->PlaySound(SOUND_LABEL_HIT);

				return true;
			}
		}

		//���̃I�u�W�F�N�g�ɂ���
		pObj = pObjectNext;
	}

	return false;
}