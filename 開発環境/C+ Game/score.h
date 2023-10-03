//==============================================
//
//ライフ(Score.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _SCORE_H_
#define _SCORE_H_

//マクロ定義
#define	 MAX_NUM_SCORE		(8)

#include"ui.h"

//********************//
//ライフクラスの定義//
//********************//
class CScore : public CUI
{
public:	//アクセス可能

	CScore();									//コンストラクタ
	~CScore();									//デストラクタ

	//メンバ関数
	HRESULT Init(void);							//初期処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	static void SetNum(int nScore);					//数字の設定
	static void AddNum(int nValue);					//数字の加算

	static int GetNum(void) { return m_nScore; }	//数字の取得

	void SetPosOrg(D3DXVECTOR3 pos);

	//静的メンバ関数
	static CScore *Create(void);						//メモリ生成処理

private: //アクセス(メンバ関数内)

	//静的メンバ変数
	D3DXVECTOR3 m_pos;
	static CScore	*m_apScore[MAX_NUM_SCORE];
	static int m_AgtNum;
	static int m_nScore;
	static D3DXVECTOR3 m_posTemp;
	bool m_bChange;
};

#endif
