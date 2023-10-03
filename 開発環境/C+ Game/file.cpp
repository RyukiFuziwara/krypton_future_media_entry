//==============================================
//
//CSV(csv.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"file.h"
#include"manager.h"
#include"renderer.h"

//�}�N����`
#define CODE_SCRIPT				"SCRIPT"			//�X�N���v�g�J�n
#define CODE_END_SCRIPT			"END_SCRIPT"		//�X�N���v�g�I��

//���[�V�����֌W
#define CODE_NUM_MODEL			"NUM_MODEL"			//���f����
#define CODE_MODEL_FILENAME		"MODEL_FILENAME"	//���f���̃t�@�C���p�X
#define CODE_CHARACTERSET		"CHARACTERSET"		//�L�����N�^�[���
#define CODE_END_CHARACTERSET	"END_CHARACTERSET"
//�p�[�c�ݒ�
#define CODE_PARTSSET			"PARTSSET"			//�p�[�c�ݒ�J�n
#define CODE_END_PARTSSET		"END_PARTSSET"		//�p�[�c�ݒ�I��
//���[�V�����ݒ�
#define CODE_MOTIONSET			"MOTIONSET"			//���[�V�����ݒ�J�n
#define CODE_END_MOTIONSET		"END_MOTIONSET"		//���[�V�����ݒ�I��
//�L�[�Z�b�g�ݒ�
#define CODE_KEYSET				"KEYSET"			//�L�[�Z�b�g�ݒ�J�n
#define CODE_END_KEYSET			"END_KEYSET"		//�L�[�Z�b�g�ݒ�I��
//�L�[�ݒ�
#define CODE_KEY				"KEY"				//�L�[�ݒ�J�n
#define CODE_END_KEY			"END_KEY"			//�L�[�ݒ�I��
//���[�V�����֌W
#define CODE_POS				"POS"				//�ʒu
#define CODE_ROT				"ROT"				//����
#define CODE_RADIUS				"RADIUS"			//���a
#define CODE_JUMP				"JUMP"				//�W�����v��
#define CODE_NUM_PARTS			"NUM_PARTS"			//�p�[�c��
#define CODE_INDEX				"INDEX"				//�ԍ�
#define CODE_PARENT				"PARENT"			//�e���f���̔ԍ�
#define CODE_LOOP				"LOOP"				//���[�v���邩�̐ݒ�
#define CODE_NUM_KEY			"NUM_KEY"			//�L�[��
#define CODE_FRAME				"FRAME"				//�t���[����

#define fatof(x)				(float)atof(x)

//�ǂݎ���ԗ�
typedef enum
{
	//����
	LOADSTAT_NONE = 0,	//�������ĂȂ�
	LOADSTAT_MOTIONSET,
	LOADSTAT_KEYSET,
	LOADSTAT_KEY,
	LOADSTAT_MAX
} LOADSTAT;

