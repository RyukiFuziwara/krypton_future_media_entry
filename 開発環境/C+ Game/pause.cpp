//==============================================
//
//�|�[�Y(pause.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "object3D.h"
#include "cylinder.h"
#include "block.h"
#include "file.h"
#include "player.h"

bool CPause::m_bPause = false;
//==============================================
//�R���X�g���N�^
//==============================================
CPause::CPause()
{
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CPause::~CPause()
{

}
//==============================================
//�|�[�Y�̏���������
//==============================================
HRESULT CPause::Init(void)
{
	return S_OK;
}
//==============================================
//�|�[�Y�̏I������
//==============================================
void CPause::Uninit(void)
{
	CScene::Uninit();
}
//==============================================
//�|�[�Y�̐�������
//==============================================
CPause *CPause::Create(void)
{
	CPause *pPause;

	//����������
	pPause = new CPause;

	if (pPause != NULL)
	{
		pPause->Init();
	}

	return pPause;
}
//==============================================
//�|�[�Y�̍X�V����
//==============================================
void CPause::Update(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_START) == true)
	{//ENTER�L�[����������

		if (m_bPause == false)
		{
			m_bPause = true;
		}
		else if (m_bPause == true)
		{
			m_bPause = false;
		}
	}
}
//==============================================
//�|�[�Y�̕`�揈��
//==============================================
void CPause::Draw(void)
{

}