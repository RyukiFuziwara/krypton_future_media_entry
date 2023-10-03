//==============================================
//
//モーション(motion.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "model.h"

//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//ニュートラル
	MOTIONTYPE_MOVE,		//ダッシュ
	MOTIONTYPE_JUMP,		//ジャンプ
	MOTIONTYPE_LAND,		//着地
	MOTIONTYPE_SMASH,
	MOTIONTYPE_MAX
} MOTIONTYPE;

class CMotion
{
public:

	CMotion();
	~CMotion();

	//キー構造体
	typedef struct
	{
		float fPosX;	//位置X
		float fPosY;	//位置Y
		float fPosZ;	//位置Z
		float fRotX;	//向きX
		float fRotY;	//向きY
		float fRotZ;	//向きZ
	} KEY;

	//キー情報の構造体
	typedef struct
	{
		int nFrame;	//再生フレーム
		KEY aKey[10];	//モデルのキー要素
	} KEY_INFO;
	
	//情報構造体
	typedef struct
	{
		bool m_bLoop;
		int nNumKey;
		KEY_INFO aKeyInfo[10];	//キーの情報

	} INFO;

	//メンバ関数
	void Set(int nType);									//設定処理
	void Update(void);										//更新処理
	int GetType(void);										//タイプ取得処理
	int GetTypeTemp(void) { return m_nTypeTemp; }			//前回タイプ取得処理
	bool IsFinish(void);									//終点処理
	void SetInfo(INFO info);								//情報設定処理
	void SetModel(CModel **ppModel, int nNumModel);			//モデル設定処理

private:

	INFO m_aInfo[10];
	int m_nNumAll;
	int m_nType;
	int m_nTypeTemp;
	int m_nKey;
	int m_nCounter;
	bool m_bFinish;
	CModel **m_ppModel;
	int m_nNumModel;
};

#endif
