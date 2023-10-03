//==============================================
//
//�p�[�e�B�N���̃r���{�[�h(particle.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"particle.h"
#include"texture.h"

//****************//
//   �}�N����`   //
//****************//
#define MAX_LIFE (50)
#define ADD_MOVE_INIT (4.0f)

//==============================================
//�R���X�g���N�^
//==============================================
CParticle::CParticle()
{
	//�����ݒ�
	m_Addmove = ADD_MOVE_INIT;
	m_nLife = MAX_LIFE;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CParticle::~CParticle()
{

}
//==============================================
//�p�[�e�B�N���̃r���{�[�h�̏���������
//==============================================
HRESULT CParticle::Init(void)
{
	CBillboard::Init();

	//�e�N�X�`���擾
	CTexture *pTexture = CManager::GetTexture();

	//�ړ��ʐݒ�
	m_move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 8 - 4);
	m_move.y = cosf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 8 - 4);
	m_move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * (float)(rand() % 8 - 4);

	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f),0.0f);

	//�^�C�v�ݒ�
	SetType(TYPE_PARTICLE);

	return S_OK;
}
//==============================================
//�p�[�e�B�N���̃r���{�[�h�̏I������
//==============================================
void CParticle::Uninit(void)
{
	//�I������
	CBillboard::Uninit();
}
//==============================================
//�p�[�e�B�N���̃r���{�[�h�̃�������������
//==============================================
CParticle *CParticle::Create(void)
{
	CParticle *pParticle;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pParticle = new CParticle;

	if (pParticle != NULL)
	{
		//����������
		pParticle->Init();

		//�e�N�X�`���ݒ�
		CTexture *pTexture = CManager::GetTexture();
		pParticle->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_EFFECT));
	}

	return pParticle;
}
//==============================================
//�p�[�e�B�N���̃r���{�[�h�̍X�V����
//==============================================
void CParticle::Update(void)
{
	D3DXVECTOR3 pos;

	m_nLife--;

	if (m_nLife <= 0)
	{//�������Ȃ��Ȃ����Ƃ�

		//�I������
		Uninit();
	}
	else
	{
		
		if (m_nLife >= MAX_LIFE)
		{
			//�ʒu�擾
			pos = GetPos();
		}
		else
		{
			//�F�ݒ�
			SetCol(GetCol(), ((float)m_nLife / (float)MAX_LIFE));

			//�ʒu�擾
			pos = GetPos();

			//�ړ��ʑ��
			pos.x += m_move.x * m_Addmove;
			pos.y += m_move.y * m_Addmove;
			pos.z += m_move.z * m_Addmove;

			//�ړ��ʌ���
			m_move.x += (0.0f - m_move.x) * 0.3f;
			m_move.y += (0.0f - m_move.y) * 0.3f;
			m_move.z += (0.0f - m_move.z) * 0.3f;
		}

		//�ʒu�ݒ�
		SetPos(pos,GetScale());
	}
}
//==============================================
//�p�[�e�B�N���̃r���{�[�h�̕`�揈��
//==============================================
void CParticle::Draw(void)
{
	//�`�揈��
	CBillboard::Draw();
}