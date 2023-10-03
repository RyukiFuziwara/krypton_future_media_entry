//==============================================
//
//�p�[�e�B�N���̃r���{�[�h(particle.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _particle_H_
#define _particle_H_

#include"billboard.h"

#define MAX_particle (4)

//**********************************//
//�p�[�e�B�N���̃r���{�[�h�N���X�̒�`//
//**********************************//
class CParticle : public CBillboard
{
public:	//�A�N�Z�X�\

	CParticle();									//�R���X�g���N�^
	virtual~CParticle();							//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);									//��������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��

	void SetAddMove(float addmove) { m_Addmove = addmove; }

	//�ÓI�����o�֐�
	static CParticle *Create(void);					//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	D3DXVECTOR3 m_move;
	float		m_Addmove;
	int			m_nLife;								//�̗�
};

#endif
