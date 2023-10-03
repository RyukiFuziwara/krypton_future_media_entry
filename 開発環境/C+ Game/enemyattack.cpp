//==============================================
//
//�G�̍U���̍U��(Enemyattack.cpp)
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
//   �}�N����`   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//�ʒuY�̏����l
#define SCALE				(4.0f)								//�傫��
#define PARTICLE_SCALE		(D3DXVECTOR3(50.0f, 50.0f, 50.0f))	//�p�[�e�B�N���̑傫��
#define PARTICLE_NUM		(4)									//�p�[�e�B�N���̐�
#define MOVE				(15.0f)								//�ړ���
#define COLOR				(D3DXCOLOR(0.2f, 0.4f, 0.8f, 1.0f)) //�F

//==============================================
//�R���X�g���N�^
//==============================================
CEnemyattack::CEnemyattack()
{
	//�����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x
	m_scale = D3DXVECTOR3(SCALE, SCALE, SCALE);
	m_bRotInit = false;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CEnemyattack::~CEnemyattack()
{

}
//==============================================
//�G�̍U���̏���������
//==============================================
HRESULT CEnemyattack::Init(void)
{
	m_apModel = CModel::Create("data\\MODEL\\CHARACTER\\ENEMY\\slime.x");

	m_apModel->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//����
	m_apModel->SetParent(NULL);							//����

	//�^�C�v�ݒ�
	SetType(TYPE_ENEMY);

	return S_OK;
}
//==============================================
//�G�̍U���̏I������
//==============================================
void CEnemyattack::Uninit(void)
{
	if (m_apModel != NULL)
	{
		m_apModel->Uninit();
	}

	//�������
	CObject::Release();
}
//==============================================
//�G�̍U���̃�������������
//==============================================
CEnemyattack *CEnemyattack::Create(void)
{
	CEnemyattack *pEnemyattack;	//Xobj�̃C���X�^���X����

	//����������
	pEnemyattack = new CEnemyattack;

	if (pEnemyattack != NULL)
	{
		//����������
		pEnemyattack->Init();
	}

	return pEnemyattack;
}
//==============================================
//�G�̍U���̍X�V����
//==============================================
void CEnemyattack::Update(void)
{
	CObject *pObj;

	//�I�u�W�F�N�g�̐擪���擾
	pObj = GetTop();

	while (pObj != NULL)
	{//������������Ƃ�

		//���̃I�u�W�F�N�g��ۑ����Ă���
		CObject *pObjectNext = pObj->GetNext();

		CObject::TYPE type;

		type = pObj->GetType();

		if (type == CObject::TYPE_PLAYER_R)
		{//�I�u�W�F�N�g�������_�v���C���[�̂Ƃ�

			//�I�u�W�F�N�g���v���C���[�ɃL���X�g
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

			//�ړ��ʌ���
			m_move.x += (0.0f - m_move.x) * 1.0f;
			m_move.z += (0.0f - m_move.z) * 1.0f;

			SetPos(m_pos,m_scale);
			
			break;
		}

		//���̃I�u�W�F�N�g�ɂ���
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
//�G�̍U���̕`�揈��
//==============================================
void CEnemyattack::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	CTexture *pTexture = CManager::GetTexture();
	D3DXMATRIX	 mtxRot, mtxTrans, mtxScall;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�g�k�𔽉f
	D3DXMatrixScaling(&mtxScall, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScall);

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
	m_apModel->Draw();
}