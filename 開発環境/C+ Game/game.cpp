//==============================================
//
//�Q�[��(game.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"game.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"score.h"
#include"time.h"
#include"object3D.h"
#include"player.h"
#include"enemy.h"
#include"object.h"
#include"cylinder.h"
#include"block.h"
#include"file.h"
#include"actiongauge.h"
#include"opegauge.h"

#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//�ʒuY�̏����l
//==============================================
//�R���X�g���N�^
//==============================================
CGame::CGame()
{
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CGame::~CGame()
{

}
//==============================================
//�Q�[���̏���������
//==============================================
HRESULT CGame::Init(void)
{
	//�I�u�W�F�N�g�̐�������
	CObject *pObject[MAX_OBJECT] = {};											//�I�u�W�F�N�g�̃C���X�^���X�𐶐�

	pObject[0] = CObject3D::Create();											//3D�I�u�W�F�N�g��������
	pObject[1] = CCylinder::Create();											//�V�����_�[��������

	pObject[2] = CPlayer::Create();											//�v���C���[��������
	pObject[2]->SetType(CObject::TYPE_PLAYER_R);								//�v���C���[�^�C�v����

	CPlayer *pPlayer;
	pPlayer = CPlayer::Create();											//�v���C���[��������
	pPlayer->SetPos(D3DXVECTOR3(0.0f, 0.0f, 1050.0f), VECTOR_INIT);				//�ʒu�ݒ菈��
	pObject[3] = pPlayer;

	pObject[4] = CEnemy::Create();											//�G��������

	pObject[5] = CFile::ObjectLoad<CBlock>("data\\FILE\\CSV\\block.csv");		//�u���b�N��������

	CScore *pScore = CScore::Create();											//�X�R�A��������
	pScore->SetPosOrg(D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	pObject[6] = pScore;

	pObject[7] = CTime::Create();												//�^�C����������

	pObject[8] = CActiongauge::Create();										//�A�N�V�����Q�[�W��������

	COpegauge *pGauge;
	pGauge = COpegauge::Create();
	pObject[9] = pGauge;														//�A�N�V�����Q�[�W��������
	m_obj = pGauge;

	CScene::Init();

	//BGM�ݒ�
	CManager::GetSound()->PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}
//==============================================
//�Q�[���̏I������
//==============================================
void CGame::Uninit(void)
{
	CScene::Uninit();

	//�S�J������
	CObject2D::ReleaseAll();
}
//==============================================
//�Q�[���̐�������
//==============================================
CGame *CGame::Create(void)
{
	CGame *pGame;

	//����������
	pGame = new CGame;

	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}
//==============================================
//�Q�[���̍X�V����
//==============================================
void CGame::Update(void)
{
	CScene::Update();

	if (CTime::GetNum() <= 0 || CEnemy::GetFormType() == CEnemy::BOSS_FORM_MAX || m_obj->GetLife() == 0)
	{
		Uninit();

		CBlock::InitDest();

		CManager::SetMode(CScene::MODE_RESULT);

		CManager::GetSound()->StopSound();
	}
}
//==============================================
//�Q�[���̕`�揈��
//==============================================
void CGame::Draw(void)
{

}