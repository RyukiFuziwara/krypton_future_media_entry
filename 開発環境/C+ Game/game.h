//==============================================
//
//�Q�[��(game.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _GAME_H_
#define _GAME_H_

#include"manager.h"

class COpegauge;
//******************//
//�Q�[���̃N���X��`//
//******************//
class CGame : public CScene
{
public: //�A�N�Z�X�\

	CGame();							//�R���X�g���N�^
	virtual ~CGame();					//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Draw(void);					//�`�揈��

	//�ÓI�����o�֐�
	static CGame *Create(void);						//��������������

private: //�A�N�Z�X(�����o�֐���)

	COpegauge *m_obj;
};

#endif 

