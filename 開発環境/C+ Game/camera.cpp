//==============================================
//
//カメラ(camera.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include "camera.h"
#include"manager.h"
#include"renderer.h"
#include"player.h"
#include"object.h"
#include"object3D.h"

#define POS_V			(D3DXVECTOR3(0.0f, 100.0f, -200.0f))	//スコアランクUI
#define POS_R			(D3DXVECTOR3(0.0f, 100.0f, 0.0f))			//今回のスコアUI
#define TITLE_CAMERA	(0.01f)									//タイトルカメラ
#define CORRECT_V		(500.0f)								//注視点補正
//==============================================
//コンストラクタ
//==============================================
CCamera::CCamera()
{
	//初期化
	 m_posV = POS_V;							//視点
	 m_posR = POS_R;							//注視点
	 m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//上方向ベクトル
	 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	 m_nCounter = 1;
}
//==============================================
//デスストラクタ
//==============================================
CCamera::~CCamera()
{

}
//==============================================
//カメラ初期化処理
//==============================================
HRESULT CCamera::Init(void)
{
	//初期化
	m_posV = POS_V;		//視点
	m_posR = POS_R;		//注視点

	return S_OK;
}
//==============================================
//カメラ終了処理
//==============================================
void CCamera::Uninit(void)
{
	
}
//==============================================
//カメラ更新処理
//==============================================
void CCamera::Update(void)
{
	if (CScene::GetMode() == CScene::MODE_TITLE)
	{
		m_rot.y += TITLE_CAMERA;

		m_posR.x += sinf(m_rot.y);
		m_posR.z += cosf(m_rot.y);
	}
	else
	{
		//オブジェクトインスタンス
		CObject *pObj;

		//タイプ変数
		CObject::TYPE type;

		//オブジェクトの先頭を取得
		pObj = CObject::GetTop();

		while (pObj != NULL)
		{//メモリがあるとき

		 //次のオブジェクトを保存しておく
			CObject *pObjectNext = pObj->GetNext();

			//タイプ取得
			type = pObj->GetType();

			if (type == CObject::TYPE_PLAYER_R)
			{//注視点プレイヤーの時

			 //オブジェクトをプレイヤーにキャスト
				CPlayer *pObjXR = dynamic_cast<CPlayer*>(pObj);

				//オブジェクトの先頭を取得
				pObj = CObject::GetTop();

				while (pObj != NULL)
				{//メモリがあるとき

				 //次のオブジェクトを保存しておく
					CObject *pObjectNext = pObj->GetNext();

					//タイプ取得
					type = pObj->GetType();

					if (type == CObject::TYPE_PLAYER)
					{//注視点プレイヤーの時

					 //オブジェクトをプレイヤーにキャスト
						CPlayer *pObjX = dynamic_cast<CPlayer*>(pObj);

						//オブジェクトの先頭を取得
						pObj = CObject::GetTop();

						while (pObj != NULL)
						{//メモリがあるとき
							 
							CObject *pObjectNext = pObj->GetNext();

							//タイプ取得
							type = pObj->GetType();

							if (type == CObject::TYPE_STAGE)
							{//注視点プレイヤーの時

							 //オブジェクトをプレイヤーにキャスト
								CObject3D *pObj3D = dynamic_cast<CObject3D*>(pObj);

								if (CPlayer::GetChange() == true)
								{
									//各視点の反対を求める
									if (pObjXR->GetRot().y >= 0)
									{
										m_rotPlayR.y = pObjXR->GetRot().y - D3DX_PI;
									}
									else if (pObjXR->GetRot().y < 0)
									{
										m_rotPlayR.y = pObjXR->GetRot().y + D3DX_PI;
									}

									if (pObjX->GetRot().y >= 0)
									{
										m_rotPlay.y = pObjX->GetRot().y - D3DX_PI;
									}
									else if (pObjX->GetRot().y < 0)
									{
										m_rotPlay.y = pObjX->GetRot().y + D3DX_PI;
									}

									m_spin = m_rotPlayR - m_rotPlay;

									if (m_spin.y > D3DX_PI)
									{
										m_spin.y = -((D3DX_PI * 2.0f) - m_spin.y);
									}
									else if (m_spin.y < -D3DX_PI)
									{
										m_spin.y = (D3DX_PI * 2.0f) + m_spin.y;
									}

									m_nCounter = 1;
								}

								//************************************************************//
								//						カメラ追従処理						  //
								//************************************************************//
								m_posR.x += (pObjXR->GetPos().x + (sinf(pObjXR->GetRot().y)) - m_posR.x) * 0.1f;
								m_posR.z += (pObjXR->GetPos().z + (cosf(pObjXR->GetRot().y)) - m_posR.z) * 0.1f;

								if (m_nCounter < 30)
								{
									m_posV.x = m_posR.x - sinf(pObjX->GetRot().y + m_spin.y * ((float)m_nCounter / 30) + D3DX_PI) * CORRECT_V;
									m_posV.z = m_posR.z - cosf(pObjX->GetRot().y + m_spin.y * ((float)m_nCounter / 30) + D3DX_PI) * CORRECT_V;

									CPlayer::SetChange(false);
									m_nCounter++;
								}
								else
								{
									m_posV.x = m_posR.x - sinf(pObjXR->GetRot().y + D3DX_PI) * CORRECT_V;
									m_posV.z = m_posR.z - cosf(pObjXR->GetRot().y + D3DX_PI) * CORRECT_V;
								}

								break;
							}

							//次のオブジェクトにする
							pObj = pObjectNext;
						}
					}

					//次のオブジェクトにする
					pObj = pObjectNext;
				}
			}

			//次のオブジェクトにする
			pObj = pObjectNext;
		}
	}
}
//==============================================
//カメラ描画処理
//==============================================
void CCamera::SetCamera()
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		6000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}