//==============================================
//
//�I�u�W�F�N�g(object.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "pause.h"

//�ÓI�����o�ϐ��錾
CObject *CObject::m_pTop = NULL;
CObject *CObject::m_pCur = NULL;
int CObject::m_nNumAll = 0;
//==============================================
//�R���X�g���N�^
//==============================================
CObject::CObject()
{
	if (m_pTop == NULL)
	{//�擪��NULL�̂Ƃ�

		//�擪�Ƃ��ĕۑ�
		m_pTop = this;
	}
	else
	{
		//�O�̃I�u�W�F�N�g��ݒ�
		this->m_pPrev = m_pCur;

		//���̃I�u�W�F�N�g��ݒ�
		m_pCur->m_pNext = this;
	}

	//�Ō���Ƃ��ĕۑ�
	m_pCur = this;

	m_nNumAll++;

	this->m_pNext = NULL;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CObject::~CObject()
{
}
//==============================================
//�I�u�W�F�N�g�̑S�������
//==============================================
void CObject::ReleaseAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject != NULL)
	{
		CObject *pObjectNext = pObject->m_pNext;

		pObject->Uninit();

		pObject = pObjectNext;
	}
}
//==============================================
//�I�u�W�F�N�g�̉������
//==============================================
void CObject::Release(void)
{
	CObject *pObject = this;

	if (pObject != m_pTop && pObject != m_pCur)
	{
		//�O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g��ݒ肷��
		pObject->m_pPrev->m_pNext = pObject->m_pNext;

		//���̃I�u�W�F�N�g�̑O�̃I�u�W�F�N�g��ݒ肷��
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	else if (pObject == m_pTop)
	{
		//���̃I�u�W�F�N�g��擪�ɂ���
		m_pTop = pObject->m_pNext;
	}
	else if (pObject == m_pCur)
	{
		//�O�̃I�u�W�F�N�g���Ō���ɂ���
		m_pCur = pObject->m_pPrev;
		m_pCur->m_pNext = NULL;
	}

	m_nNumAll--;

	//�������J��
	delete pObject;
	pObject = NULL;
}
//==============================================
//�I�u�W�F�N�g�̍X�V����
//==============================================
void CObject::UpdateAll(void)
{
	CObject *pObject = m_pTop;

	while (pObject != NULL)
	{
		CObject *pObjectNext = pObject->m_pNext;

		if (CPause::GetPause() == false)
		{
			pObject->Update();
		}

		pObject = pObjectNext;	
	}
}
//==============================================
//�I�u�W�F�N�g�̕`�揈��
//==============================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();

	pCamera->SetCamera();

	CObject *pObject = m_pTop;

	while (pObject != NULL)
	{
		CObject *pObjectNext = pObject->m_pNext;

		if (pObject->GetType() != TYPE_PAUSE || CPause::GetPause() == true)
		{
			pObject->Draw();	
		}

		pObject = pObjectNext;
	}
}