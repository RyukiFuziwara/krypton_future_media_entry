//==============================================
//
//���C�g(Light.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _LIGHT_H_
#define _LIGhT_H_

#include"main.h"

//******************//
//���C�g�̃N���X��`//
//******************//
class CLight
{
public: //�A�N�Z�X�\

	CLight();							//�R���X�g���N�^
	virtual ~CLight();					//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����

private: //�A�N�Z�X(�����o�֐���)

	D3DLIGHT9 m_Light;
};
#endif 
