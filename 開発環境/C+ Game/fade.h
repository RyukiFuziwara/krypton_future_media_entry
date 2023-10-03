//==============================================
//
//フェード(fade.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _FADE_H_
#define _FADE_H_

#include"manager.h"
#include"object2d.h"

//******************//
//フェードのクラス定義//
//******************//
class CFade : public CObject2D
{
public: //アクセス可能

	//フェードの状態
	; typedef enum
	{
		FADE_NONE = 0,	//何もしていない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//フェードアウト状態
		FADE_MAX

	}FADE;

	CFade();							//コンストラクタ
	~CFade();					//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理

	static void SetFade(FADE fade) { m_fade = fade; }
	static bool GetbNext(void) { return m_bNext; }

private: //アクセス(メンバ関数内)

	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffer;			//バッファへのポインタ
	D3DXVECTOR3					m_pos;					//位置
	D3DXVECTOR2					m_tex;
	static FADE					m_fade;
	D3DXCOLOR					m_colFade;
	static bool					m_bNext;
};

#endif 