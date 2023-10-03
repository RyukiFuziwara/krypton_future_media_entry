//==============================================
//
//�}�l�[�W���[(manager.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"camera.h"
#include"light.h"
#include"texture.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"pause.h"

//****************//
//   �}�N����`   //
//****************//

//�ÓI�����o�錾
CTexture *CManager::m_pTexture = NULL;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputKeyPad *CManager::m_pInputKeyPad = NULL;
CSound *CManager::m_pSound = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CScene *CManager::m_pScene = NULL;
CFade  *CScene::m_pfade = NULL;
CScene::MODE CScene::m_mode = CScene::MODE_TITLE;
//==============================================
//�R���X�g���N�^
//==============================================
CManager::CManager()
{
	
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CManager::~CManager()
{

}
//==============================================
//����������
//==============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pRenderer = new CRenderer;			//�����_�[�̃C���X�^���X�𐶐�

	if (m_pRenderer != NULL)
	{//�������m�ۂł��Ă���Ƃ�

		//����������
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//���������������s�����Ƃ�8 ji
			return -1;
		}
	}

	m_pInputKeyboard = new CInputKeyboard;	//�L�[�{�[�h�̃C���X�^���X�𐶐�

 	if (m_pInputKeyboard != NULL)
	{//�������m�ۂł��Ă���Ƃ�

		//�L�[�{�[�h�̏���������
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//���������������s�����Ƃ�
			return E_FAIL;
		}
	}

	m_pInputKeyPad = new CInputKeyPad;	//�L�[�{�[�h�̃C���X�^���X�𐶐�

	if (m_pInputKeyPad != NULL)
	{//�������m�ۂł��Ă���Ƃ�

	 //�L�[�p�b�h�̏���������
		if (FAILED(m_pInputKeyPad->Init(hInstance, hWnd)))
		{//���������������s�����Ƃ�
			return E_FAIL;
		}
	}

	m_pSound = new CSound;	//�T�E���h�̃C���X�^���X�𐶐�

	if (m_pSound != NULL)
	{//�������m�ۂł��Ă���Ƃ�

		//�T�E���h�̏���������
		if (FAILED(m_pSound->Init(hWnd)))
		{//���������������s�����Ƃ�
			return E_FAIL;
		}
	}

	m_pCamera = new CCamera;	//�J�����̃C���X�^���X�𐶐�

	if (m_pCamera != NULL)
	{//�������m�ۂł��Ă���Ƃ�

	 //�J�����̏���������
		if (FAILED(m_pCamera->Init()))
		{//���������������s�����Ƃ�
			return E_FAIL;
		}
	}

	m_pLight = new CLight;	//���C�g�̃C���X�^���X�𐶐�

	if (m_pLight != NULL)
	{//�������m�ۂł��Ă���Ƃ�

	 //�J�����̏���������
		if (FAILED(m_pLight->Init()))
		{//���������������s�����Ƃ�
			return E_FAIL;
		}
	}

	//�e�N�X�`���ǂݍ���
	m_pTexture = new CTexture;
	m_pTexture->Load();

	m_pScene = CScene::Create(CScene::MODE_TITLE);

	return S_OK;
}
//==============================================
//�I������
//==============================================
void CManager::Uninit(void)
{
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}

	//�L�[�{�[�h�̏I������
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�L�[�p�b�h�̏I������
	if (m_pInputKeyPad != NULL)
	{
		m_pInputKeyPad->Uninit();

		delete m_pInputKeyPad;
		m_pInputKeyPad = NULL;
	}

	//�����_�[�̏I������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//�T�E���h�̏I������
	if (m_pSound != NULL)
	{
		m_pSound->StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	//�J�����̏I������
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//���C�g�̏I������
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	//�e�N�X�`���̔j��
	m_pTexture->Unload();
	m_pTexture = NULL;
}
//==============================================
//�X�V����
//==============================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//�L�[�p�b�h�̍X�V����
	if (m_pInputKeyPad!= NULL)
	{
		m_pInputKeyPad->Update();
	}

	//�����_�[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//�J�����̍X�V����
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	//���C�g�̍X�V����
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	if (m_pScene != NULL)
	{
		m_pScene->Update();
	}
}
//==============================================
//�`�揈��
//==============================================
void CManager::Draw(int nCount)
{
	//�����_�[�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->SetFPS(nCount);

		m_pRenderer->Draw();
	}

	if (m_pScene != NULL)
	{
		m_pScene->Draw();
	}
}
//==============================================
//���[�h�̎擾����
//==============================================
void CManager::SetMode(CScene::MODE mode)
{
	//�T�E���h��~
	m_pSound->StopSound();

	//�j��
	delete m_pScene;
	m_pScene = NULL;

	//�V�[������
	m_pScene = CScene::Create(mode);
}
//==============================================
//���[�h�̎擾����
//==============================================
CScene::MODE CScene::GetMode(void)
{
	return m_mode;
}
//==============================================
//�����_���[�擾����
//==============================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//==============================================
//�L�[�{�[�h�擾����
//==============================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//==============================================
//�L�[�p�b�h�擾����
//==============================================
CInputKeyPad *CManager::GetInputKeyPad(void)
{
	return m_pInputKeyPad;
}
//==============================================
//�J�����擾����
//==============================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}
//==============================================
//�e�N�X�`���擾����
//==============================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}
//==============================================
//�T�E���h�̎擾����
//==============================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}
//==============================================
//�R���X�g���N�^
//==============================================
CScene::CScene()
{

}
//==============================================
//�f�X�X�g���N�^
//==============================================
CScene::~CScene()
{

}
//==============================================
//�V�[���̏���������
//==============================================
HRESULT CScene::Init()
{	
	//�V�[������
	CPause *pPause = CPause::Create();
	m_pPause = pPause;

	return S_OK;
}
//==============================================
//�V�[���̏I������
//==============================================
void CScene::Uninit()
{
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();

		//�j��
		delete m_pPause;
		m_pPause = NULL;
	}
}
//==============================================
//�V�[���̐�������
//==============================================
CScene *CScene::Create(CScene::MODE mode)
{
	CScene *pScene;

	//����������
	pScene = new CScene;

	if (pScene != NULL)
	{
		//���[�h��ݒ�
		m_mode = mode;

		switch (m_mode)
		{
		case MODE_TITLE:

			pScene = CTitle::Create();

			break;

		case MODE_GAME:

			pScene = CGame::Create();

			break;

		case MODE_RESULT:

			pScene = CResult::Create();

			break;
		}

		m_pfade = new CFade;

		if (m_pfade != NULL)
		{
			m_pfade->Init();
			m_pfade->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
		}
	}
	
	return pScene;
}
//==============================================
//�V�[���̍X�V����
//==============================================
void CScene::Update()
{
	if (m_pPause != NULL)
	{
		m_pPause->Update();
	}
}
//==============================================
//�V�[���̕`�揈��
//==============================================
void CScene::Draw()
{

}