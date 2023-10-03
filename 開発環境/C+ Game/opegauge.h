//==============================================
//
//�Ǘ�(opegauge.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _OPEGAUGE_H_
#define _OPEGAUGE_H_

#include"gauge.h"
#include"life.h"

//�}�N����`

//**********************//
//�N���X�̒�`//
//**********************//
class COpegauge : public CGauge
{
public:	//�A�N�Z�X�\

	COpegauge();					//�R���X�g���N�^
	~COpegauge();					//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);				//��������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����
	void Draw(void);				//�`�揈��

	//�ÓI�����o�֐�
	static COpegauge *Create(void);		//��������

	void Set(int Opegauge);								//����Q�[�W�̐ݒ�
	void AddSub(int nValue);							//����Q�[�W�̉����Z
	int GetLife(void) { return m_nLife; }				//�̗͂̎擾
	static int GetGauge(void) { return m_nOpegauge; }	//����Q�[�W�̎擾

private: //�A�N�Z�X(�����o�֐���)

	static int m_nOpegauge;
	static int m_nOpegaugeTemp;

	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;

	int m_nLife;
};

#endif
