//==============================================
//
//����(input.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "input.h"


//****************//
//   �}�N����`   //
//****************//
#define NUM_KEY_MAX			(256)		//�L�[�̍ő吔

//�ÓI�����o�錾
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==============================================
//�R���X�g���N�^
//==============================================
CInput::CInput()
{
	//�����ݒ�
	LPDIRECTINPUTDEVICE8 m_pDevice = NULL;
}
//==============================================
//�f�X�g���N�^
//==============================================
CInput::~CInput()
{

}
//==============================================
//���͏���
//==============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}	

	return S_OK;
}
//==============================================
//�I������
//==============================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
//==============================================
//�R���X�g���N�^
//==============================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		m_aKeyState[nCount] = 0;
		m_aKeyStateTrigger[nCount] = 0;
	}
}
//==============================================
//�f�X�g���N�^
//==============================================
CInputKeyboard::~CInputKeyboard()
{
	
}
//==============================================
//�L�[�{�[�h���͏���
//==============================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance,hWnd);

	if (m_pInput != NULL)
	{
		//���̓f�o�C�X�̐���
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		if (m_pDevice != NULL)
		{
			//�f�[�^�t�H�[�}�b�g�̐ݒ�
			if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
			{
				return E_FAIL;
			}

			//�������[�h�̐ݒ�
			if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
				DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
			{
				return E_FAIL;
			}

			//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
			m_pDevice->Acquire();
		}
	}

	return S_OK;
}
//==============================================
//�L�[�{�[�h�I������
//==============================================
void CInputKeyboard::Uninit(void)
{
	//�I������
	CInput::Uninit();
}
//==============================================
//�L�[�{�[�h�X�V����
//==============================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}
//==============================================
//�L�[�{�[�h�̃v���X����
//==============================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}
//======================================================================
//�L�[�{�[�h�̃g���K�[�����擾
//======================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//==============================================
//�R���X�g���N�^
//==============================================
CInputKeyPad::CInputKeyPad()
{
	m_aPadState.Gamepad.wButtons = false;
	m_aPadStateTrigger.Gamepad.wButtons = false;
}
//==============================================
//�f�X�g���N�^
//==============================================
CInputKeyPad::~CInputKeyPad()
{

}
//==============================================
//�L�[�{�[�h���͏���
//==============================================
HRESULT CInputKeyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	if (m_pInput != NULL)
	{
		XInputEnable(true);

		memset(&m_aPadState,0,sizeof(XINPUT_STATE));
		memset(&m_aPadStateTrigger,0, sizeof(XINPUT_STATE));
	}

	return S_OK;
}
//==============================================
//�L�[�{�[�h�I������
//==============================================
void CInputKeyPad::Uninit(void)
{
	XInputEnable(false);

	//�I������
	CInput::Uninit();
}
//==============================================
//�L�[�{�[�h�X�V����
//==============================================
void CInputKeyPad::Update(void)
{
	XINPUT_STATE aPadState;	//�p�b�h�̓��͏��

	if (XInputGetState(0, &aPadState) == ERROR_SUCCESS)
	{
		WORD wButton = m_aPadState.Gamepad.wButtons;
		WORD wOldButton = aPadState.Gamepad.wButtons;

		m_aPadStateTrigger.Gamepad.wButtons = ~wButton & wOldButton;
		m_aPadState = aPadState;
	}
}
//==============================================
//�L�[�{�[�h�̃v���X����
//==============================================
bool CInputKeyPad::GetPress(JOYKEY Key)
{
	return(m_aPadState.Gamepad.wButtons & (0x01 << Key));
}
//======================================================================
//�L�[�{�[�h�̃g���K�[�����擾
//======================================================================
bool CInputKeyPad::GetTrigger(JOYKEY Key)
{
	return(m_aPadStateTrigger.Gamepad.wButtons & (0x01 << Key));
}