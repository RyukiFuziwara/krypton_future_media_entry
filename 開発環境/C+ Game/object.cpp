//==============================================
//
//オブジェクト(object.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "object.h"
#include "camera.h"
#include "manager.h"
#include "pause.h"

//静的メンバ変数宣言
CObject *CObject::m_pTop = NULL;
CObject *CObject::m_pCur = NULL;
int CObject::m_nNumAll = 0;
//==============================================
//コンストラクタ
//==============================================
CObject::CObject()
{
	if (m_pTop == NULL)
	{//先頭がNULLのとき

		//先頭として保存
		m_pTop = this;
	}
	else
	{
		//前のオブジェクトを設定
		this->m_pPrev = m_pCur;

		//次のオブジェクトを設定
		m_pCur->m_pNext = this;
	}

	//最後尾として保存
	m_pCur = this;

	m_nNumAll++;

	this->m_pNext = NULL;
}
//==============================================
//デスストラクタ
//==============================================
CObject::~CObject()
{
}
//==============================================
//オブジェクトの全解放処理
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
//オブジェクトの解放処理
//==============================================
void CObject::Release(void)
{
	CObject *pObject = this;

	if (pObject != m_pTop && pObject != m_pCur)
	{
		//前のオブジェクトの次のオブジェクトを設定する
		pObject->m_pPrev->m_pNext = pObject->m_pNext;

		//次のオブジェクトの前のオブジェクトを設定する
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	else if (pObject == m_pTop)
	{
		//次のオブジェクトを先頭にする
		m_pTop = pObject->m_pNext;
	}
	else if (pObject == m_pCur)
	{
		//前のオブジェクトを最後尾にする
		m_pCur = pObject->m_pPrev;
		m_pCur->m_pNext = NULL;
	}

	m_nNumAll--;

	//メモリ開放
	delete pObject;
	pObject = NULL;
}
//==============================================
//オブジェクトの更新処理
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
//オブジェクトの描画処理
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