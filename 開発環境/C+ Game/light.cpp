//==============================================
//
//ライト(light.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"light.h"
#include"manager.h"
#include"renderer.h"

//==============================================
//コンストラクタ
//==============================================
CLight::CLight()
{			
}
//==============================================
//デスストラクタ
//==============================================
CLight::~CLight()
{

}
//==============================================
//ライトの初期化処理
//==============================================
HRESULT CLight::Init(void)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3	vecDir;	//設定用方向ベクトル

	//ライトの情報をクリアする
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	//ライトの種類を設定
	m_Light.Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	D3DXVec3Normalize(&vecDir, &vecDir);
	m_Light.Direction = vecDir;
	
	//ライトを設定する
	pDevice->SetLight(0, &m_Light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	return S_OK;
}
//==============================================
//ライトの終了処理
//==============================================
void CLight::Uninit(void)
{
	
}
//==============================================
//ライトの更新処理
//==============================================
void CLight::Update(void)
{

}