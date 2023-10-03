//==============================================
//
//�I�u�W�F�N�g2D(object2D.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include"object.h"

//**************************//
//2D�I�u�W�F�N�g�N���X�̒�`//
//**************************//
class CObject2D : public CObject
{
public:	//�A�N�Z�X�\

	CObject2D();									//�R���X�g���N�^
	virtual~CObject2D();							//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);								//��������
	virtual void Uninit(void);								//�I������
	virtual void Update(void);								//�X�V����
	virtual void Draw(void);								//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);			//�e�N�X�`���̊��蓖��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//�ʒu�ݒ菈��
	void SetGauge(float Gauge);		//�ʒu�ݒ菈��
	void SetTex(D3DXVECTOR2 tex, float Anim);				//�e�N�X�`�����W�ݒ菈��
	void SetCol(D3DXCOLOR col, float fRadius);				//�F�ݒ菈��
	D3DXVECTOR3 GetPos(void) { return m_pos; }				//�ʒu�擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }			//�ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }				//�p�x�擾����
	D3DXVECTOR3 GetScale(void) { return m_scale; }			//�傫���擾����
	
	//�ÓI�����o�֐�
	static CObject2D *Create(void);							//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture; 	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;	//�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXVECTOR3 m_rot;						//�p�x
	D3DXVECTOR3 m_scale;					//�傫��
};

#endif
