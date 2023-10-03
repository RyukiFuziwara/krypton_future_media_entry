//==============================================
//
//�G�t�F�N�g�̃r���{�[�h(effect.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"effect.h"
#include"texture.h"

//****************//
//   �}�N����`   //
//****************//
#define MAX_LIFE (20)

//==============================================
//�R���X�g���N�^
//==============================================
CEffect::CEffect()
{
	//�����ݒ�
	m_nLife = MAX_LIFE;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CEffect::~CEffect()
{

}
//==============================================
//�G�t�F�N�g�̃r���{�[�h�̏���������
//==============================================
HRESULT CEffect::Init(void)
{
	//����������
	CBillboard::Init();

	//�G���[�̐ݒ�
	SetType(TYPE_EFFECT);

	//�����ݒ�
	SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);

	return S_OK;
}
//==============================================
//�G�t�F�N�g�̃r���{�[�h�̏I������
//==============================================
void CEffect::Uninit(void)
{
	//�I������
	CBillboard::Uninit();
}
//==============================================
//�G�t�F�N�g�̃r���{�[�h�̃�������������
//==============================================
CEffect *CEffect::Create(void)
{
	CEffect *pEffect;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		//����������
		pEffect->Init();

		//�e�N�X�`���ݒ�
		CTexture *pTexture = CManager::GetTexture();
		pEffect->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_EFFECT));
	}

	return pEffect;
}
//==============================================
//�G�t�F�N�g�̃r���{�[�h�̍X�V����
//==============================================
void CEffect::Update(void)
{
	//�F�ݒ�
	SetCol(GetCol(), ((float)m_nLife / (float)MAX_LIFE));

	m_nLife--;

	if (m_nLife <= 0)
	{//�������Ȃ��Ȃ����Ƃ�

		//�I������
		Uninit();
	}
}
//==============================================
//�G�t�F�N�g�̃r���{�[�h�̕`�揈��
//==============================================
void CEffect::Draw(void)
{
	//�`�揈��
	CBillboard::Draw();
}