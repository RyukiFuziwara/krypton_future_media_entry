//==============================================
//
//モーション(motion.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"motion.h"
#include"file.h"

//==============================================
//コンストラクタ
//==============================================
CMotion::CMotion()
{
	m_nNumModel = 0;
	m_nNumAll	= 0;
	m_nType		= 0;
	m_nKey		= 0;
	m_nCounter	= 0;

	m_bFinish = false;

	m_ppModel = NULL;
}
//==============================================
//デスストラクタ
//==============================================
CMotion::~CMotion()
{

}
//==============================================
//モーションの設定処理
//==============================================
void CMotion::Set(int nType)
{
	//前回モーション型の保存
	m_nTypeTemp = m_nType;

	if(m_aInfo[m_nTypeTemp].m_bLoop == false)
	{//ループしないモーションの時

		if (m_bFinish == true)
		{//モーションが終わったとき

			//今回のモーションを設定
			m_nType = nType;
		
			//初期化
			m_nCounter = 0;
			m_nKey = 0;
			m_bFinish = false;
		}
	}
	else if (nType != m_nTypeTemp)
	{//前回のモーションと違うモーションのとき

		//今回のモーションを設定
		m_nType = nType;

		//初期化
		m_nCounter = 0;
		m_nKey = 0;
		m_bFinish = false;
	}
}
//==============================================
//モーションの更新処理
//==============================================
void CMotion::Update(void)
{	
	if (m_bFinish == false)
	{
		int NextKey = (m_nKey + 1)% m_aInfo[m_nType].nNumKey;
		float fParFlame = ((float)m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame);

		for (int nCntModel = 0; nCntModel< m_nNumModel; nCntModel++)
		{
			//差分算出
			float posDiffX = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fPosX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			float posDiffY = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fPosY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			float posDiffZ = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fPosZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;
			float rotDiffX = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fRotX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			float rotDiffY = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fRotY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			float rotDiffZ = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fRotZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			//位置向き算出
			float posDemandX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX + posDiffX * fParFlame;
			float posDemandY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY + posDiffY * fParFlame;
			float posDemandZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ + posDiffZ * fParFlame;
			float rotDemandX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX + rotDiffX * fParFlame;
			float rotDemandY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY + rotDiffY * fParFlame;
			float rotDemandZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ + rotDiffZ * fParFlame;

			//位置角度設定
			m_ppModel[nCntModel]->SetPos(D3DXVECTOR3(posDemandX, posDemandY, posDemandZ));
			m_ppModel[nCntModel]->SetRot(D3DXVECTOR3(rotDemandX, rotDemandY + m_ppModel[nCntModel]->GetDirection(), rotDemandZ));
		}

		m_nCounter++;

		if (m_nCounter == m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)
		{//モーションが一周したとき

			m_nCounter = 0;
			m_nKey++;

			if (m_nKey == m_aInfo[m_nType].nNumKey)
			{//キーの総数に到達

				if (m_aInfo[m_nType].m_bLoop == true)
				{//モーションをループさせるとき

					//初期化
					m_nKey = 0;
				}
				else
				{
					//初期化
					m_nKey = 0;

					//モーションが終わった
					m_bFinish = true;
				}
			}
		}
	}
}
//==============================================
//モーションのタイプ取得処理
//==============================================
int CMotion::GetType(void)
{
	return m_nType;
}
//==============================================
//モーションの終点処理
//==============================================
bool CMotion::IsFinish(void)
{
	return m_bFinish;
}
//==============================================
//モーションの情報設定処理
//==============================================
void CMotion::SetInfo(INFO info)
{
	m_aInfo[m_nNumAll] = info;

	m_nNumAll++;
}
//==============================================
//モーションのモデル設定処理
//==============================================
void CMotion::SetModel(CModel **ppModel, int nNumModel)
{
	m_ppModel = ppModel;

	m_nNumModel = nNumModel;
}