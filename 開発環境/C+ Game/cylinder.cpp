//==============================================
//
//オブジェクト2D(object.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"cylinder.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT				(D3DXVECTOR3(0.0f,0.0f,0.0f))	//位置Yの初期値
#define MESH_SPLIT				(6)							//分割数
#define MESH_WIDTH				(2000.0f)						//背景の広さ
#define MESH_HEIGHT				(2000.0f)						//背景の高さ
#define MESH_TEX_RESOLUTION		(2.0f)							//背景の解像度
//==============================================
//コンストラクタ
//==============================================
CCylinder::CCylinder()
{
	//初期設定
	m_pTexture = NULL;		//テクスチャのポインタ
	m_pVtxBuffer = NULL;	//バッファのポインタ
	m_pIdxBuffer = NULL;

	m_pos = VECTOR_INIT;		//位置
	m_rot = VECTOR_INIT;		//角度
	m_scale = SCALE_INIT * 10;	//大きさ
}
//==============================================
//デスストラクタ
//==============================================
CCylinder::~CCylinder()
{

}
//==============================================
//シリンダーの初期化処理
//==============================================
HRESULT CCylinder::Init(void)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall.jpg",
		&m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESH_SPLIT * 2 + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファのロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	for (int nCntMeshCylinder = 0; nCntMeshCylinder < MESH_SPLIT + 1; nCntMeshCylinder++)
	{
		pVtx[nCntMeshCylinder].pos = D3DXVECTOR3(
		sinf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) *MESH_WIDTH,
			MESH_HEIGHT,
			cosf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) * MESH_WIDTH);

		pVtx[MESH_SPLIT + nCntMeshCylinder + 1].pos = D3DXVECTOR3(
			sinf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) *MESH_WIDTH,
			0.0f,
			cosf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) * MESH_WIDTH);

		if (nCntMeshCylinder == MESH_SPLIT)
		{
			pVtx[nCntMeshCylinder].pos = D3DXVECTOR3(
				sinf(D3DX_PI * 1.0f) *MESH_WIDTH,
				MESH_HEIGHT,
				cosf(D3DX_PI * 1.0f) * MESH_WIDTH);

			pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].pos = D3DXVECTOR3(
				sinf(D3DX_PI * 1.0f) *MESH_WIDTH,
				0.0f,
				cosf(D3DX_PI * 1.0f) * MESH_WIDTH);
		}

		//法線ベクトルの設定
		pVtx[nCntMeshCylinder].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntMeshCylinder].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[nCntMeshCylinder].tex = D3DXVECTOR2(nCntMeshCylinder * (MESH_TEX_RESOLUTION / MESH_SPLIT), 0.0f);
		pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].tex = D3DXVECTOR2(nCntMeshCylinder * (MESH_TEX_RESOLUTION / MESH_SPLIT), 1.0f);
	}

	//頂点バッファのアンロック
	m_pVtxBuffer->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (MESH_SPLIT * 2 + 2), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuffer, NULL);

	WORD *pIdx;

	//インデックスバッファをロックし、頂点番号へのポインタを取得
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//頂点番号データの設定
	for (int nCntMeshCylinder = 0; nCntMeshCylinder < MESH_SPLIT * 2 + 2; nCntMeshCylinder++)
	{
		if (nCntMeshCylinder % EVENPARITY == NOPARITY)
		{
			pIdx[nCntMeshCylinder] = nCntMeshCylinder / EVENPARITY;
		}
		if (nCntMeshCylinder % EVENPARITY == ODDPARITY)
		{
			pIdx[nCntMeshCylinder] = (nCntMeshCylinder / EVENPARITY) + ODDPARITY + MESH_SPLIT;
		}
	}

	//インデックスバッファのアンロック
	m_pIdxBuffer->Unlock();

	SetType(TYPE_WALL);

	return S_OK;
}
//==============================================
//シリンダーの終了処理
//==============================================
void CCylinder::Uninit(void)
{
	if (m_pVtxBuffer != NULL)
	{//バッファの破棄
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}

	//オブジェクトの解放処理
	CObject::Release();
}
//==============================================
//シリンダーのメモリ生成処理
//==============================================
CCylinder *CCylinder::Create(void)
{
	CCylinder *pCylinder;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pCylinder = new CCylinder;

	if (pCylinder != NULL)
	{
		//初期化処理
		pCylinder->Init();
	}

	return pCylinder;
}
//==============================================
//シリンダーの更新処理
//==============================================
void CCylinder::Update(void)
{

}
//==============================================
//シリンダーの描画処理
//==============================================
void CCylinder::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;		//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

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

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuffer);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);

	//ポリゴン描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MESH_SPLIT * 2 + 2), 0, (MESH_SPLIT * 2 + 2));
}
//==============================================
//テクスチャの割り当て
//==============================================
void CCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//==============================================
//位置設定処理
//==============================================
void CCylinder::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//位置代入
	m_pos = pos;
}