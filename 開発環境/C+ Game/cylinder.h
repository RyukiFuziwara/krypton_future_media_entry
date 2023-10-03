//==============================================
//
//�I�u�W�F�N�g3D(Cylinder.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _Cylinder_H_
#define _Cylinder_H_

#include"object.h"

//**************************//
//2D�I�u�W�F�N�g�N���X�̒�`//
//**************************//
class CCylinder : public CObject
{
public:	//�A�N�Z�X�\

	CCylinder();									//�R���X�g���N�^
	virtual~CCylinder();							//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);							//��������
	virtual void Uninit(void);							//�I������
	virtual void Update(void);							//�X�V����
	virtual void Draw(void);							//�`�揈��

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);		//�e�N�X�`���̊��蓖��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	//�ʒu�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		//�X���ݒ菈��
	D3DXVECTOR3 GetPos(void) { return m_pos; }			//�ʒu�擾����
	D3DXVECTOR3 GetScale(void) { return m_scale; }		//�p�x�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }			//�p�x�擾����

	//�ÓI�����o�֐�
	static CCylinder *Create(void);						//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	LPDIRECT3DTEXTURE9		m_pTexture; 				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffer;				//�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuffer;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxworld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;						//�ʒu
	D3DXVECTOR3				m_rot;						//�p�x
	D3DXVECTOR3				m_scale;					//�傫��
};

#endif
