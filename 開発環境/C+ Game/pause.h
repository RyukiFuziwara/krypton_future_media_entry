//==============================================
//
//�|�[�Y(pause.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include"manager.h"
#include"object2d.h"

//******************//
//���C�g�̃N���X��`//
//******************//
class CPause : public CScene
{
public: //�A�N�Z�X�\

	CPause();							//�R���X�g���N�^
	~CPause();							//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Draw(void);					//�`�揈��

	//�ÓI�����o�֐�
	static CPause *Create(void);		//��������������

	static bool GetPause(void) { return m_bPause; }

private: //�A�N�Z�X(�����o�֐���)

	static bool	  m_bPause;
};

#endif 
