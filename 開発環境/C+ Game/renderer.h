//==============================================
//
//�����_���[(renderer.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include"d3dx9.h"

//********************//
//�����_�[�N���X�̒�`//
//********************//
class CRenderer
{
public:	//�A�N�Z�X�\

	CRenderer();	//�R���X�g���N�^
	~CRenderer();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HWND hWind,BOOL bWindow);					//��������
	void Uninit(void);										//�I������
	void Update(void);										//�X�V����
	void Draw(void);										//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//�f�o�C�X�̎擾
	void SetFPS(int nCount) { m_nCountFPS = nCount; }
	void DrawFPS();

private: //�A�N�Z�X(�����o�֐���)

	//�����o�ϐ�
	LPDIRECT3D9				m_pD3D;			//DirectX3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_pD3DDevice;	//Direct3D�f�o�C�X�ւ̃|�C���^
	LPD3DXFONT	m_pFont;
	int m_nCountFPS;
};
#endif