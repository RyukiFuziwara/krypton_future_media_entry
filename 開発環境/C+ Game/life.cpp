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
#include"life.h"
#include"texture.h"

//****************//
//   �}�N����`   //
//****************//
#define GAUGE_POS	(D3DXVECTOR3(640.0f,70.0f, 0.0f))		//�ʒu�̏����l
#define GAUGE		(D3DXVECTOR3(200.0f,10.0f,0.0f))		//�ʒu�̏����l
#define COLOR		(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))		//�F
//==============================================
//�R���X�g���N�^
//==============================================
CLife::CLife()
{
	m_nGauge = GAUGE;
	m_nGaugeTemp = m_nGauge;
	m_nLife = 0;
	m_nLifeTemp = 0;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CLife::~CLife()
{

}
//==============================================
//���C�t�̏���������
//==============================================
HRESULT CLife::Init(void)
{
	//����������
	CUI::Init();

	//�^�C�v�ݒ�
	SetType(TYPE_LIFE);

	//�ʒu�ݒ�
	SetPos(GAUGE_POS,m_nGauge);

	return S_OK;
}
//==============================================
//���C�t�̏I������
//==============================================
void CLife::Uninit(void)
{
	//�I������
	CUI::Uninit();
}
//==============================================
//���C�t�̃�������������
//==============================================
CLife *CLife::Create(void)
{
	CLife *pLife;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pLife = new CLife;

	if (pLife != NULL)
	{
		//����������
		pLife->Init();

		pLife->SetCol(COLOR,0.0f);
	}

	return pLife;
}
//==============================================
//���C�t�̍X�V����
//==============================================
void CLife::Update(void)
{
	
}
//==============================================
//���C�t�̕`�揈��
//==============================================
void CLife::Draw(void)
{
	//�`�揈��
	CUI::Draw();
}
//==============================================
//���C�t�̐ݒ菈��
//==============================================
void CLife::Set(int life)
{
	m_nLife = life;

	m_nLifeTemp = m_nLife;
}
//==============================================
//���C�t�̌��Z����
//==============================================
void CLife::Sub(int nValue)
{
	m_nLife += nValue;

 	float gauge = m_nGaugeTemp.x / (float)m_nLifeTemp;

	m_nGauge.x -= gauge * 2.0f;

  	SetGauge(m_nGauge.x);
}