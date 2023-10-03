//==============================================================
//
//C+ポリゴン(main.h)
//Author: Fujiwara Ryuki
//
//==============================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION		(0x800)
#include"dinput.h"
#include<xaudio2.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//マクロ定義
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_NORMAL| D3DFVF_TEX1)

//2Dバッファの情報
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

//2Dバッファの情報
typedef struct
{
	HWND		hWnd;
}MAIN;

//3Dバッファの情報
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標

}VERTEX_3D;

void WindowMode(bool bScreen);

#endif