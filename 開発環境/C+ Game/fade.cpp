//==============================================
//
//フェード(fade.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "fade.h"

CFade::FADE CFade::m_fade = CFade::FADE_NONE;
bool CFade::m_bNext = false;
//==============================================
//コンストラクタ
//==============================================
CFade::CFade()
{
	m_colFade = D3DXCOLOR(0.0f, 0.0f, 0.0f,1.0f);
}
//==============================================
//デスストラクタ
//==============================================
CFade::~CFade()
{

}
//==============================================
//フェードの初期化処理
//==============================================
HRESULT CFade::Init(void)
{
	CObject2D::Init();

	m_fade = FADE_IN;		//フェードイン状態に

	m_bNext = false;

	SetCol(m_colFade,0.0f);	//黒いポリゴン(不透明)にしておく

	return S_OK;
}
//==============================================
//フェードの終了処理
//==============================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}
//==============================================
//フェードの更新処理
//==============================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//フェードイン状態
			m_colFade.a -= 0.03f; //ポリゴンを透明にしていく

			if (m_colFade.a <= 0.0f)
			{
				m_colFade.a = 0.0f;
				m_fade = FADE_NONE;	//何もしていない状態に
			}
		}
		else if (m_fade == FADE_OUT)
		{//フェードアウト状態
			m_colFade.a += 0.03f;

			if (m_colFade.a >= 1.0f)
			{
				m_colFade.a = 1.0f;
				m_bNext = true;
			}
		}

		SetCol(m_colFade, 0.0f);
	}
}
//==============================================
//フェードの描画処理
//==============================================
void CFade::Draw(void)
{
	if (m_fade != FADE_NONE)
	{
		CObject2D::Draw();
	}
}