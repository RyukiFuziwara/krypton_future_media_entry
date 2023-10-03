//==============================================
//
//�}�l�[�W���[(manager.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"d3dx9.h"
#include"object.h"

class CRenderer;
class CInputKeyboard;
class CInputKeyPad;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CFade;

//******************//
//�V�[���̃N���X��`//
//******************//
class CScene
{
public: //�A�N�Z�X�\

	enum MODE
	{
		MODE_TITLE,
		MODE_GAME,
		MODE_PAUSE,
		MODE_RESULT,
		MODE_MAX
	};

	CScene();					//�R���X�g���N�^
	virtual ~CScene();			//�f�X�g���N�^

	virtual HRESULT Init(void);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	//�ÓI�����o�֐�
	static CScene *Create(MODE mode);	//��������������
	static CScene::MODE GetMode(void);	//���[�h�̎擾

	static CFade *m_pfade;

private: //�A�N�Z�X(�����o�֐���)

	static MODE m_mode;

	CScene *m_pPause;					//�|�[�Y�̃|�C���^
};

//************************//
//�}�l�[�W���[�N���X�̒�`//
//************************//
class CManager
{
public: //�A�N�Z�X�\

	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		//��������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(int nCount);											//�`�揈��

	static void SetMode(CScene::MODE mode);							//���[�h�̐ݒ�
	static CRenderer *GetRenderer(void);							//�����_�[�̎擾
	static CInputKeyboard *GetInputKeyboard(void);					//�L�[�{�[�h�̎擾
	static CInputKeyPad *GetInputKeyPad(void);					//�L�[�p�b�h�̎擾
	static CCamera *GetCamera(void);								//�J�����̎擾
	static CTexture *GetTexture(void);								//�e�N�X�`���̎擾
	static CSound *GetSound(void);									//�T�E���h�̎擾

private: //�A�N�Z�X(�����o�֐���)

	static CTexture			*m_pTexture;							//�e�N�X�`���̃|�C���^
	static CRenderer		*m_pRenderer;							//�����_�[�̃|�C���^
	static CInputKeyboard	*m_pInputKeyboard;						//�L�[�{�[�h�̃|�C���^
	static CInputKeyPad		*m_pInputKeyPad;						//�L�[�p�b�h�̃|�C���^
	static CSound			*m_pSound;								//�T�E���h�̃|�C���^
	static CCamera			*m_pCamera;								//�J�����̃|�C���^
	static CLight			*m_pLight;								//���C�g�̃|�C���^
	static CScene			*m_pScene;								//�V�[���̃|�C���^
};
#endif 
