//==============================================
//
//����(input.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"
#include"Xinput.h"

//****************//
//���͂̃N���X��`//
//****************//
class CInput
{
public: //�A�N�Z�X�\

	CInput();												//�R���X�g���N�^
	virtual ~CInput();										//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	virtual void Uninit(void);								//�I������
	virtual void Update(void) = 0;							//�X�V����

protected: //�A�N�Z�X(�h���N���X�͉\)

	static LPDIRECTINPUT8 m_pInput;							//
	LPDIRECTINPUTDEVICE8 m_pDevice;							//

private:
};
//**************************//
//�L�[�{�[�h���͂̃N���X��`//
//**************************//
class CInputKeyboard : public CInput
{
public: //�A�N�Z�X�\

	CInputKeyboard();										//�R���X�g���N�^
	~CInputKeyboard();										//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//����������
	void Uninit(void);										//�I������
	void Update(void);										//�X�V����
	bool GetPress(int nKey);								//�v���X�擾
	bool GetTrigger(int nKey);								//�g���K�[�擾

private: //�A�N�Z�X(�����o�֐���)

	BYTE m_aKeyState[256];									//�v���X
	BYTE m_aKeyStateTrigger[256];							//�g���K�[
};
//******************************//
//�p�b�h���͂̃N���X��`//
//******************************//
class CInputKeyPad : public CInput
{
public: //�A�N�Z�X�\

	enum JOYKEY
	{
		JOYKEY_UP = 0,				//�\���{�^����
		JOYKEY_DOWN,				//�\���{�^����
		JOYKEY_LEFT,				//�\���{�^����
		JOYKEY_RIGHT,				//�\���{�^���E
		JOYKEY_START,				//�X�^�[�g�{�^��
		JOYKEY_BACK,				//�o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
		JOYKEY_A,					//A�{�^��
		JOYKEY_B,					//B�{�^��
		JOYKEY_X,					//X�{�^��
		JOYKEY_Y,					//Y�{�^��
		JOYKEY_MAX
	};

	CInputKeyPad();											//�R���X�g���N�^
	~CInputKeyPad();										//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//����������
	void Uninit(void);										//�I������
	void Update(void);										//�X�V����
	bool GetPress(JOYKEY Key);								//�v���X�擾
	bool GetTrigger(JOYKEY Key);								//�g���K�[�擾

private: //�A�N�Z�X(�����o�֐���)

	XINPUT_STATE m_aPadState;							//�v���X
	XINPUT_STATE m_aPadStateTrigger;						//�g���K�[
	XINPUT_STATE m_xInput;									//���͏��
};

#endif
