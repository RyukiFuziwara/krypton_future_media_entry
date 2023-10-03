//==============================================
//
//�G�t�F�N�g�̃r���{�[�h(effect.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _effect_H_
#define _effect_H_

#include"billboard.h"

//**********************************//
//�G�t�F�N�g�̃r���{�[�h�N���X�̒�`//
//**********************************//
class CEffect : public CBillboard
{
public:	//�A�N�Z�X�\

	CEffect();									//�R���X�g���N�^
	virtual~CEffect();							//�f�X�g���N�^

													//�����o�֐�
	HRESULT Init(void);								//��������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

	//�ÓI�����o�֐�
	static CEffect *Create(void);				//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	int							m_nLife;		//�̗�
};

#endif