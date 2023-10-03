//==============================================
//
//�t�F�[�h(fade.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _FADE_H_
#define _FADE_H_

#include"manager.h"
#include"object2d.h"

//******************//
//�t�F�[�h�̃N���X��`//
//******************//
class CFade : public CObject2D
{
public: //�A�N�Z�X�\

	//�t�F�[�h�̏��
	; typedef enum
	{
		FADE_NONE = 0,	//�������Ă��Ȃ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//�t�F�[�h�A�E�g���
		FADE_MAX

	}FADE;

	CFade();							//�R���X�g���N�^
	~CFade();					//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Draw(void);					//�`�揈��

	static void SetFade(FADE fade) { m_fade = fade; }
	static bool GetbNext(void) { return m_bNext; }

private: //�A�N�Z�X(�����o�֐���)

	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffer;			//�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;					//�ʒu
	D3DXVECTOR2					m_tex;
	static FADE					m_fade;
	D3DXCOLOR					m_colFade;
	static bool					m_bNext;
};

#endif 