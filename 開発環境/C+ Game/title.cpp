//==============================================
//
//�^�C�g��(title.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "title.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "object3D.h"
#include "cylinder.h"
#include "block.h"
#include "file.h"
#include "player.h"
#include "manager.h"
#include "sound.h"

#define TITLE_UI_SCALE		( D3DXVECTOR3(300.0f, 90.0f, 0.0f))		//�X�R�A�����NUI
#define ENTER_UI_SCALE		( D3DXVECTOR3(200.0f, 100.0f, 0.0f))	//����̃X�R�AUI
#define CONTROL_UI_SCALE	( D3DXVECTOR3(640.0f, 360.0f, 0.0f))	//�����ʂ̑傫��
//==============================================
//�R���X�g���N�^
//==============================================
CTitle::CTitle()
{
	m_bCon = false;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CTitle::~CTitle()
{

}
//==============================================
//�^�C�g���̏���������
//==============================================
HRESULT CTitle::Init(void)
{
	//�I�u�W�F�N�g�̐�������
	CObject *pObject[MAX_OBJECT] = {};										//�I�u�W�F�N�g�̃C���X�^���X�𐶐�

	pObject[0] = CObject3D::Create();										//3D�I�u�W�F�N�g��������
	pObject[1] = CCylinder::Create();										//�V�����_�[��������
	pObject[2] = CFile::ObjectLoad<CBlock>("data\\FILE\\CSV\\block.csv");	//�u���b�N��������	

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		Obj2D[nCnt] = new CObject2D;
	}

	if (Obj2D != NULL)
	{
		Obj2D[0] = CObject2D::Create();
		Obj2D[0]->SetPos(D3DXVECTOR3(640.0f, 160.0f, 0.0f), TITLE_UI_SCALE);

		Obj2D[1] = CObject2D::Create();
		Obj2D[1]->SetPos(D3DXVECTOR3(640.0f,560.0f, 0.0f), ENTER_UI_SCALE);

		//�e�N�X�`���ݒ�
		CTexture *pTexture = CManager::GetTexture();
		Obj2D[0]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_TITLE));
		Obj2D[1]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_ENTER));
	}

	//BGM�ݒ�
	CManager::GetSound()->PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}
//==============================================
//�^�C�g���̏I������
//==============================================
void CTitle::Uninit(void)
{	
	CObject::ReleaseAll();
}
//==============================================
//�^�C�g���̐�������
//==============================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle;

	//����������
	pTitle = new CTitle;

	if (pTitle != NULL)
	{
		pTitle->Init();
	}

	return pTitle;
}
//==============================================
//�^�C�g���̍X�V����
//==============================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (m_bCon == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true)
		{//ENTER�L�[����������

			CFade::SetFade(CFade::FADE::FADE_OUT);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true)
	{//ENTER�L�[����������

		Obj2D[2] = CObject2D::Create();
		Obj2D[2]->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f), CONTROL_UI_SCALE);

		//�e�N�X�`���ݒ�
		CTexture *pTexture = CManager::GetTexture();
		Obj2D[2]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_CONTROL));

		//BGM�ݒ�
		CManager::GetSound()->PlaySound(SOUND_LABEL_BUTTON);

		m_bCon = true;
		
	}

	if (CFade::GetbNext() == true)
	{
		Uninit();
		CManager::SetMode(CScene::MODE_GAME);
	}
}
//==============================================
//�^�C�g���̕`�揈��
//==============================================
void CTitle::Draw(void)
{

}