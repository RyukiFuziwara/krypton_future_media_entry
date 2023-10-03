//==============================================
//
//�I�u�W�F�N�gX(player.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _player_H_
#define _player_H_

#include"object.h"
#include"model.h"
#include"motion.h"
#include"ActionGauge.h"

#define PLAYER_MODEL_PARTS (10)	//�v���C���[�̃p�[�c��
//************************//
//�v���C���[�̃N���X�̒�`//
//************************//
class CPlayer : public CObject
{
public:	//�A�N�Z�X�\

	CPlayer();									//�R���X�g���N�^
	~CPlayer();									//�f�X�g���N�^

	typedef enum
	{
		CONTROL_P1 = 0,
		CONTROL_P2,
		CONTROL_ALL
	}CONTROL;

	//�����o�֐�
	HRESULT Init(void);											//��������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)				//�ʒu�ݒ菈��
	{ m_pos = pos; m_posTemp = pos;}

	D3DXVECTOR3 GetPos(void) { return m_pos; }					//�ʒu�擾����
	D3DXVECTOR3 GetScale(void) { return m_scale; }				//�傫���擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }					//�p�x�擾����

	//�ÓI�����o�֐�
	static CPlayer *Create(void);							//��������������

	static void SetChange(bool change) { m_change = change;}		//�ؑ֐ݒ菈��
	static bool GetChange(void) { return m_change; }				//�ؑ֎擾����
	static CONTROL GetCon(void) { return m_con; }					//����擾����
	static void SetAction(bool bAction) { m_bAction = bAction; }	//�s�����Ă邩�̐ݒ菈��
	static bool GetAction(void) { return m_bAction; }				//�s�����Ă邩�̎擾����
	static int GetOperation(void) { return m_nOpeCnt; }				//���삵�Ă邩�̎擾����
	static bool GetDamage(void) { return m_bDamage; }				//�U���󂯂Ă邩�̎擾����
	static void SetDamage(bool bDamage) { m_bDamage = bDamage; }	//�U���󂯂Ă邩�̐ݒ菈��

	static bool Collision(D3DXVECTOR3 *pPos,						//�����蔻��
		D3DXVECTOR3 scale,
		float fWidth,
		float fHeight);

private: //�A�N�Z�X(�����o�֐���)

	void Action(void);								//�s������

	static CONTROL	m_con;
	static CONTROL	m_conTemp;
	static bool		m_change;
	static bool		m_bAction;
	static bool		m_bDamage;
	static int		m_nOpeCnt;

	D3DXVECTOR3		m_pos;							//�ʒu
	D3DXVECTOR3		m_posTemp;						//�ʒu
	D3DXVECTOR3		m_rot;							//�p�x
	D3DXVECTOR3		m_move;							//�ړ���
	D3DXVECTOR3		m_scale;						//�傫��
	D3DXMATRIX		m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel			*m_apModel[PLAYER_MODEL_PARTS];	//���f���ւ̃|�C���^
	CMotion			*pMotion;
	MOTIONTYPE		MotionType;
	int				m_nNumModel;					//���f���̑���
	int				m_nCntEfe;					//���f���̑���
	bool			m_bJump;
	bool			m_bmove;
};

#endif
