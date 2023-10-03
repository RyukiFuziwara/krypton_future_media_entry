//==============================================
//
//オブジェクト(object.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include"d3dx9.h"

#define SCALE_INIT		(D3DXVECTOR3(20.0f,20.0f,0.0f))		//大小の初期値
#define POS_INIT		(D3DXVECTOR3(640.0f,360.0f, 0.0f))	//位置Xの初期値

#define MAX_ANIMATION	(8)									//アニメーション最大数
#define MAX_OBJECT		(8192)								//オブジェクトの最大数

//********************//
//レンダークラスの定義//
//********************//
class CObject
{
public:	//アクセス可能

	CObject();			//コンストラクタ
	virtual ~CObject();	//デストラクタ

	//タイプ情報
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_PLAYER_R,
		TYPE_ENEMY,
		TYPE_ENEMY_BOSS,
		TYPE_BLOCK,
		TYPE_ROCK,
		TYPE_BULLET_ENEMY,
		TYPE_EXPLOSION,
		TYPE_SCORE,
		TYPE_TIME,
		TYPE_LIFE,
		TYPE_GAUGE,
		TYPE_EFFECT,
		TYPE_PARTICLE,
		TYPE_OBJX,
		TYPE_STAGE,
		TYPE_WALL,
		TYPE_PAUSE,
		TYPE_MAX
	}TYPE;

	//メンバ関数(純粋仮想)
	virtual HRESULT Init(void) = 0;										//初期処理
	virtual void Uninit(void) = 0;										//終了処理
	virtual void Update(void) = 0;										//更新処理
	virtual void Draw(void) = 0;										//描画処理


	void SetType(TYPE type) { m_type = type; }
	TYPE GetType(void) { return m_type; }

	//静的メンバ関数
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	static CObject *GetTop(void) { return m_pTop; }
	CObject *GetNext(void) { return m_pNext; }
	CObject *GetPrev(void) { return m_pPrev; }

protected://アクセス(派生クラスも可能)

	void Release(void);

private: //アクセス(メンバ関数内)

	static int m_nNumAll;

	TYPE m_type;

	static CObject *m_pTop;
	static CObject *m_pCur;

	CObject *m_pPrev;
	CObject *m_pNext;
};

#endif
