//==============================================
//
//���U���g(result.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "result.h"
#include "Input.h"
#include "texture.h"
#include "score.h"
#include "file.h"
#include "manager.h"
#include "sound.h"

#define MAX_2DOBJECT	(8)									//2D�|���S���̍ő吔
#define MAX_RANKING		(3)									//�����L���O�̐�
#define RESULT_UI_SCALE	(D3DXVECTOR3(250.0f, 90.0f, 0.0f))	//���U���gUI
#define NUM_UI_SCALE	(D3DXVECTOR3(50.0f, 50.0f, 0.0f))	//����UI
#define FRAME_UI_SCALE	(D3DXVECTOR3(190.0f, 200.0f, 0.0f))	//�t���[��UI
#define RANK_UI_SCALE	(D3DXVECTOR3(150.0f, 70.0f, 0.0f))	//�X�R�A�����NUI
#define YOUR_UI_SCALE	(D3DXVECTOR3(170.0f, 70.0f, 0.0f))	//����̃X�R�AUI
#define SCORE_UI_SCALE	(D3DXVECTOR3(940.0f,440.0f,0.0f))	//����̃X�R�A
#define RANK_SORT		(4)									//�\�[�g��
//==============================================
//�R���X�g���N�^
//==============================================
CResult::CResult()
{
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CResult::~CResult()
{

}
//==============================================
//���U���g�̏���������
//==============================================
HRESULT CResult::Init(void)
{
	//�e�N�X�`���ݒ�
	CTexture *pTexture = CManager::GetTexture();

	//�C���X�^���X����
	Obj2D = new CObject2D;

	if (Obj2D != NULL)
	{
		//�e�ݒ�
		Obj2D = CObject2D::Create();
		Obj2D->Init();
		Obj2D->SetPos(D3DXVECTOR3(640.0f, 100.0f, 0.0f), RESULT_UI_SCALE);
		Obj2D->BindTexture(pTexture->GetAddress(1));
	}

	//�I�u�W�F�N�g�̐�������
	CObject2D *pObject2D[MAX_2DOBJECT] = {};	//�I�u�W�F�N�g�̃C���X�^���X�𐶐�

	pObject2D[0] = CObject2D::Create();			//�gUI
	pObject2D[0]->SetPos(D3DXVECTOR3(240.0f, 440.0f, 0.0f), FRAME_UI_SCALE);
	pObject2D[0]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_FLAME));

	pObject2D[1] = CObject2D::Create();			//�gUI
	pObject2D[1]->SetPos(D3DXVECTOR3(1040.0f, 440.0f, 0.0f), FRAME_UI_SCALE);
	pObject2D[1]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_FLAME));

	pObject2D[2] = CObject2D::Create();			//�����L���OUI
	pObject2D[2]->SetPos(D3DXVECTOR3(240.0f, 200.0f, 0.0f), RANK_UI_SCALE);
	pObject2D[2]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_RANKING));

	pObject2D[3] = CObject2D::Create();			//����̃X�R�AUI
	pObject2D[3]->SetPos(D3DXVECTOR3(1040.0f, 200.0f, 0.0f), YOUR_UI_SCALE);
	pObject2D[3]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_YOURSCORE));
	
	pObject2D[4] = CObject2D::Create();			//����̃��C�tUI
	pObject2D[4]->SetPos(D3DXVECTOR3(110.0f, 340.0f, 0.0f), NUM_UI_SCALE);
	pObject2D[4]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_FIRST));

	pObject2D[5] = CObject2D::Create();			//����̃��C�tUI
	pObject2D[5]->SetPos(D3DXVECTOR3(110.0f, 440.0f, 0.0f), NUM_UI_SCALE);
	pObject2D[5]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_SECOND));

	pObject2D[6] = CObject2D::Create();			//����̃��C�tUI
	pObject2D[6]->SetPos(D3DXVECTOR3(110.0f, 540.0f, 0.0f), NUM_UI_SCALE);
	pObject2D[6]->BindTexture(pTexture->GetAddress(CTexture::TEXTURE_THIRD));

	int nScore = CScore::GetNum();
	CScore *pScore = CScore::Create();
	pScore->SetNum(nScore);
	pScore->SetPosOrg(SCORE_UI_SCALE);
	pObject2D[7] = pScore;

	RankSort(nScore);
	
	return S_OK;
}
//==============================================
//���U���g�̏I������
//==============================================
void CResult::Uninit(void)
{
	CObject::ReleaseAll();
}
//==============================================
//���U���g�̐�������
//==============================================
CResult *CResult::Create(void)
{
	CResult *pResult;

	//����������
	pResult = new CResult;

	if (pResult != NULL)
	{
		pResult->Init();
	}

	return pResult;
}
//==============================================
//���U���g�̍X�V����
//==============================================
void CResult::Update(void)
{
	//�L�[�{�[�h�̏����擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();
	CInputKeyPad *pInputKeyPad = CManager::GetInputKeyPad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputKeyPad->GetTrigger(CInputKeyPad::JOYKEY_A) == true)
	{//ENTER�L�[����������

		//BGM�ݒ�
		CManager::GetSound()->PlaySound(SOUND_LABEL_BUTTON);

		Uninit();

		CManager::SetMode(CScene::MODE_TITLE);
	}
}
//==============================================
//���U���g�̕`�揈��
//==============================================
void CResult::Draw(void)
{
	if (Obj2D != NULL)
	{
		Obj2D->Draw();
	}
}
//==============================================
//���U���g�̃����L���O�\�[�g
//==============================================
void CResult::RankSort(int nScore)
{
	int nScoreRank[4];

	bool bChange = false;

	nScoreRank[3] = nScore;

	CFile::RankingLoad("data\\FILE\\BIN\\ranking.bin",&nScoreRank[0]);

	//�\�[�g�̏���
	for (int nCount1 = 0; nCount1 < 4 - 1; nCount1++)
	{
		//���ёւ�������
		for (int nCount2 = nCount1 + 1; nCount2 < 4; nCount2++)
		{
			if (nScoreRank[nCount2] > nScoreRank[nCount1])
			{
				//���݂̔�r���Ă��鐔��ۑ�
				int nMax = nScoreRank[nCount1];

				//�ő�l�ɒu��������
				nScoreRank[nCount1] = nScoreRank[nCount2];

				//�ύX�������l�����ɖ߂�
				nScoreRank[nCount2] = nMax;

				bChange = true;
			}
		}
	}

	CScore *pScore[MAX_RANKING];

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		pScore[nCnt] = CScore::Create();

		pScore[nCnt]->SetNum(nScoreRank[nCnt]);

		pScore[nCnt]->SetPosOrg(D3DXVECTOR3(170.0f, 340.0f + (nCnt * 100.0f), 0.0f));
	}

	if (bChange == true)
	{
		CFile::RankingSave("data\\FILE\\BIN\\ranking.bin", &nScoreRank[0]);
	}
}