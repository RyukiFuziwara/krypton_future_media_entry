//==============================================
//
//カメラ(camera.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

//****************//
//カメラのクラス定義//
//****************//
class CCamera
{
public: //アクセス可能

	CCamera();							//コンストラクタ
	virtual ~CCamera();					//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void SetCamera(void);

private: //アクセス(メンバ関数内)

	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注視点
	D3DXVECTOR3 m_posU;				//上方向ベクトル
	D3DXMATRIX  m_mtxView;			//ビューマトリックス
	D3DXVECTOR3 m_rot;				//向き
	D3DXVECTOR3 m_rotPlayR;			//向き
	D3DXVECTOR3 m_rotPlay;			//向き
	D3DXVECTOR3 m_posPlayR;			//向き
	D3DXVECTOR3 m_posPlay;			//向き
	D3DXVECTOR3 m_spin;				//回転
	D3DXMATRIX  m_mtxProjection;	//プロジェクションマトリックス
	int			m_nCounter;
	
};
#endif 
