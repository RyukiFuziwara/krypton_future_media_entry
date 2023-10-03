//==============================================
//
//入力(input.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "input.h"


//****************//
//   マクロ定義   //
//****************//
#define NUM_KEY_MAX			(256)		//キーの最大数

//静的メンバ宣言
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//==============================================
//コンストラクタ
//==============================================
CInput::CInput()
{
	//初期設定
	LPDIRECTINPUTDEVICE8 m_pDevice = NULL;
}
//==============================================
//デストラクタ
//==============================================
CInput::~CInput()
{

}
//==============================================
//入力処理
//==============================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}	

	return S_OK;
}
//==============================================
//終了処理
//==============================================
void CInput::Uninit(void)
{
	//入力デバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
//==============================================
//コンストラクタ
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
//デストラクタ
//==============================================
CInputKeyboard::~CInputKeyboard()
{
	
}
//==============================================
//キーボード入力処理
//==============================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{

	CInput::Init(hInstance,hWnd);

	if (m_pInput != NULL)
	{
		//入力デバイスの生成
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		if (m_pDevice != NULL)
		{
			//データフォーマットの設定
			if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
			{
				return E_FAIL;
			}

			//協調モードの設定
			if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
				DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
			{
				return E_FAIL;
			}

			//キーボードへのアクセス権を獲得
			m_pDevice->Acquire();
		}
	}

	return S_OK;
}
//==============================================
//キーボード終了処理
//==============================================
void CInputKeyboard::Uninit(void)
{
	//終了処理
	CInput::Uninit();
}
//==============================================
//キーボード更新処理
//==============================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
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
//キーボードのプレス処理
//==============================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}
//======================================================================
//キーボードのトリガー情報を取得
//======================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//==============================================
//コンストラクタ
//==============================================
CInputKeyPad::CInputKeyPad()
{
	m_aPadState.Gamepad.wButtons = false;
	m_aPadStateTrigger.Gamepad.wButtons = false;
}
//==============================================
//デストラクタ
//==============================================
CInputKeyPad::~CInputKeyPad()
{

}
//==============================================
//キーボード入力処理
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
//キーボード終了処理
//==============================================
void CInputKeyPad::Uninit(void)
{
	XInputEnable(false);

	//終了処理
	CInput::Uninit();
}
//==============================================
//キーボード更新処理
//==============================================
void CInputKeyPad::Update(void)
{
	XINPUT_STATE aPadState;	//パッドの入力情報

	if (XInputGetState(0, &aPadState) == ERROR_SUCCESS)
	{
		WORD wButton = m_aPadState.Gamepad.wButtons;
		WORD wOldButton = aPadState.Gamepad.wButtons;

		m_aPadStateTrigger.Gamepad.wButtons = ~wButton & wOldButton;
		m_aPadState = aPadState;
	}
}
//==============================================
//キーボードのプレス処理
//==============================================
bool CInputKeyPad::GetPress(JOYKEY Key)
{
	return(m_aPadState.Gamepad.wButtons & (0x01 << Key));
}
//======================================================================
//キーボードのトリガー情報を取得
//======================================================================
bool CInputKeyPad::GetTrigger(JOYKEY Key)
{
	return(m_aPadStateTrigger.Gamepad.wButtons & (0x01 << Key));
}