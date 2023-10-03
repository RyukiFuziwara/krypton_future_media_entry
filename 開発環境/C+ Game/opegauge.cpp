//==============================================
//
//���C�t(Life.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"opegauge.h"
#include"texture.h"
#include"player.h"
#include"life.h"

//****************//
//   �}�N����`   //
//****************//
#define GAUGE_POS		(D3DXVECTOR3(640.0f,650.0f, 0.0f))		//�ʒu�̏����l
#define GAUGE			(D3DXVECTOR3(400.0f,20.0f,0.0f))		//�ʒu�̏����l
#define MAX_GAUGE		(1200)									//�Q�[�W�l�̏����l
#define COLOR			(D3DXCOLOR(0.0f, 1.0f, 0.5f, 1.0f))		//�F

//�ÓI�����o�ϐ��錾
int COpegauge::m_nOpegauge = 0;
int COpegauge::m_nOpegaugeTemp = 0;
//==============================================
//�R���X�g���N�^
//==============================================
COpegauge::COpegauge()
{
	m_nGauge = GAUGE;
	m_nGaugeTemp = m_nGauge;
	m_nLife = 1;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
COpegauge::~COpegauge()
{

}
//==============================================
//���C�t�̏���������
//==============================================
HRESULT COpegauge::Init(void)
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
void COpegauge::Uninit(void)
{
	//�I������
	CGauge::Uninit();
}
//==============================================
//���C�t�̃�������������
//==============================================
COpegauge *COpegauge::Create(void)
{
	COpegauge *pOpeGauge;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pOpeGauge = new COpegauge;

	if (pOpeGauge != NULL)
	{
		//����������
		pOpeGauge->Init();

		pOpeGauge->SetCol(COLOR, 0.0f);
	}

	return pOpeGauge;
}
//==============================================
//���C�t�̍X�V����
//==============================================
void COpegauge::Update(void)
{
	if (CPlayer::GetOperation() > 375 && CPlayer::GetCon() != CPlayer::CONTROL_ALL)
	{
		AddSub(-1);
	}

	if(CPlayer::GetDamage() == true)
	{
		AddSub(-40);
		CPlayer::SetDamage(false);
	}
}
//==============================================
//���C�t�̕`�揈��
//==============================================
void COpegauge::Draw(void)
{
	//�`�揈��
	CGauge::Draw();
}
//==============================================
//���C�t�̐ݒ菈��
//==============================================
void COpegauge::Set(int Opegauge)
{
	m_nOpegauge = Opegauge;

	m_nOpegaugeTemp = m_nOpegauge;
}
//==============================================
//���C�t�̌��Z����
//==============================================
void COpegauge::AddSub(int nValue)
{
	if (m_nOpegauge + nValue >= 0)
	{
		m_nOpegauge += nValue;

		float gauge = m_nGaugeTemp.x / (float)m_nOpegaugeTemp;

		m_nGauge.x += gauge * 2.0f * nValue;

		SetGauge(m_nGauge.x);
	}
	else
	{
		m_nOpegauge += MAX_GAUGE;

		float gauge = m_nGaugeTemp.x / (float)m_nOpegaugeTemp;

		m_nGauge.x += gauge * 2.0f * MAX_GAUGE;

		SetGauge(m_nGauge.x);

		m_nLife--;
	}
}