//==============================================
//
//�G3D(enemy.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _enemy_H_
#define _enemy_H_

#include"object.h"
#include"model.h"
#include"motion.h"
#include"life.h"

#define ENEMY_MODEL_PARTS (3)	//�v���C���[�̃p�[�c��
//************************//
//	  �G�̃N���X�̒�`	  //
//************************//
class CEnemy : public CObject
{
public:	//�A�N�Z�X�\

	CEnemy();									//�R���X�g���N�^
	~CEnemy();									//�f�X�g���N�^

	typedef enum
	{
		BOSS_FORM_ONE = 0,
		BOSS_FORM_TWO,
		BOSS_FORM_THREE,
		BOSS_FORM_MAX,

	}BOSS_FORM;

	//�����o�֐�
	HRESULT Init(void);								//��������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

	virtual void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale) { m_pos = pos;}			//�ʒu�ݒ菈��
	virtual D3DXVECTOR3 GetPos(void) { return m_pos; }								//�ʒu�擾����
	virtual D3DXVECTOR3 GetScale(void) { return m_scale; }							//�傫���擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }										//�p�x�擾����
	static int GetFormType(void) { return m_Form; }

	//�ÓI�����o�֐�
	static CEnemy *Create(void);												//��������������

	//�����蔻��
	static bool CEnemy::Collision(
		D3DXVECTOR3 *pPos,
		D3DXVECTOR3 *pMove,
		D3DXVECTOR3 scale,
		float fWidth,
		float fHeight);


private: //�A�N�Z�X(�����o�֐���)

	void Attack(void);								//�X�V����
	void Defeat(void);								//���j����

	static CLife	*m_pLife;
	static int		m_Form;							//�{�X�̌`��

	int				m_nLifeTemp;
	D3DXVECTOR3		m_pos;							//�ʒu
	D3DXVECTOR3		m_rot;							//�p�x
	D3DXVECTOR3		m_scale;						//�傫��
	D3DXMATRIX		m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel			*m_apModel[ENEMY_MODEL_PARTS];	//���f���ւ̃|�C���^
	int				m_nNumModel;					//���f���̑���
	CMotion			*pMotion;
	
	int				m_nAttackCount;					//�U���J�E���g
	int				m_UltStack;						//�K�E�X�^�b�N
	int				m_nNum;							//�̗�
	float			m_movey;						//�d�͉��Z�p

	bool			m_bDefeat;
};
#endif
