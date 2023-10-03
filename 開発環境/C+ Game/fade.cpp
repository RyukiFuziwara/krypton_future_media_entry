//==============================================
//
//�t�F�[�h(fade.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "fade.h"

CFade::FADE CFade::m_fade = CFade::FADE_NONE;
bool CFade::m_bNext = false;
//==============================================
//�R���X�g���N�^
//==============================================
CFade::CFade()
{
	m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f,1.0f);
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CFade::~CFade()
{

}
//==============================================
//�t�F�[�h�̏���������
//==============================================
HRESULT CFade::Init(void)
{
	CObject2D::Init();

	m_fade = FADE_IN;		//�t�F�[�h�C����Ԃ�

	m_bNext = false;

	SetCol(m_colFade,0.0f);	//�����|���S��(�s����)�ɂ��Ă���

	return S_OK;
}
//==============================================
//�t�F�[�h�̏I������
//==============================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}
//==============================================
//�t�F�[�h�̍X�V����
//==============================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C�����
			m_colFade.a -= 0.03f; //�|���S���𓧖��ɂ��Ă���

			if (m_colFade.a <= 0.0f)
			{
				m_colFade.a = 0.0f;
				m_fade = FADE_NONE;	//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���
			m_colFade.a += 0.03f;

			if (m_colFade.a >= 1.0f)
			{
				m_colFade.a = 1.0f;
				m_bNext = true;
			}
		}

		SetCol(m_colFade, 0.0f);
	}
}
//==============================================
//�t�F�[�h�̕`�揈��
//==============================================
void CFade::Draw(void)
{
	if (m_fade != FADE_NONE)
	{
		CObject2D::Draw();
	}
}