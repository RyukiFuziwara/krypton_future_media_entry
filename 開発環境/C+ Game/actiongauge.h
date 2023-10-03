//==============================================
//
//�̗͊Ǘ�(actiongauge.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _ACTIONGAUGE_H_
#define _ACTIONGAUGE_H_

#include"gauge.h"

//�}�N����`
#define ACTION_COST		(-150)	//�A�N�V�����̏���R�X�g
#define MALTICON_COST	(-3)	//��������̏���R�X�g
#define HEAL_VALUE		(1)		//�񕜃R�X�g
//**********************//
//�N���X�̒�`//
//**********************//
class CActiongauge : public CGauge
{
public:	//�A�N�Z�X�\

	CActiongauge();					//�R���X�g���N�^
	~CActiongauge();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);				//��������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����
	void Draw(void);				//�`�揈��

	//�ÓI�����o�֐�
	static CActiongauge *Create(void);		//��������

	void Set(int Actiongauge);						//�s���Q�[�W�̐ݒ�
	void AddSub(int nValue);						//�s���Q�[�W�̉����Z
	static int GetGauge(void) { return m_nActiongauge; }	//�s���Q�[�W�̎擾

private: //�A�N�Z�X(�����o�֐���)

	static int m_nActiongauge;
	static int m_nActiongaugeTemp;
	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;
};

#endif