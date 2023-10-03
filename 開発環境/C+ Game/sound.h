//==============================================
//
//�T�E���h(sound.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include"main.h"

//**********************************************
// �T�E���h�ꗗ
//**********************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,	// BGM0
	SOUND_LABEL_BGM001,		// BGM1
	SOUND_LABEL_MOVE,		// ����
	SOUND_LABEL_JUMP,		// �W�����v
	SOUND_LABEL_ATTACK,		// �U��
	SOUND_LABEL_HIT,		// �q�b�g
	SOUND_LABEL_ENEMYULT,	// �G�K�E
	SOUND_LABEL_ENEMYHIT,	// �G�q�b�g
	SOUND_LABEL_ENEMYDEST,	// �G���j
	SOUND_LABEL_BUTTON,		// �{�^�� 
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//********************//
//�T�E���h�N���X�̒�`//
//********************//
class CSound
{
public:	//�A�N�Z�X�\

	CSound();	//�R���X�g���N�^
	~CSound();	//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HWND hWind);				//��������
	void Uninit(void);						//�I������

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private: //�A�N�Z�X(�����o�֐���)

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *g_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *g_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *g_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] ;					// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif
