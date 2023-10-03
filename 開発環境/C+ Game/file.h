//==============================================
//
//�t�@�C���֌W(file.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _FILE_H_
#define _FILE_H_

#include"main.h"
#include"object.h"
#include"motion.h"

//************************//
//	�G�̍U���N���X�̒�`�@//
//************************//
class CFile
{
public:	//�A�N�Z�X�\

	CFile();														//�R���X�g���N�^
	~CFile();														//�f�X�g���N�^

	//�����o�֐�
	void Input(void);												//���͏���
	void Output(void);												//��������
	template<class T> static T *ObjectLoad(const char*pFilename);	//�I�u�W�F�N�g�Ǎ�����
	static void MotionLoad(const char*pFilename, CMotion *motion);	//���[�V�����Ǎ�����
	static void RankingLoad(const char*pFilename, int nScore[3]);		//�����L���O�Ǎ�����
	static void RankingSave(const char*pFilename, int nScore[3]);		//�����L���O�Ǎ�����

private: //�A�N�Z�X(�����o�֐���)
};

//==============================================
//CSV�̃I�u�W�F�N�g�Ǎ�����
//==============================================
template<class T> T *CFile::ObjectLoad(const char*pFilename)
{
	int c = 0;			//�ꕶ�����m�F����ϐ�
	int column = 1;		//�񐔂𐔂���ϐ�
	int line = 0;		//�s���𐔂��鏈��
	char aData[1000];	//�Ȃ��镶����
	FILE *pFile;		//�t�@�C���|�C���^��錾

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;

	memset(aData, 0, sizeof(aData));

	// �t�@�C�����J��
	pFile = fopen(pFilename, "r");

	T *obj[100];

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		//�t�@�C������ꕶ���ǂݍ���
		while (fgetc(pFile) != '\n');

		while (c != EOF)
		{
			//1�Z�����̕���������
			while (1)
			{
				c = fgetc(pFile);

				//�����Ȃ烋�[�v�𔲂���
				if (c == EOF)
				{
					break;
				}

				//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
				if (c != ',' && c != '\n')
				{
					strcat(aData, (const char*)&c);
				}
				//�J���}�����s�Ȃ烋�[�v�𔲂���
				else
				{
					break;
				}
			}

			switch (column)
			{
				//atoi�֐��Ő��l�Ƃ��đ��
			case 1: pos.x = (float)(atoi(aData));	break;	//X�ʒu
			case 2: pos.y = (float)(atoi(aData));	break;	//Y�ʒu
			case 3: pos.z = (float)(atoi(aData));	break;	//Z�ʒu
			case 4: rot.x = (float)(atoi(aData));	break;	//X�p�x
			case 5: rot.y = (float)(atoi(aData));	break;	//Y�p�x
			case 6: rot.z = (float)(atoi(aData));	break;	//Z�p�x
			case 7:	scale.x = (float)(atoi(aData));	break;	//X��
			case 8:	scale.y = (float)(atoi(aData));	break;	//Y��
			case 9: scale.z = (float)(atoi(aData));	break;	//Z��
			}
			//�o�b�t�@��������
			memset(aData, 0, sizeof(aData));

			//�񐔂𑫂�
			column++;

			//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
			if (c == '\n')
			{
				obj[line] = T::Create();

				obj[line]->SetPos(pos,scale);				//�ʒu���ݒ�
				obj[line]->SetRot(rot * 0.001f);			//�p�x�ݒ�

				column = 1;
				line++;
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	return obj[0];
}
#endif