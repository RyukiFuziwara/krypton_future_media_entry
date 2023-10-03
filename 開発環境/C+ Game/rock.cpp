//==============================================
//
//��(rock.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"rock.h"
#include"texture.h"
#include"texture.h"
#include"file.h"
#include"enemy.h"
#include"effect.h"
#include"particle.h"
#include"object3D.h"
#include"player.h"
#include"score.h"
#include"block.h"

#define MAX_WIDTH			(30.0f)
#define MAX_HEIGHT			(30.0f)
#define PARTICLE_INIT		(D3DXVECTOR3(40.0f,40.0f,0.0f))		//�ʒuY�̏����l

D3DXVECTOR3 CRock::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//==============================================
//�R���X�g���N�^
//==============================================
CRock::CRock()
{
	m_spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntEfe = 0;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CRock::~CRock()
{

}
//==============================================
//��̏���������
//==============================================
HRESULT CRock::Init(void)
{
	SetFile("data\\MODEL\\ORNAMENT\\rock.x");

	//����������
	CObjX::Init();

	SetRot(m_rot);
	m_rot.y += 0.16f;

	//�ړ��ʐݒ�
	m_move.x = sinf(m_rot.y) * 15.0f;
	m_move.z = cosf(m_rot.y) * 15.0f;

	//�^�C�v�ݒ�
	SetType(TYPE_ROCK);

	return S_OK;
}
//==============================================
//��̏I������
//==============================================
void CRock::Uninit(void)
{
	//�I������
	CObjX::Uninit();
}
//==============================================
//��̃�������������
//==============================================
CRock *CRock::Create(void)
{
	CRock *prock;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	prock = new CRock;

	if (prock != NULL)
	{
		//����������
		prock->Init();
	}

	return prock;
}
//==============================================
//��̍X�V����
//==============================================
void CRock::Update(void)
{
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	m_spin.x += 0.08f;

	SetRot(D3DXVECTOR3(m_spin.x, m_rot.y, 0.0f));

	SetPos(m_pos, m_scale);

	m_nCntEfe++;

	//��������
	if (m_nCntEfe >= 18)
	{
		CParticle *pParticle;
		pParticle = CParticle::Create();
		pParticle->SetPos(m_pos, PARTICLE_INIT);
		pParticle->SetCol(D3DXCOLOR(0.2f, 0.1f, 0.0f, 0.0f), 0.0f);

		m_nCntEfe = 0;
	}

	//�X�e�[�W�����蔻��
	if ((CObject3D::CollisionStage(m_pos)) == true)
	{
		for (int nCntpar = 0; nCntpar < 8; nCntpar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(m_pos, PARTICLE_INIT);
			pParticle->SetCol(D3DXCOLOR(0.8f, 0.8f, 0.4f, 0.0f), 0.0f);
		}

		Uninit();
	}
	//�v���C���[�̓����蔻��
	else if ((CPlayer::Collision(&m_pos, GetScale(), PARTICLE_INIT.x, PARTICLE_INIT.y)) == true)
	{
		CScore::AddNum(-200);

		for (int nCntpar = 0; nCntpar < 16; nCntpar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(GetPos(), PARTICLE_INIT);
			pParticle->SetCol(D3DXCOLOR(0.8f, 0.5f, 0.4f, 0.0f), 0.0f);
		}

		Uninit();
	}
	//�u���b�N�̓����蔻��
	else if ((CBlock::Collision(&m_pos,D3DXVECTOR3(0.0f,0.0f,0.0f), &m_move,GetScale(), PARTICLE_INIT.x, PARTICLE_INIT.y, false)) == true)
	{
		for (int nCntpar = 0; nCntpar < 16; nCntpar++)
		{
			CParticle *pParticle;
			pParticle = CParticle::Create();
			pParticle->SetPos(GetPos(), PARTICLE_INIT);
			pParticle->SetCol(D3DXCOLOR(0.8f, 0.5f, 0.4f, 0.0f), 0.0f);
		}

		Uninit();
	}
}
//==============================================
//��̕`�揈��
//==============================================
void CRock::Draw(void)
{
	//�`�揈��
	CObjX::Draw();
}
