//==============================================
//
//�r���{�[�h(billvoard.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include"object.h"

//**************************//
//2D�I�u�W�F�N�g�N���X�̒�`//
//**************************//
class CBillboard : public CObject
{
public:	//�A�N�Z�X�\

	CBillboard();										//�R���X�g���N�^
	virtual~CBillboard();								//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);							//��������
	virtual void Uninit(void);							//�I������
	virtual void Update(void);							//�X�V����
	virtual void Draw(void);							//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);		//�e�N�X�`���̊��蓖��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	//�ʒu�ݒ菈��
	void SetCol(D3DXCOLOR col, float fRadius);				//�F�ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//�ʒu�擾����
	D3DXVECTOR3 GetScale(void) { return m_scale; }		//�p�x�擾����
	D3DXCOLOR	GetCol(void) { return m_col; }		//�p�x�擾����

	//�ÓI�����o�֐�
	static CBillboard *Create(void);					//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture; 			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffer;			//�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX					m_mtxworld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;					//�ʒu
	D3DXVECTOR3					m_scale;				//�傫��
	D3DXCOLOR					m_col;				//�傫��
};

#endif