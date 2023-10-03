//==============================================
//
//レンダラー(renderer.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include"d3dx9.h"

//********************//
//レンダークラスの定義//
//********************//
class CRenderer
{
public:	//アクセス可能

	CRenderer();	//コンストラクタ
	~CRenderer();	//デストラクタ

	//メンバ関数
	HRESULT Init(HWND hWind,BOOL bWindow);					//初期処理
	void Uninit(void);										//終了処理
	void Update(void);										//更新処理
	void Draw(void);										//描画処理
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//デバイスの取得
	void SetFPS(int nCount) { m_nCountFPS = nCount; }
	void DrawFPS();

private: //アクセス(メンバ関数内)

	//メンバ変数
	LPDIRECT3D9				m_pD3D;			//DirectX3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9		m_pD3DDevice;	//Direct3Dデバイスへのポインタ
	LPD3DXFONT	m_pFont;
	int m_nCountFPS;
};
#endif