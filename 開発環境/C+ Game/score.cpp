//==============================================
//
//���C�t(Score.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"score.h"
#include"texture.h"

//****************//
//   �}�N����`   //
//****************//
#define POS		(D3DXVECTOR3(30.0f, 50.0f, 0.0f))		//�ʒu�̏����l
#define SCALE	(D3DXVECTOR3(20.0f, 40.0f, 0.0f))		//�傫���̏����l

//�ÓI�����o�ϐ��錾
CScore *CScore::m_apScore[MAX_NUM_SCORE] = {};
int CScore::m_AgtNum = 0;
int CScore::m_nScore = 0;
//==============================================
//�R���X�g���N�^
//==============================================
CScore::CScore()
{
	m_pos = POS;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CScore::~CScore()
{
	m_AgtNum = 0;
}
//==============================================
//���C�t�̏���������
//==============================================
HRESULT CScore::Init(void)
{
	//����������
	CUI::Init();

	//�^�C�v�ݒ�
	SetType(TYPE_SCORE);

	//���C�t�̑���
	m_AgtNum++;

	//�ʒu�ݒ�
	CScore::SetPos(D3DXVECTOR3((m_pos.x + (30.0f * m_AgtNum)), m_pos.y, 0.0f), SCALE);

	return S_OK;
}
//==============================================
//���C�t�̏I������
//==============================================
void CScore::Uninit(void)
{
	//�I������
	CUI::Uninit();
}
//==============================================
//���C�t�̃�������������
//==============================================
CScore *CScore::Create(void)
{
	//�e�N�X�`���̎擾
	CTexture *pTexture = CManager::GetTexture();

	for (int nCount = 0; nCount < MAX_NUM_SCORE; nCount++)
	{
		//����������
		m_apScore[nCount] = new CScore;

		if (m_apScore[nCount] != NULL)
		{
			//����������
			m_apScore[nCount]->Init();

			//�e�N�X�`���ݒ�
			m_apScore[nCount]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_NUMBER));
		}
	}

	//���C�t�̏����l�ݒ�
	SetNum(0);

	return *m_apScore;
}
//==============================================
//���C�t�̍X�V����
//==============================================
void CScore::Update(void)
{
	if (m_bChange == true)
	{
		//�ʒu�ݒ�
		CScore::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), SCALE);

		m_AgtNum++;

		m_bChange = false;
	}
	else if (m_AgtNum > 0)
	{
		CObject *pObj = this;

		//�I�u�W�F�N�g���v���C���[�ɃL���X�g
		CScore *pScore = dynamic_cast<CScore*>(pObj->GetPrev());

		m_pos = D3DXVECTOR3(pScore->m_pos.x + 30.0f, pScore->m_pos.y, 0.0f);

		//�ʒu�ݒ�
		CScore::SetPos(D3DXVECTOR3(m_pos.x,m_pos.y, 0.0f), SCALE);

		m_AgtNum++;

		if (m_AgtNum == MAX_NUM_SCORE)
		{
			m_AgtNum = 0;
		}
	}
}
//==============================================
//���C�t�̕`�揈��
//==============================================
void CScore::Draw(void)
{
	//�`�揈��
	CUI::Draw();
}
//==============================================
//���C�t�̐ݒ菈��
//==============================================
void CScore::SetNum(int nScore)
{
	int aTexU[MAX_NUM_SCORE];
	int nCntScore;

	//���C�t�̐ݒ�
	m_nScore = nScore;

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10;

	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		//�e�N�X�`�����W�ݒ�
		m_apScore[nCntScore]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f),10);
	}
}
//==============================================
//���C�t�̉��Z����
//==============================================
void CScore::AddNum(int nValue)
{
	int aTexU[MAX_NUM_SCORE];
	int nCntScore;

	//���C�t���Z
	m_nScore += nValue;

	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}

	aTexU[0] = m_nScore % 100000000 / 10000000;
	aTexU[1] = m_nScore % 10000000 / 1000000;
	aTexU[2] = m_nScore % 1000000 / 100000;
	aTexU[3] = m_nScore % 100000 / 10000;
	aTexU[4] = m_nScore % 10000 / 1000;
	aTexU[5] = m_nScore % 1000 / 100;
	aTexU[6] = m_nScore % 100 / 10;
	aTexU[7] = m_nScore % 10;

	for (nCntScore = 0; nCntScore < MAX_NUM_SCORE; nCntScore++)
	{
		//�e�N�X�`�����W�ݒ�
 		m_apScore[nCntScore]->SetTex(D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f), 10);
	}
}
void CScore::SetPosOrg(D3DXVECTOR3 pos)
{
	//����������
	m_AgtNum = 0;

	//�ʒu�ύX
	m_pos = pos;

	m_bChange = true;
}