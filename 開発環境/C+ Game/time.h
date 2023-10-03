//==============================================
//
//タイム(Time.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _TIME_H_
#define _TIME_H_

//マクロ定義
#define	 MAX_NUM_TIME		(2)

#include"ui.h"

//********************//
//タイムクラスの定義//
//********************//
class CTime : public CUI
{
public:	//アクセス可能

	CTime();									//コンストラクタ
	~CTime();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);							//初期処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	static void SetNum(int nTime);				//数字の設定
	static void AddNum(int nValue);				//数字の加算
	static int GetNum(void) { return m_nTime; }	//数字の取得

	//静的メンバ関数
	static CTime *Create(void);					//メモリ生成処理

private: //アクセス(メンバ関数内)

	//静的メンバ変数
	static CTime	*m_apTime[MAX_NUM_TIME];
	static int m_AgtNum;
	static int m_nTime;
	static int m_nTimeFlame;
};

#endif
