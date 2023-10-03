//==============================================
//
//�̗͊Ǘ�(life.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include"ui.h"

//**********************//
//�v���C���[�N���X�̒�`//
//**********************//
class CLife : public CUI
{
public:	//�A�N�Z�X�\

	CLife();						//�R���X�g���N�^
	~CLife();						//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);				//��������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����
	void Draw(void);				//�`�揈��

	//�ÓI�����o�֐�
	static CLife *Create(void);		//��������

	void Set(int life);		//�̗͂̐ݒ�
	void Sub(int nValue);	//�̗͂̌��Z
	int Get(void) { return m_nLife; }	//�̗͂̌��Z

private: //�A�N�Z�X(�����o�֐���)

	int m_nLife;
	int m_nLifeTemp;
	D3DXVECTOR3 m_nGauge;
	D3DXVECTOR3 m_nGaugeTemp;
};

#endif
