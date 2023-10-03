//==============================================
//
//�J����(camera.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

//****************//
//�J�����̃N���X��`//
//****************//
class CCamera
{
public: //�A�N�Z�X�\

	CCamera();							//�R���X�g���N�^
	virtual ~CCamera();					//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void SetCamera(void);

private: //�A�N�Z�X(�����o�֐���)

	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_posU;				//������x�N�g��
	D3DXMATRIX  m_mtxView;			//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;				//����
	D3DXVECTOR3 m_rotPlayR;			//����
	D3DXVECTOR3 m_rotPlay;			//����
	D3DXVECTOR3 m_posPlayR;			//����
	D3DXVECTOR3 m_posPlay;			//����
	D3DXVECTOR3 m_spin;				//��]
	D3DXMATRIX  m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	int			m_nCounter;
	
};
#endif 
