//==============================================
//
//�I�u�W�F�N�g(object.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include"d3dx9.h"

#define SCALE_INIT		(D3DXVECTOR3(20.0f,20.0f,0.0f))		//�召�̏����l
#define POS_INIT		(D3DXVECTOR3(640.0f,360.0f, 0.0f))	//�ʒuX�̏����l

#define MAX_ANIMATION	(8)									//�A�j���[�V�����ő吔
#define MAX_OBJECT		(8192)								//�I�u�W�F�N�g�̍ő吔

//********************//
//�����_�[�N���X�̒�`//
//********************//
class CObject
{
public:	//�A�N�Z�X�\

	CObject();			//�R���X�g���N�^
	virtual ~CObject();	//�f�X�g���N�^

	//�^�C�v���
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_PLAYER_R,
		TYPE_ENEMY,
		TYPE_ENEMY_BOSS,
		TYPE_BLOCK,
		TYPE_ROCK,
		TYPE_BULLET_ENEMY,
		TYPE_EXPLOSION,
		TYPE_SCORE,
		TYPE_TIME,
		TYPE_LIFE,
		TYPE_GAUGE,
		TYPE_EFFECT,
		TYPE_PARTICLE,
		TYPE_OBJX,
		TYPE_STAGE,
		TYPE_WALL,
		TYPE_PAUSE,
		TYPE_MAX
	}TYPE;

	//�����o�֐�(�������z)
	virtual HRESULT Init(void) = 0;										//��������
	virtual void Uninit(void) = 0;										//�I������
	virtual void Update(void) = 0;										//�X�V����
	virtual void Draw(void) = 0;										//�`�揈��


	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

	//�ÓI�����o�֐�
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	static CObject *GetTop(void) { return m_pTop; }
	CObject *GetNext(void) { return m_pNext; }
	CObject *GetPrev(void) { return m_pPrev; }

protected://�A�N�Z�X(�h���N���X���\)

	void Release(void);

private: //�A�N�Z�X(�����o�֐���)

	static int m_nNumAll;

	TYPE m_type;

	static CObject *m_pTop;
	static CObject *m_pCur;

	CObject *m_pPrev;
	CObject *m_pNext;
};

#endif
