//==============================================
//
//���U���g(result.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include"manager.h"
#include"object2d.h"

//******************//
//���U���g�̃N���X��`//
//******************//
class CResult : public CScene
{
public: //�A�N�Z�X�\

	CResult();							//�R���X�g���N�^
	virtual ~CResult();					//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Draw(void);					//�`�揈��

	void RankSort(int nScore);

	//�ÓI�����o�֐�
	static CResult *Create(void);		//��������������

private: //�A�N�Z�X(�����o�֐���)

	CObject2D *Obj2D;
};

#endif 
