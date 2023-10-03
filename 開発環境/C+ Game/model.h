//==============================================
//
//���f��(model.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//**************************//
//2D�I�u�W�F�N�g�N���X�̒�`//
//**************************//
class CModel
{
public:	//�A�N�Z�X�\

	CModel();						//�R���X�g���N�^
	~CModel();						//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(const char *Filename);	//��������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Draw(void);					//�`�揈��

	//�ÓI�����o�֐�
	static CModel *Create(const char *Filename);	//��������������
	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; };

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos + m_offset; };				//�ʒu�ݒ菈��
	void SetOffSet(D3DXVECTOR3 offset) { m_offset = offset; };				//�I�t�Z�b�g�ݒ菈��
	void AddPos(D3DXVECTOR3 add) { m_pos += add; }							//�ʒu���Z�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };							//�p�x�ݒ菈��
	void SetDirection(float direction) { m_direction = direction; }			//�����ݒ菈��
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	
	float GetDirection(void) { return m_direction; }

private: //�A�N�Z�X(�����o�֐���)

	
	LPD3DXMESH		m_pMesh;		//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER	m_pBuffMat;		//�}�e���A���ւ̃|�C���^
	DWORD			m_dwNumMat;		//�}�e���A���̐�
	D3DXVECTOR3		m_pos;			//�ʒu
	D3DXVECTOR3		m_offset;		//�I�t�Z�b�g
	D3DXVECTOR3		m_rot;			//�p�x
	D3DXMATRIX		m_mtxWorld;		//���[���h�}�g���b�N�X
	CModel			*m_pParent;		//�e���f���̃|�C���^
	int				*m_nIdxTex;		//�e�N�X�`���̐�
	float			m_direction;	//�̂̕���
};

#endif
