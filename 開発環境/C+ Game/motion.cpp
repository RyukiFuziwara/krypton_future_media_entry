//==============================================
//
//���[�V����(motion.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"motion.h"
#include"file.h"

//==============================================
//�R���X�g���N�^
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
//�f�X�X�g���N�^
//==============================================
CMotion::~CMotion()
{

}
//==============================================
//���[�V�����̐ݒ菈��
//==============================================
void CMotion::Set(int nType)
{
	//�O�񃂁[�V�����^�̕ۑ�
	m_nTypeTemp = m_nType;

	if(m_aInfo[m_nTypeTemp].m_bLoop == false)
	{//���[�v���Ȃ����[�V�����̎�

		if (m_bFinish == true)
		{//���[�V�������I������Ƃ�

			//����̃��[�V������ݒ�
			m_nType = nType;
		
			//������
			m_nCounter = 0;
			m_nKey = 0;
			m_bFinish = false;
		}
	}
	else if (nType != m_nTypeTemp)
	{//�O��̃��[�V�����ƈႤ���[�V�����̂Ƃ�

		//����̃��[�V������ݒ�
		m_nType = nType;

		//������
		m_nCounter = 0;
		m_nKey = 0;
		m_bFinish = false;
	}
}
//==============================================
//���[�V�����̍X�V����
//==============================================
void CMotion::Update(void)
{	
	if (m_bFinish == false)
	{
		int NextKey = (m_nKey + 1)% m_aInfo[m_nType].nNumKey;
		float fParFlame = ((float)m_nCounter / m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame);

		for (int nCntModel = 0; nCntModel< m_nNumModel; nCntModel++)
		{
			//�����Z�o
			float posDiffX = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fPosX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			float posDiffY = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fPosY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			float posDiffZ = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fPosZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;
			float rotDiffX = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fRotX - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			float rotDiffY = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fRotY - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			float rotDiffZ = m_aInfo[m_nType].aKeyInfo[NextKey].aKey[nCntModel].fRotZ - m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			//�ʒu�����Z�o
			float posDemandX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX + posDiffX * fParFlame;
			float posDemandY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY + posDiffY * fParFlame;
			float posDemandZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ + posDiffZ * fParFlame;
			float rotDemandX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX + rotDiffX * fParFlame;
			float rotDemandY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY + rotDiffY * fParFlame;
			float rotDemandZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ + rotDiffZ * fParFlame;

			//�ʒu�p�x�ݒ�
			m_ppModel[nCntModel]->SetPos(D3DXVECTOR3(posDemandX, posDemandY, posDemandZ));
			m_ppModel[nCntModel]->SetRot(D3DXVECTOR3(rotDemandX, rotDemandY + m_ppModel[nCntModel]->GetDirection(), rotDemandZ));
		}

		m_nCounter++;

		if (m_nCounter == m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)
		{//���[�V��������������Ƃ�

			m_nCounter = 0;
			m_nKey++;

			if (m_nKey == m_aInfo[m_nType].nNumKey)
			{//�L�[�̑����ɓ��B

				if (m_aInfo[m_nType].m_bLoop == true)
				{//���[�V���������[�v������Ƃ�

					//������
					m_nKey = 0;
				}
				else
				{
					//������
					m_nKey = 0;

					//���[�V�������I�����
					m_bFinish = true;
				}
			}
		}
	}
}
//==============================================
//���[�V�����̃^�C�v�擾����
//==============================================
int CMotion::GetType(void)
{
	return m_nType;
}
//==============================================
//���[�V�����̏I�_����
//==============================================
bool CMotion::IsFinish(void)
{
	return m_bFinish;
}
//==============================================
//���[�V�����̏��ݒ菈��
//==============================================
void CMotion::SetInfo(INFO info)
{
	m_aInfo[m_nNumAll] = info;

	m_nNumAll++;
}
//==============================================
//���[�V�����̃��f���ݒ菈��
//==============================================
void CMotion::SetModel(CModel **ppModel, int nNumModel)
{
	m_ppModel = ppModel;

	m_nNumModel = nNumModel;
}