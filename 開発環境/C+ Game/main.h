//==============================================================
//
//C+�|���S��(main.h)
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

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//�}�N����`
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE |D3DFVF_NORMAL| D3DFVF_TEX1)

//2D�o�b�t�@�̏��
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

//2D�o�b�t�@�̏��
typedef struct
{
	HWND		hWnd;
}MAIN;

//3D�o�b�t�@�̏��
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W

}VERTEX_3D;

void WindowMode(bool bScreen);

#endif