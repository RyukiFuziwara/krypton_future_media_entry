//==============================================
//
//�^�C��(Time.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _TIME_H_
#define _TIME_H_

//�}�N����`
#define	 MAX_NUM_TIME		(2)

#include"ui.h"

//********************//
//�^�C���N���X�̒�`//
//********************//
class CTime : public CUI
{
public:	//�A�N�Z�X�\

	CTime();									//�R���X�g���N�^
	~CTime();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);							//��������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	static void SetNum(int nTime);				//�����̐ݒ�
	static void AddNum(int nValue);				//�����̉��Z
	static int GetNum(void) { return m_nTime; }	//�����̎擾

	//�ÓI�����o�֐�
	static CTime *Create(void);					//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�ÓI�����o�ϐ�
	static CTime	*m_apTime[MAX_NUM_TIME];
	static int m_AgtNum;
	static int m_nTime;
	static int m_nTimeFlame;
};

#endif
