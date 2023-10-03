//==============================================
//
//�J����(camera.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "camera.h"
#include"manager.h"
#include"renderer.h"
#include"player.h"
#include"object.h"
#include"object3D.h"

#define POS_V			(D3DXVECTOR3(0.0f, 100.0f, -200.0f))	//�X�R�A�����NUI
#define POS_R			(D3DXVECTOR3(0.0f, 100.0f, 0.0f))			//����̃X�R�AUI
#define TITLE_CAMERA	(0.01f)									//�^�C�g���J����
#define CORRECT_V		(500.0f)								//�����_�␳
//==============================================
//�R���X�g���N�^
//==============================================
CCamera::CCamera()
{
	//������
	 m_posV = POS_V;							//���_
	 m_posR = POS_R;							//�����_
	 m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//������x�N�g��
	 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	 m_nCounter = 1;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CCamera::~CCamera()
{

}
//==============================================
//�J��������������
//==============================================
HRESULT CCamera::Init(void)
{
	//������
	m_posV = POS_V;		//���_
	m_posR = POS_R;		//�����_

	return S_OK;
}
//==============================================
//�J�����I������
//==============================================
void CCamera::Uninit(void)
{
	
}
//==============================================
//�J�����X�V����
//==============================================
void CCamera::Update(void)
{
	if (CScene::GetMode() == CScene::MODE_TITLE)
	{
		m_rot.y += TITLE_CAMERA;

		m_posR.x += sinf(m_rot.y);
		m_posR.z += cosf(m_rot.y);
	}
	else
	{
		//�I�u�W�F�N�g�C���X�^���X
		CObject *pObj;

		//�^�C�v�ϐ�
		CObject::TYPE type;

		//�I�u�W�F�N�g�̐擪���擾
		pObj = CObject::GetTop();

		while (pObj != NULL)
		{//������������Ƃ�

		 //���̃I�u�W�F�N�g��ۑ����Ă���
			CObject *pObjectNext = pObj->GetNext();

			//�^�C�v�擾
			type = pObj->GetType();

			if (type == CObject::TYPE_PLAYER_R)
			{//�����_�v���C���[�̎�

			 //�I�u�W�F�N�g���v���C���[�ɃL���X�g
				CPlayer *pObjXR = dynamic_cast<CPlayer*>(pObj);

				//�I�u�W�F�N�g�̐擪���擾
				pObj = CObject::GetTop();

				while (pObj != NULL)
				{//������������Ƃ�

				 //���̃I�u�W�F�N�g��ۑ����Ă���
					CObject *pObjectNext = pObj->GetNext();

					//�^�C�v�擾
					type = pObj->GetType();

					if (type == CObject::TYPE_PLAYER)
					{//�����_�v���C���[�̎�

					 //�I�u�W�F�N�g���v���C���[�ɃL���X�g
						CPlayer *pObjX = dynamic_cast<CPlayer*>(pObj);

						//�I�u�W�F�N�g�̐擪���擾
						pObj = CObject::GetTop();

						while (pObj != NULL)
						{//������������Ƃ�
							 
							CObject *pObjectNext = pObj->GetNext();

							//�^�C�v�擾
							type = pObj->GetType();

							if (type == CObject::TYPE_STAGE)
							{//�����_�v���C���[�̎�

							 //�I�u�W�F�N�g���v���C���[�ɃL���X�g
								CObject3D *pObj3D = dynamic_cast<CObject3D*>(pObj);

								if (CPlayer::GetChange() == true)
								{
									//�e���_�̔��΂����߂�
									if (pObjXR->GetRot().y >= 0)
									{
										m_rotPlayR.y = pObjXR->GetRot().y - D3DX_PI;
									}
									else if (pObjXR->GetRot().y < 0)
									{
										m_rotPlayR.y = pObjXR->GetRot().y + D3DX_PI;
									}

									if (pObjX->GetRot().y >= 0)
									{
										m_rotPlay.y = pObjX->GetRot().y - D3DX_PI;
									}
									else if (pObjX->GetRot().y < 0)
									{
										m_rotPlay.y = pObjX->GetRot().y + D3DX_PI;
									}

									m_spin = m_rotPlayR - m_rotPlay;

									if (m_spin.y > D3DX_PI)
									{
										m_spin.y = -((D3DX_PI * 2.0f) - m_spin.y);
									}
									else if (m_spin.y < -D3DX_PI)
									{
										m_spin.y = (D3DX_PI * 2.0f) + m_spin.y;
									}

									m_nCounter = 1;
								}

								//************************************************************//
								//						�J�����Ǐ]����						  //
								//************************************************************//
								m_posR.x += (pObjXR->GetPos().x + (sinf(pObjXR->GetRot().y)) - m_posR.x) * 0.1f;
								m_posR.z += (pObjXR->GetPos().z + (cosf(pObjXR->GetRot().y)) - m_posR.z) * 0.1f;

								if (m_nCounter < 30)
								{
									m_posV.x = m_posR.x - sinf(pObjX->GetRot().y + m_spin.y * ((float)m_nCounter / 30) + D3DX_PI) * CORRECT_V;
									m_posV.z = m_posR.z - cosf(pObjX->GetRot().y + m_spin.y * ((float)m_nCounter / 30) + D3DX_PI) * CORRECT_V;

									CPlayer::SetChange(false);
									m_nCounter++;
								}
								else
								{
									m_posV.x = m_posR.x - sinf(pObjXR->GetRot().y + D3DX_PI) * CORRECT_V;
									m_posV.z = m_posR.z - cosf(pObjXR->GetRot().y + D3DX_PI) * CORRECT_V;
								}

								break;
							}

							//���̃I�u�W�F�N�g�ɂ���
							pObj = pObjectNext;
						}
					}

					//���̃I�u�W�F�N�g�ɂ���
					pObj = pObjectNext;
				}
			}

			//���̃I�u�W�F�N�g�ɂ���
			pObj = pObjectNext;
		}
	}
}
//==============================================
//�J�����`�揈��
//==============================================
void CCamera::SetCamera()
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		6000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}