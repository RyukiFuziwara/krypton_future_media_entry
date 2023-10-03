//==============================================
//
//�G�̍U��(enemyattack.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _ENEMYATTACK_H_
#define _ENEMYATTACK_H_

#include"object.h"
#include"model.h"
#include"motion.h"

//************************//
//	�G�̍U���N���X�̒�`�@//
//************************//
class CEnemyattack : public CObject
{
public:	//�A�N�Z�X�\

	CEnemyattack();									//�R���X�g���N�^
	~CEnemyattack();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);								//��������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale) { m_pos = pos; m_scale = scale; }		//�ʒu�ݒ菈��
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					//�p�x�ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }						//�ʒu�擾����
	D3DXVECTOR3 GetScale(void) { return m_scale; }					//�傫���擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//�p�x�擾����

	//�ÓI�����o�֐�
	static CEnemyattack *Create(void);				//��������������

private: //�A�N�Z�X(�����o�֐���)

	D3DXVECTOR3		m_pos;							//�ʒu
	D3DXVECTOR3		m_move;							//�ʒu
	D3DXVECTOR3		m_rot;							//�p�x
	D3DXVECTOR3		m_scale;						//�傫��
	D3DXMATRIX		m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel			*m_apModel;						//���f���ւ̃|�C���^
	int				m_nNumModel;					//���f���̑���
	CMotion			*pMotion;
	bool			m_bRotInit;						//�ŏ������p�x���擾����p
	int				m_nLife;						//�̗�
};

#endif
