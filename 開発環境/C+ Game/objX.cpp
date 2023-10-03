//==============================================
//
//オブジェクトX(objX.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"objX.h"
#include"texture.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//位置Yの初期値
//==============================================
//コンストラクタ
//==============================================
CObjX::CObjX()
{
	//初期設定
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;

	m_pos = VECTOR_INIT;	//位置
	m_rot = VECTOR_INIT;	//角度
	m_move = VECTOR_INIT;	//大きさ
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
//==============================================
//デスストラクタ
//==============================================
CObjX::~CObjX()
{

}
//==============================================
//3Dオブジェクトの初期化処理
//==============================================
HRESULT CObjX::Init(void)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	CTexture *pTexture = CManager::GetTexture();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATERIAL	*pMat;	//マテリアルへのポインタ

	//xファイルの読み込み
	D3DXLoadMeshFromX({m_Filename},
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	m_nIdxTex = new int[(int)m_dwNumMat];

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する　

			m_nIdxTex[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	SetType(TYPE_OBJX);

	return S_OK;
}
//==============================================
//3Dオブジェクトの終了処理
//==============================================
void CObjX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//オブジェクトの解放処理
	CObject::Release();
}
//==============================================
//3Dオブジェクトのメモリ生成処理
//==============================================
CObjX *CObjX::Create(void)
{
	CObjX *pObjX;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pObjX = new CObjX;

	if (pObjX != NULL)
	{
		//初期化処理
		pObjX->Init();
	}

	return pObjX;
}
//==============================================
//3Dオブジェクトの更新処理
//==============================================
void CObjX::Update(void)
{
}
//==============================================
//3Dオブジェクトの描画処理
//==============================================
void CObjX::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	D3DXMATRIX		  mtxRot, mtxTrans, mtxScall;	//計算用マトリックス
	D3DMATERIAL9	  matDef;						//現在のマテリアル保存用
	D3DXMATERIAL	  *pMat;						//マテリアルデータへのポインタ

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	//拡縮を反映
	D3DXMatrixScaling(&mtxScall, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0,pTexture->GetAddress(*m_nIdxTex));

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}
	
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}