//==============================================
//
//�����֌W(ui.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _UI_H_
#define _UI_H_

#include"object2D.h"

//********************//
//�����֌W�N���X�̒�`//
//********************//
class CUI : public CObject2D
{
public:	//�A�N�Z�X�\

	CUI();									//�R���X�g���N�^
	virtual~CUI();							//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);							//��������
	virtual void Uninit(void);							//�I������
	virtual void Update(void);							//�X�V����
	virtual void Draw(void);							//�`�揈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//�ʒu�擾����

	//�ÓI�����o�֐�
	static CUI *Create(void);						//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture; 	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	//�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
};

#endif
