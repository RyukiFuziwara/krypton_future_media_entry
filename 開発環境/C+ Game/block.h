//==============================================
//
//�u���b�N(block.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _block_H_
#define _block_H_

#include"objX.h"

//**************************//
//2D�I�u�W�F�N�g�N���X�̒�`//
//**************************//
class CBlock : public CObjX
{
public:	//�A�N�Z�X�\

	CBlock();									//�R���X�g���N�^
	virtual~CBlock();							//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);										//��������
	virtual void Uninit(void);										//�I������
	virtual void Update(void);										//�X�V����
	virtual void Draw(void);										//�`�揈��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)					//�ʒu�ݒ菈��
	{m_pos = pos;
	m_scale = scale;
	CObjX::SetPos(m_pos, m_scale);
	};

	void SetRot(D3DXVECTOR3 rot)									//�p�x�ݒ菈��
	{m_rot = rot; CObjX::SetRot(m_rot);}

	D3DXVECTOR3 GetPos(void) { return m_pos; }						//�ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//�p�x�擾����

	static bool Collision(D3DXVECTOR3 *pPos,
		D3DXVECTOR3 pPosOld,
		D3DXVECTOR3 *pMove,
		D3DXVECTOR3 scale,
		float fWidth,
		float fHeight,
		bool bflag);

	//�ÓI�����o�֐�
	static CBlock *Create(void);										//��������������

	static void InitDest(void) { m_nDest = 0; }							//�j�󐔏�����

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	D3DXVECTOR3				m_pos;										//�ʒu
	D3DXVECTOR3				m_rot;										//�p�x
	D3DXVECTOR3				m_move;										//�ړ�
	D3DXVECTOR3				m_scale;									//�p�x
	bool					m_bsmash;									//��΂��t���O
	int						m_nCnt;										//�G�t�F�N�g�J�E���g
	int						m_nLife;									//�̗�
	static int				m_nDest;									//�j��
};

#endif
