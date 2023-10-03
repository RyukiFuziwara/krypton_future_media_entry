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
#include"object3D.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))	//位置Yの初期値
#define MESH_SPLIT			(32)							//分割数
#define CENTER_AND_ONELAP	(2)								//中心点と１周で重なる点
#define MESH_ALL_VERTEX		(MESH_SPLIT + 1)				//周辺の分割地点と中心
#define MESH_ALL_INDEX		(MESH_SPLIT + 2)				//周辺の分割地点と中心・１周で重なる点
#define MESH_WIDTH			(2000.0f)						//地面の横幅
#define MESH_HEIGHT			(2000.0f)						//地面の縦幅
#define MESH_RADIUS			(MESH_HEIGHT)			//半径

//静的メンバ変数宣言
D3DXVECTOR3 CObject3D::m_pos = {};
float CObject3D::m_fRadius = 0.0f;

//==============================================
//コンストラクタ
//==============================================
CObject3D::CObject3D()
{
	//初期設定
	m_pTexture = NULL;		//テクスチャのポインタ
	m_pVtxBuffer = NULL;	//バッファのポインタ
	m_pIdxBuffer = NULL;

	m_pos = VECTOR_INIT;		//位置
	m_rot = VECTOR_INIT;		//角度
	m_scale = SCALE_INIT * 10;	//大きさ

	m_fRadius = MESH_RADIUS;
}
//==============================================
//デスストラクタ
//==============================================
CObject3D::~CObject3D()
{

}
//==============================================
//3Dオブジェクトの初期化処理
//==============================================
HRESULT CObject3D::Init(void)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Tile.jpg",
		&m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_ALL_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点番号
	int nNumVtx = 0;

	float Rot = D3DX_PI;	//角度

	pVtx[nNumVtx].pos = VECTOR_INIT;						//中心座標代入
	pVtx[nNumVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//法線
	pVtx[nNumVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	pVtx[nNumVtx].tex = D3DXVECTOR2(0.5f, 0.5f);			//テクスチャ座標

	nNumVtx++;

	//周辺の頂点情報の設定
	for (int nCntVtx = 0; nCntVtx < MESH_SPLIT; nCntVtx++, nNumVtx++)
	{
		pVtx[nNumVtx].pos = D3DXVECTOR3(
			sinf(Rot) * MESH_WIDTH,			//Xの位置
			0.0f,							//Yの位置
			cosf(Rot) * MESH_HEIGHT);		//Zの位置

		pVtx[nNumVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nNumVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		float aTexU = 0.5f - 0.5f * sinf(Rot);	//テクスチャ幅
		float aTexV = 0.5f - 0.5f * cosf(Rot);	//テクスチャ高さ

		pVtx[nNumVtx].tex = D3DXVECTOR2(aTexU, aTexV);

		//角度を　全体の角度÷分割数で割った答え分、引く
		Rot -= (D3DX_PI * 2.0f) / MESH_SPLIT;
	}

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_ALL_INDEX,
		D3DUSAGE_WRITEONLY, 
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffer,
		NULL);

	//インデックス情報へのポインタ
	WORD *pIdx;

	//インデックスバッファをロックし頂点情報へのポインタを取得
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	for (int nNumIdx = 0; nNumIdx < MESH_ALL_INDEX; nNumIdx++)
	{
		//下の計算式では、　ちょうど1周するときに答えが1になる　　それ以外では、カウンター÷分割数　の余りが番号として設定される
		pIdx[nNumIdx] = (nNumIdx / (MESH_ALL_INDEX - 1)) + (nNumIdx % (MESH_ALL_INDEX - 1));
	}

	//インデックスバッファをアンロック
	m_pIdxBuffer->Unlock();

	SetType(TYPE_STAGE);

	return S_OK;
}
//==============================================
//3Dオブジェクトの終了処理
//==============================================
void CObject3D::Uninit(void)
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
//3Dオブジェクトのメモリ生成処理
//==============================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObject3D;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pObject3D = new CObject3D;

	if (pObject3D != NULL)
	{
		//初期化処理
		pObject3D->Init();
	}

	return pObject3D;
}
//==============================================
//3Dオブジェクトの更新処理
//==============================================
void CObject3D::Update(void)
{
}
//==============================================
//3Dオブジェクトの描画処理
//==============================================
void CObject3D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;		//計算用マトリックス

	//両面カリングをON
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

	//描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,0,0, MESH_ALL_VERTEX,0, MESH_SPLIT);

	//普通のカリングモードにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//==============================================
//3Dオブジェクトの当たり判定処理
//==============================================
bool CObject3D::CollisionStage(D3DXVECTOR3 pos)
{
	bool bColli = false;

	//現在・前回の位置とフィールドの中心位置の差を格納
	D3DXVECTOR2 PosDiff;

	PosDiff.x = powf(m_pos.x - pos.x, 2.0f);	//現在のＸ座標の差の２乗
	PosDiff.y = powf(m_pos.z - pos.z, 2.0f);	//現在のＺ座標の差の２乗	変数は  "Ｙ" だけど、Ｚ座標の差を入れます 

	float fLength = sqrtf(PosDiff.x + PosDiff.y);	//現在のＸ・Ｚの長さを取得

	if (fLength >= m_fRadius)
	{//中心位置からの距離がフィールドの半径以上だった

		bColli = true;
	}

	return bColli;
}
//==============================================
//テクスチャの割り当て
//==============================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//==============================================
//位置設定処理
//==============================================
void CObject3D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//位置代入
	m_pos = pos;
}