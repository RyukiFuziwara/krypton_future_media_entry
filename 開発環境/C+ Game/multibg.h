//==============================================
//
//���d�w�i(multibg.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MULTIBG_H_
#define _MULTIBG_H_

//�}�N����`
#define	 MAX_BG		(3)

#include"object2D.h"

//**************************//
//2D�I�u�W�F�N�g�N���X�̒�`//
//**************************//
class CMultibg : public CObject
{
public:	//�A�N�Z�X�\

	CMultibg();											//�R���X�g���N�^
	~CMultibg();										//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);									//��������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	//�ʒu�ݒ菈��
	void SetTex(D3DXVECTOR2 tex);						//�e�N�X�`�����W�ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }			//�ʒu�擾����
	D3DXVECTOR3 GetScale(void) { return m_scale; }		//�傫���擾����

	static CMultibg *CMultibg::Create(void);

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	static CObject2D			*m_apObject2D[MAX_BG];

	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffer;			//�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;					//�ʒu
	D3DXVECTOR3					m_move;					//�ړ���
	D3DXVECTOR3					m_scale;				//�傫��
	D3DXVECTOR2					m_tex[MAX_BG];


	static char *m_aTexName[MAX_BG];
};

#endif
