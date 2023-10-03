//==============================================
//
//ゲーム(game.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _GAME_H_
#define _GAME_H_

#include"manager.h"

class COpegauge;
//******************//
//ゲームのクラス定義//
//******************//
class CGame : public CScene
{
public: //アクセス可能

	CGame();							//コンストラクタ
	virtual ~CGame();					//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理

	//静的メンバ関数
	static CGame *Create(void);						//メモリ生成処理

private: //アクセス(メンバ関数内)

	COpegauge *m_obj;
};

#endif 

