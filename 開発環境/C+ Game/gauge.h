//==============================================
//
//�̗͊Ǘ�(gauge.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include"ui.h"

//**********************//
//�N���X�̒�`//
//**********************//
class CGauge : public CUI
{
public:	//�A�N�Z�X�\

	CGauge();						//�R���X�g���N�^
	virtual ~CGauge();				//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);		//��������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	void Set(int Actiongauge);		//�s���Q�[�W�̐ݒ�
	void AddSub(int nValue);		//�s���Q�[�W�̉����Z
	
private: //�A�N�Z�X(�����o�֐���)

	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;
};

#endif
