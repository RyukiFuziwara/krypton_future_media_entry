//==============================================
//
//���C�t(Score.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _SCORE_H_
#define _SCORE_H_

//�}�N����`
#define	 MAX_NUM_SCORE		(8)

#include"ui.h"

//********************//
//���C�t�N���X�̒�`//
//********************//
class CScore : public CUI
{
public:	//�A�N�Z�X�\

	CScore();									//�R���X�g���N�^
	~CScore();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);							//��������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	static void SetNum(int nScore);					//�����̐ݒ�
	static void AddNum(int nValue);					//�����̉��Z

	static int GetNum(void) { return m_nScore; }	//�����̎擾

	void SetPosOrg(D3DXVECTOR3 pos);

	//�ÓI�����o�֐�
	static CScore *Create(void);						//��������������

private: //�A�N�Z�X(�����o�֐���)

	//�ÓI�����o�ϐ�
	D3DXVECTOR3 m_pos;
	static CScore	*m_apScore[MAX_NUM_SCORE];
	static int m_AgtNum;
	static int m_nScore;
	static D3DXVECTOR3 m_posTemp;
	bool m_bChange;
};

#endif
