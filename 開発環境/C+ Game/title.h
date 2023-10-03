//==============================================
//
//�^�C�g��(title.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include"manager.h"
#include"object2d.h"

//******************//
//���C�g�̃N���X��`//
//******************//
class CTitle : public CScene
{
public: //�A�N�Z�X�\

	CTitle();							//�R���X�g���N�^
	~CTitle();					//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Draw(void);					//�`�揈��

	//�ÓI�����o�֐�
	static CTitle *Create(void);		//��������������

private: //�A�N�Z�X(�����o�֐���)

	CObject2D *Obj2D[3];

	bool m_bCon;
};

#endif 

