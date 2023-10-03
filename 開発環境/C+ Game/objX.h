//==============================================
//
//�I�u�W�F�N�gX(objX.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _OBJX_H_
#define _OBJX_H_

#include"object.h"

//**************************//
//2D�I�u�W�F�N�g�N���X�̒�`//
//**************************//
class CObjX : public CObject
{
public:	//�A�N�Z�X�\

	CObjX();									//�R���X�g���N�^
	virtual~CObjX();							//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);										//��������
	virtual void Uninit(void);										//�I������
	virtual void Update(void);										//�X�V����
	virtual void Draw(void);										//�`�揈��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale) { m_pos = pos; m_scale = scale; };	//�ʒu�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) {m_rot = rot;};	//�ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) { return m_pos; }						//�ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//�p�x�擾����
	D3DXVECTOR3 GetScale(void) { return m_scale; }					//�p�x�擾����

	void SetFile(const char *Filename) { m_Filename = Filename; };	//�t�@�C���ݒ菈��

	//�ÓI�����o�֐�
	static CObjX *Create(void);										//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	D3DXMATRIX				m_mtxworld;								//���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;									//�ʒu
	D3DXVECTOR3				m_rot;									//�p�x
	D3DXVECTOR3				m_move;									//�ړ���
	D3DXVECTOR3				m_scale;								//�傫��
	LPD3DXMESH				m_pMesh;								//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;								//�}�e���A���ւ̃|�C���^
	DWORD					m_dwNumMat;								//�}�e���A���̐�
	
	int *m_nIdxTex;

	const char *m_Filename;
};

#endif
