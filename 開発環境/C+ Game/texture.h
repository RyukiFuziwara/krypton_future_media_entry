//==============================================
//
//�e�N�X�`���Ǘ�(texture.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include"main.h"

#define MAX_TEXTURE (21)

//**********************//
//�e�N�X�`���̃N���X��`//
//**********************//
class CTexture
{
public: //�A�N�Z�X�\

	CTexture();											//�R���X�g���N�^
	virtual ~CTexture();								//�f�X�g���N�^

	typedef enum 
	{
		TEXTURE_TITLE = 0,
		TEXTURE_RESULT,
		TEXTURE_ENTER,
		TEXTURE_RANKING,
		TEXTURE_YOURSCORE,
		TEXTURE_FIRST,
		TEXTURE_SECOND,
		TEXTURE_THIRD,
		TEXTURE_NUMBER,
		TEXTURE_FLAME,
		TEXTURE_EFFECT,
		TEXTURE_PLAYER,
		TEXTURE_ENEMY,
		TEXTURE_BLOCK,
		TEXTURE_BULLET,
		TEXTURE_EXPLOSION,
		TEXTURE_CONTROL,
		TEXTURE_MAX,

	}TEXTURE;

	HRESULT Load(void);									//����������
	void Unload(void);									//�I������
	int Regist(const char *pFilename);					//
	LPDIRECT3DTEXTURE9 GetAddress(int ndlx);			//�e�N�X�`���擾

private: //�A�N�Z�X(�����o�֐���)

	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];		//�e�N�X�`���ւ̃|�C���^
	static int m_nNumAll;								//�e�N�X�`���̑���
	char *m_nTexname[MAX_TEXTURE];
};
#endif 