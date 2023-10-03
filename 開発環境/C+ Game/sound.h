//==============================================
//
//サウンド(sound.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include"main.h"

//**********************************************
// サウンド一覧
//**********************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,	// BGM0
	SOUND_LABEL_BGM001,		// BGM1
	SOUND_LABEL_MOVE,		// 走り
	SOUND_LABEL_JUMP,		// ジャンプ
	SOUND_LABEL_ATTACK,		// 攻撃
	SOUND_LABEL_HIT,		// ヒット
	SOUND_LABEL_ENEMYULT,	// 敵必殺
	SOUND_LABEL_ENEMYHIT,	// 敵ヒット
	SOUND_LABEL_ENEMYDEST,	// 敵撃破
	SOUND_LABEL_BUTTON,		// ボタン 
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//********************//
//サウンドクラスの定義//
//********************//
class CSound
{
public:	//アクセス可能

	CSound();	//コンストラクタ
	~CSound();	//デストラクタ

	//メンバ関数
	HRESULT Init(HWND hWind);				//初期処理
	void Uninit(void);						//終了処理

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private: //アクセス(メンバ関数内)

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *g_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *g_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *g_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] ;					// オーディオデータサイズ
};
#endif
