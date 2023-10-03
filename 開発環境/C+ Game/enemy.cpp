//==============================================
//
//�I�u�W�F�N�gX(enemy.cpp)
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
//   �}�N����`   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))	//�ʒuY�̏����l
#define SCALE				(40.0f)							//�傫��
#define ATTACK_COUNT		(30)							//�U���Ԋu
#define LIFE				(6)								//�̗�
#define PARTICLE_POS_HEIGHT	(D3DXVECTOR3(0.0f,200.0f,0.0f))	//�p�[�e�B�N�������␳
#define MAX_HEIGHT			(5.0f)							//����
#define MAX_WIDTH			(5.0f)							//��
#define ATTACK_SCALE		(D3DXVECTOR3(4.0f, 4.0f, 4.0f))	//�U���̑傫��
#define PARTICLE_NUM		(4)								//�p�[�e�B�N���̐�
#define ROCK_SCALE_ONE		(D3DXVECTOR3(0.5f,0.5f,0.5f))	//��̑傫���P
#define ROCK_SCALE_TWO		(D3DXVECTOR3(1.0f,1.0f,1.0f))	//��̑傫���Q
#define ULT_STACK_ONE		(1)								//�K�E�̔����^�C�~���O�P
#define ULT_STACK_TWO		(5)								//�K�E�̔����^�C�~���O�Q
#define ULT_STACK_THREE		(10)							//�K�E�̔����^�C�~���O�R
#define ULT_STACK_FOUR		(15)							//�K�E�̔����^�C�~���O�S
#define ULT_NUM_THREE		(117)							//�K�E�R�̐�
#define ULT_NUM_FOUR		(39)							//�K�E�S�̐�


//�ÓI�����o�ϐ��錾
CLife *CEnemy::m_pLife = NULL;
int CEnemy::m_Form = NULL;
//==============================================
//�R���X�g���N�^
//==============================================
CEnemy::CEnemy()
{
	//�����ݒ�
	m_pos = VECTOR_INIT;						//�ʒu
	m_rot = VECTOR_INIT;						//�p�x
	m_scale = D3DXVECTOR3(SCALE, SCALE, SCALE);	//�傫��
	m_nAttackCount = ATTACK_COUNT;				//�U���Ԋu
	m_UltStack = 1;								//�K�E�X�^�b�N
	m_nNum = -1;								//�{�X��
	m_Form = BOSS_FORM_ONE;						//�{�X�`��
	m_bDefeat = false;							//���j�t���O
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CEnemy::~CEnemy()
{

}
//==============================================
//�G�̏���������
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

	//�I�t�Z�b�g
	m_apModel[0]->SetOffSet(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//��(��)
	m_apModel[1]->SetOffSet(D3DXVECTOR3(0.0f, 10.0f, 0.0f));	//��(��)
	m_apModel[2]->SetOffSet(D3DXVECTOR3(0.0f, 10.0f, 0.0f));	//��(��)

	//�e�q�֌W
	m_apModel[0]->SetParent(NULL);			//����
	m_apModel[1]->SetParent(m_apModel[0]);	//��
	m_apModel[2]->SetParent(m_apModel[1]);	//�E�r

	//�^�C�v�ݒ�
	SetType(TYPE_ENEMY_BOSS);

	//���[�V�����ݒ�
	pMotion = new CMotion;
	pMotion->SetModel(m_apModel, m_nNumModel);
	CFile::MotionLoad("data\\FILE\\TXT\\motion_slime.txt", pMotion);
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	//���C�t����
	m_pLife = CLife::Create();
	m_pLife->Set(LIFE);
	m_nLifeTemp = LIFE;

	return S_OK;
}
//==============================================
//�G�̏I������
//==============================================
void CEnemy::Uninit(void)
{
	//�������J��
	delete pMotion;
	pMotion = NULL;

	for (int nCntNum = 0; nCntNum < ENEMY_MODEL_PARTS; nCntNum++)
	{
		m_apModel[nCntNum]->Uninit();
	}

	//�������
	CObject::Release();
}
//==============================================
//�G�̃�������������
//==============================================
CEnemy *CEnemy::Create(void)
{
	CEnemy *penemy;	//Xobj�̃C���X�^���X����

	//����������
	penemy = new CEnemy;

	if (penemy != NULL)
	{
		//����������
		penemy->Init();
	}

	return penemy;
}
//==============================================
//�G�̍X�V����
//==============================================
void CEnemy::Update(void)
{
	if (pMotion != NULL)
	{
		//���[�V�����X�V����
		pMotion->Update();
	}

	//�U������
	Attack();

	//�d��
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

	//�̗͊Ǘ�
	if ((m_pLife->Get() % 2) == 0 && m_nLifeTemp != m_pLife->Get())
	{
		//BGM�ݒ�
		CManager::GetSound()->PlaySound(SOUND_LABEL_ENEMYDEST);

		//���j����
		Defeat();
		m_nLifeTemp = m_pLife->Get();
	}
}
//==============================================
//�G�̕`�揈��
//==============================================
void CEnemy::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	CTexture *pTexture = CManager::GetTexture();
	D3DXMATRIX	 mtxRot, mtxTrans,mtxScall;			//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�g�k�𔽉f
	D3DXMatrixScaling(&mtxScall, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxScall);

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
	for (int nCntParts = 0; nCntParts < m_nNum + 1; nCntParts++)
	{
		m_apModel[nCntParts]->Draw();
	}
}
//==============================================
//�G�̍U������
//==============================================
void CEnemy::Attack(void)
{
	//�I�u�W�F�N�g�̐擪���擾
	CObject *pObj = CObject::GetTop();;

	while (pObj != NULL)
	{//������������Ƃ�

		//���̃I�u�W�F�N�g��ۑ����Ă���
		CObject *pObjectNext = pObj->GetNext();

		CObject::TYPE type = pObj->GetType();;

		if (type == CObject::TYPE_PLAYER_R)
		{//�I�u�W�F�N�g�������_�v���C���[�̂Ƃ�

			//�I�u�W�F�N�g���v���C���[�ɃL���X�g
			CPlayer *pObjX = dynamic_cast<CPlayer*>(pObj);

			//�v���C���[�̌������擾
			m_rot.y = pObjX->GetRot().y;
		}

		//���̃I�u�W�F�N�g�ɂ���
		pObj = pObjectNext;
	}

	//�U���J�E���g�_�E��
	m_nAttackCount--;

	if (m_nAttackCount == 0)
	{//�U���^�C�~���O

		//�K�E�X�^�b�N
		m_UltStack++;

		//�G����
		CEnemyattack *Enemyattack;
		Enemyattack = CEnemyattack::Create();
		Enemyattack->SetPos(m_pos,ATTACK_SCALE);

		if ((m_UltStack % ULT_STACK_ONE) == 0)
		{//�ʏ�K�E

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
		{//�K�E(��)

			if (m_Form >= BOSS_FORM_TWO)
			{
				//BGM�ݒ�
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
		{//�K�E(��)

			//BGM�ݒ�
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

		//�U���J�E���g�ݒ�
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
//�G�̌��j����
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
//�G�̓����蔻�菈��
//==============================================
bool CEnemy::Collision(D3DXVECTOR3 *pPos,D3DXVECTOR3 *pMove, D3DXVECTOR3 scale, float fWidth, float fHeight)
{
	CObject *pObj;

	//�I�u�W�F�N�g�̐擪���擾
	pObj = CObject::GetTop();

	while (pObj != NULL)
	{//������������Ƃ�

	 //���̃I�u�W�F�N�g��ۑ����Ă���
		CObject *pObjectNext = pObj->GetNext();

		TYPE typObje;

		typObje = pObj->GetType();

		if (typObje == TYPE_ENEMY_BOSS)
		{//�I�u�W�F�N�g���G�̂Ƃ�

		 //�I�u�W�F�N�g��G�ɃL���X�g
			CEnemy *pObjenemy = dynamic_cast<CEnemy*>(pObj);

			if (pPos->x + (scale.x * fWidth) >= pObjenemy->GetPos().x + sinf(pObjenemy->GetRot().y) - (pObjenemy->GetScale().x * MAX_WIDTH)
				&& pPos->x - (scale.x * fWidth) <= pObjenemy->GetPos().x + sinf(pObjenemy->GetRot().y) + (pObjenemy->GetScale().x * MAX_WIDTH)
				&& pPos->z + (scale.z * fHeight) >= pObjenemy->GetPos().z + cosf(pObjenemy->GetRot().y) - (pObjenemy->GetScale().z * MAX_HEIGHT)
				&& pPos->z - (scale.z * fHeight) <= pObjenemy->GetPos().z + cosf(pObjenemy->GetRot().y) + (pObjenemy->GetScale().z * MAX_HEIGHT))
			{//�G�͈͓̔�

				//BGM�ݒ�
				CManager::GetSound()->PlaySound(SOUND_LABEL_ENEMYHIT);

				m_pLife->Sub(-1);

				return true;
			}
		}

		pObj = pObjectNext;
	}

	return false;
}