//==============================================
//�R���X�g���N�^
//==============================================
CFile::CFile()
{
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CFile::~CFile()
{

}
//==============================================
//�t�@�C���̏���������
//==============================================
void CFile::Input(void)
{

}
//==============================================
//�t�@�C���̏I������
//==============================================
void CFile::Output(void)
{
}
//==============================================
//TXT�̃��[�V�����Ǎ�����
//==============================================
void CFile::MotionLoad(const char*pFilename,CMotion *motion)
{
	FILE *pFile;		//�t�@�C���|�C���^��錾
	char cData[1000];	//�ꕶ�����m�F����ϐ�
	bool bLoad = false;
	LOADSTAT LoadStat = LOADSTAT_NONE;
	char *pSprit;
	int nCntMotionInfo = 0;
	int nCntKeyInfo = 0;
	int nCntKey = 0;
	CMotion::INFO Info[10];

	// �t�@�C�����J��
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		while (1)
		{
			//�t�@�C�����當���ǂݍ���
			fgets(&cData[0], 1000, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&cData[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l��NULL�ł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (cData[0] == '\t')
			{
				char cDataBackup[1000];
				strcpy(&cDataBackup[0], &cData[0]);
				strcpy(&cData[0], &cDataBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&cData[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bLoad = true;
			}
			else if (strncmp(&cData[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bLoad = false;

				break;
			}
			else if (cData[0] == EOF)
			{//EOF�̔�����

				if (feof(pFile))
				{//EOF�Ɖ���

					bLoad = false;
					break;
				}
			}
			else if (bLoad == true)
			{//�ǂݎ��

				switch (LoadStat)
				{
				case LOADSTAT_NONE:	//�����擾

					if (strncmp(&cData[0], CODE_MOTIONSET, sizeof CODE_MOTIONSET / sizeof(char) - 1) == 0)
					{
						if (nCntMotionInfo < MOTIONTYPE_MAX)
						{
							LoadStat = LOADSTAT_MOTIONSET;
						}
					}
					break;
				case LOADSTAT_MOTIONSET:
					if (strncmp(&cData[0], CODE_KEYSET, sizeof CODE_KEYSET / sizeof(char) - 1) == 0)
					{
						LoadStat = LOADSTAT_KEYSET;
					}
					else if (strncmp(&cData[0], CODE_END_MOTIONSET, sizeof CODE_END_MOTIONSET / sizeof(char) - 1) == 0)
					{
						nCntMotionInfo++;
						nCntKeyInfo = 0;
						LoadStat = LOADSTAT_NONE;
					}
					else if (strncmp(&cData[0], CODE_LOOP, sizeof CODE_LOOP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//�������e�̕�������

						//���[�v�ۓǂݎ��
						pSprit = strtok(NULL, " =\n");
								
						Info[nCntMotionInfo].m_bLoop = atoi(pSprit) == 1 ? true : false;
					}
					else if (strncmp(&cData[0], CODE_NUM_KEY, sizeof CODE_NUM_KEY / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//�������e�̕�������

						//�L�[���ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].nNumKey = atoi(pSprit);
					}
					break;
				case LOADSTAT_KEYSET:
					if (strncmp(&cData[0], CODE_KEY, sizeof CODE_KEY / sizeof(char) - 1) == 0)
					{
						LoadStat = LOADSTAT_KEY;
					}
					else if (strncmp(&cData[0], CODE_END_KEYSET, sizeof CODE_END_KEYSET / sizeof(char) - 1) == 0)
					{
						nCntKeyInfo++;
						nCntKey = 0;
						LoadStat = LOADSTAT_MOTIONSET;
					}
					else if (strncmp(&cData[0], CODE_FRAME, sizeof CODE_FRAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//�������e�̕�������

						//�t���[�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].nFrame = atoi(pSprit);
					}
					break;
				case LOADSTAT_KEY:
					if (strncmp(&cData[0], CODE_END_KEY, sizeof CODE_END_KEY / sizeof(char) - 1) == 0)
					{
						nCntKey++;
						LoadStat = LOADSTAT_KEYSET;
					}
					else if (strncmp(&cData[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fPosX = fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fPosY = fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fPosZ = fatof(pSprit);
					}
					else if (strncmp(&cData[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&cData[0], " =\n");	//�������e�̕�������

															//X�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fRotX = fatof(pSprit);

						//Y�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fRotY = fatof(pSprit);

						//Z�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						Info[nCntMotionInfo].aKeyInfo[nCntKeyInfo].aKey[nCntKey].fRotZ = fatof(pSprit);
					}
					break;
				}
			}

		}

		for (int nCntInfo = 0; nCntInfo <= nCntMotionInfo; nCntInfo++)
		{
			motion->SetInfo(Info[nCntInfo]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}
//==============================================
//TXT�̃����L���O�Ǎ�����
//==============================================
void CFile::RankingLoad(const char*pFilename, int nScore[3])
{
	FILE *pFile;		//�t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(pFilename, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		//�t�@�C������f�[�^����ǂݍ���
		fread(&nScore[0], sizeof(int), 3, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}
//==============================================
//TXT�̃����L���O��������
//==============================================
void CFile::RankingSave(const char*pFilename, int nScore[3])
{
	FILE *pFile;		//�t�@�C���|�C���^��錾

	// �t�@�C�����J��
	pFile = fopen(pFilename, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�t�@�C������f�[�^����ǂݍ���
		fwrite(&nScore[0], sizeof(int), 3, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}