//==============================================
//
//�A�N�V�����Q�[�W(actiongauge.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"actiongauge.h"
#include"texture.h"
#include"player.h"

//****************//
//   �}�N����`   //
//****************//
#define GAUGE_POS		(D3DXVECTOR3(170.0f,130.0f, 0.0f))		//�ʒu�̏����l
#define GAUGE			(D3DXVECTOR3(150.0f,20.0f,0.0f))		//�ʒu�̏����l
#define MAX_GAUGE		(600)									//�Q�[�W�l�̏����l
#define COLOR			(D3DXCOLOR(1.0f, 1.0f, 0.3f, 1.0f))		//�F


//�ÓI�����o�ϐ��錾
int CActiongauge::m_nActiongauge = 0;
int CActiongauge::m_nActiongaugeTemp = 0;
//==============================================
//�R���X�g���N�^
//==============================================
CActiongauge::CActiongauge()
{
	m_nGauge = GAUGE;
	m_nGaugeTemp = m_nGauge;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CActiongauge::~CActiongauge()
{

}
//==============================================
//���C�t�̏���������
//==============================================
HRESULT CActiongauge::Init(void)
{
	//����������
	CGauge::Init();

	//�^�C�v�ݒ�
	SetType(TYPE_GAUGE);

	//�ʒu�ݒ�
	SetPos(GAUGE_POS, m_nGauge);

	Set(MAX_GAUGE);

	return S_OK;
}
//==============================================
//���C�t�̏I������
//==============================================
void CActiongauge::Uninit(void)
{
	//�I������
	CGauge::Uninit();
}
//==============================================
//���C�t�̃�������������
//==============================================
CActiongauge *CActiongauge::Create(void)
{
	CActiongauge *pActionGauge;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pActionGauge = new CActiongauge;

	if (pActionGauge != NULL)
	{
		//����������
		pActionGauge->Init();

		pActionGauge->SetCol(COLOR, 0.0f);
	}

	return pActionGauge;
}
//==============================================
//���C�t�̍X�V����
//==============================================
void CActiongauge::Update(void)
{
	if ((CPlayer::GetAction()) == true)
	{
		CPlayer::SetAction(false);
		AddSub(ACTION_COST);
	}
	if (m_nActiongauge < MAX_GAUGE )
	{
		if (CPlayer::GetCon() != CPlayer::CONTROL_ALL)
		{
			AddSub(HEAL_VALUE * 2);
		}
		else
		{
			AddSub(HEAL_VALUE);
		}
	}
}
//==============================================
//���C�t�̕`�揈��
//==============================================
void CActiongauge::Draw(void)
{
	//�`�揈��
	CGauge::Draw();
}
//==============================================
//���C�t�̐ݒ菈��
//==============================================
void CActiongauge::Set(int Actiongauge)
{
	m_nActiongauge = Actiongauge;

	m_nActiongaugeTemp = m_nActiongauge;
}
//==============================================
//���C�t�̌��Z����
//==============================================
void CActiongauge::AddSub(int nValue)
{
	if (m_nActiongauge + nValue > 0)
	{
		m_nActiongauge += nValue;

		float gauge = m_nGaugeTemp.x / (float)m_nActiongaugeTemp;

		m_nGauge.x += gauge * 2.0f * nValue;

		SetGauge(m_nGauge.x);
	}
}