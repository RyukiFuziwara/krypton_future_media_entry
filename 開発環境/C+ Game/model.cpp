//==============================================
//
//モデル(Model.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"model.h"
#include"texture.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//位置Yの初期値
//==============================================
//コンストラクタ
//==============================================
CModel::CModel()
{
	//初期設定
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;

	m_nIdxTex = NULL;

	m_pos = VECTOR_INIT;	//位置
	m_rot = VECTOR_INIT;	//角度
}
//==============================================
//デスストラクタ
//==============================================
CModel::~CModel()
{

}
//==============================================
//モデルの初期化処理
//==============================================
HRESULT CModel::Init(const char *FIlename)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//テクスチャ取得
	CTexture *pTexture = CManager::GetTexture();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATERIAL	*pMat;	//マテリアルへのポインタ

	//xファイルの読み込み
	D3DXLoadMeshFromX({FIlename},
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
		else
		{
			m_nIdxTex[nCntMat] = NULL;
		}
	}

	//初期設定
	m_pos = VECTOR_INIT;
	m_rot = VECTOR_INIT;

	return S_OK;
}
//==============================================
//モデルの終了処理
//==============================================
void CModel::Uninit(void)
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

	if (m_pParent != NULL)
	{
		m_pParent = NULL;
	}
}
//==============================================
//モデルのメモリ生成処理
//==============================================
CModel *CModel::Create(const char *Filename)
{
	CModel *pModel;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pModel = new CModel;

	if (pModel != NULL)
	{
		//初期化処理
		pModel->Init(Filename);
	}

	return pModel;
}
//==============================================
//モデルの更新処理
//==============================================
void CModel::Update(void)
{
}
//==============================================
//モデルの描画処理
//==============================================
void CModel::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	D3DXMATRIX		  mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9	  matDef;				//現在のマテリアル保存用
	D3DXMATERIAL	  *pMat;				//マテリアルデータへのポインタ

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParent;

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//マトリックスをかけ合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータへのポインタを取得
  	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_nIdxTex[nCntMat] != NULL)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, pTexture->GetAddress(*m_nIdxTex));
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0,NULL);
		}

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//==============================================
//親モデル設定処理
//==============================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}