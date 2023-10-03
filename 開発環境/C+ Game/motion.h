//==============================================
//
//���[�V����(motion.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "model.h"

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//�j���[�g����
	MOTIONTYPE_MOVE,		//�_�b�V��
	MOTIONTYPE_JUMP,		//�W�����v
	MOTIONTYPE_LAND,		//���n
	MOTIONTYPE_SMASH,
	MOTIONTYPE_MAX
} MOTIONTYPE;

class CMotion
{
public:

	CMotion();
	~CMotion();

	//�L�[�\����
	typedef struct
	{
		float fPosX;	//�ʒuX
		float fPosY;	//�ʒuY
		float fPosZ;	//�ʒuZ
		float fRotX;	//����X
		float fRotY;	//����Y
		float fRotZ;	//����Z
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame;	//�Đ��t���[��
		KEY aKey[10];	//���f���̃L�[�v�f
	} KEY_INFO;
	
	//���\����
	typedef struct
	{
		bool m_bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[10];	//�L�[�̏��

	} INFO;

	//�����o�֐�
	void Set(int nType);									//�ݒ菈��
	void Update(void);										//�X�V����
	int GetType(void);										//�^�C�v�擾����
	int GetTypeTemp(void) { return m_nTypeTemp; }			//�O��^�C�v�擾����
	bool IsFinish(void);									//�I�_����
	void SetInfo(INFO info);								//���ݒ菈��
	void SetModel(CModel **ppModel, int nNumModel);			//���f���ݒ菈��

private:

	INFO m_aInfo[10];
	int m_nNumAll;
	int m_nType;
	int m_nTypeTemp;
	int m_nKey;
	int m_nCounter;
	bool m_bFinish;
	CModel **m_ppModel;
	int m_nNumModel;
};

#endif
