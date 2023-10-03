//==============================================
//
//入力(input.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"
#include"Xinput.h"

//****************//
//入力のクラス定義//
//****************//
class CInput
{
public: //アクセス可能

	CInput();												//コンストラクタ
	virtual ~CInput();										//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	virtual void Uninit(void);								//終了処理
	virtual void Update(void) = 0;							//更新処理

protected: //アクセス(派生クラスは可能)

	static LPDIRECTINPUT8 m_pInput;							//
	LPDIRECTINPUTDEVICE8 m_pDevice;							//

private:
};
//**************************//
//キーボード入力のクラス定義//
//**************************//
class CInputKeyboard : public CInput
{
public: //アクセス可能

	CInputKeyboard();										//コンストラクタ
	~CInputKeyboard();										//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//初期化処理
	void Uninit(void);										//終了処理
	void Update(void);										//更新処理
	bool GetPress(int nKey);								//プレス取得
	bool GetTrigger(int nKey);								//トリガー取得

private: //アクセス(メンバ関数内)

	BYTE m_aKeyState[256];									//プレス
	BYTE m_aKeyStateTrigger[256];							//トリガー
};
//******************************//
//パッド入力のクラス定義//
//******************************//
class CInputKeyPad : public CInput
{
public: //アクセス可能

	enum JOYKEY
	{
		JOYKEY_UP = 0,				//十字ボタン上
		JOYKEY_DOWN,				//十字ボタン下
		JOYKEY_LEFT,				//十字ボタン左
		JOYKEY_RIGHT,				//十字ボタン右
		JOYKEY_START,				//スタートボタン
		JOYKEY_BACK,				//バックボタン
		JOYKEY_LEFT_THUMB,			//左スティック押込み
		JOYKEY_RIGHT_THUMB,			//右スティック押込み
		JOYKEY_LEFT_SHOULDER,		//L１ボタン
		JOYKEY_RIGHT_SHOULDER,		//R１ボタン
		JOYKEY_LEFT_TRIGGER,		//L２トリガー
		JOYKEY_RIGHT_TRIGGER,		//R２トリガー
		JOYKEY_A,					//Aボタン
		JOYKEY_B,					//Bボタン
		JOYKEY_X,					//Xボタン
		JOYKEY_Y,					//Yボタン
		JOYKEY_MAX
	};

	CInputKeyPad();											//コンストラクタ
	~CInputKeyPad();										//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//初期化処理
	void Uninit(void);										//終了処理
	void Update(void);										//更新処理
	bool GetPress(JOYKEY Key);								//プレス取得
	bool GetTrigger(JOYKEY Key);								//トリガー取得

private: //アクセス(メンバ関数内)

	XINPUT_STATE m_aPadState;							//プレス
	XINPUT_STATE m_aPadStateTrigger;						//トリガー
	XINPUT_STATE m_xInput;									//入力情報
};

#endif
