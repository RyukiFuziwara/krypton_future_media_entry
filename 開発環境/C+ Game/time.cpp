//==============================================
//
//�^�C��(Time.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"time.h"
#include"texture.h"

//****************//
//   �}�N����`   //
//****************//
#define	SECOND_FLAME	(120)
#define SCALE			(D3DXVECTOR3(30.0f, 60.0f, 0.0f))		//�傫���̏����l


//�ÓI�����o�ϐ��錾
CTime *CTime::m_apTime[MAX_NUM_TIME] = {};
int CTime::m_AgtNum = 0;
int CTime::m_nTime = 0;
int CTime::m_nTimeFlame = SECOND_FLAME;
//==============================================
//�R���X�g���N�^
//==============================================
CTime::CTime()
{

}
//==============================================
//�f�X�X�g���N�^
//==============================================
CTime::~CTime()
{
	m_AgtNum = 0;
}
//==============================================
//�^�C���̏���������
//==============================================
HRESULT CTime::Init(void)
{
	//����������
	CUI::Init();

	//�^�C�v�ݒ�
	SetType(TYPE_TIME);

	//�^�C���̑���
	m_AgtNum++;

	//�ʒu�ݒ�
	CTime::SetPos(D3DXVECTOR3((560.0f + (50.0f * m_AgtNum)), 30.0f, 0.0f), SCALE);

	return S_OK;
}
//==============================================
//�^�C���̏I������
//==============================================
void CTime::Uninit(void)
{
	//�I������
	CUI::Uninit();
}
//==============================================
//�^�C���̃�������������
//==============================================
CTime *CTime::Create(void)
{
	//�e�N�X�`���擾
	CTexture *pTexture = CManager::GetTexture();

	for (int nCount = 0; nCount < MAX_NUM_TIME; nCount++)
	{
		//����������
		m_apTime[nCount] = new CTime;

		if (m_apTime[nCount] != NULL)
		{
			//����������
			m_apTime[nCount]->Init();

			//�e�N�X�`���ݒ�
			m_apTime[nCount]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_NUMBER));
		}
	}

	//�����l�ݒ�
	SetNum(90);

	return *m_apTime;
}
//==============================================
//�^�C���̍X�V����
//==============================================
void CTime::Update(void)
{
	m_nTimeFlame--;

	if (m_nTimeFlame == 0)
	{//�t���[����0�ɂȂ����Ƃ�

		//��b����
		AddNum(-1);

		//�t���[���Đݒ�
		m_nTimeFlame = SECOND_FLAME;
	}
}
//==============================================
//�^�C���̕`�揈��
//==============================================
void CTime::Draw(void)
{
	//�`�揈��
	CUI::Draw();
}
//==============================================
//�^�C���̐ݒ菈��
//==============================================
void CTime::SetNum(int nTime)
{
	int aTexU[MAX_NUM_TIME];
	int nCntTime;

	//�^�C���ݒ�
	m_nTime = nTime;

	aTexU[0] = m_nTime % 100 / 10;
	aTexU[1] = m_nTime % 10;

	for (nCntTime = 0; nCntTime < MAX_NUM_TIME; nCntTime++)
	{
		//�e�N�X�`�����W�ݒ�
		m_apTime[nCntTime]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 1.0f), 10);
	}
}
//==============================================
//�^�C���̉��Z����
//==============================================
void CTime::AddNum(int nValue)
{
	int aTexU[MAX_NUM_TIME];
	int nCntTime;

	//�^�C�����Z
	m_nTime += nValue;

	aTexU[0] = m_nTime % 100 / 10;
	aTexU[1] = m_nTime % 10;

	for (nCntTime = 0; nCntTime < MAX_NUM_TIME; nCntTime++)
	{
		//�e�N�X�`�����W�ݒ�
		m_apTime[nCntTime]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntTime] * 0.1f), 1.0f), 10);
	}
}