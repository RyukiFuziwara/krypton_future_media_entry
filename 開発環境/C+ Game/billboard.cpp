//==============================================
//
//ビルボード(billboard.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Billboard.h"
#include"pause.h"

//****************//
//   マクロ定義   //
//****************//
#define BILLBOARD_WIDTH		(10)
#define BILLBOARD_HEIGHT	(10)
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//位置Yの初期値

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CBillboard::m_pTexture = NULL;
//==============================================
//コンストラクタ
//==============================================
CBillboard::CBillboard()
{
	//初期設定
	m_pTexture = NULL;		//テクスチャのポインタ
	m_pVtxBuffer = NULL;	//バッファのポインタ

	m_pos = VECTOR_INIT;		//位置
	m_scale = SCALE_INIT;	//大きさ
}
//==============================================
//デスストラクタ
//==============================================
CBillboard::~CBillboard()
{

}
//==============================================
//ビルボードの初期化処理
//==============================================
HRESULT CBillboard::Init(void)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_3D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の座標の設定
	pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, +BILLBOARD_HEIGHT, +BILLBOARD_HEIGHT);
	pVtx[1].pos = D3DXVECTOR3(+BILLBOARD_WIDTH, +BILLBOARD_HEIGHT, +BILLBOARD_HEIGHT);
	pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, -BILLBOARD_HEIGHT);
	pVtx[3].pos = D3DXVECTOR3(+BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, -BILLBOARD_HEIGHT);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//色の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();

	return S_OK;
}
//==============================================
//ビルボードの終了処理
//==============================================
void CBillboard::Uninit(void)
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
//ビルボードのメモリ生成処理
//==============================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard;	//ビルボードのインスタンス生成

	//メモリ生成
	pBillboard = new CBillboard;

	if (pBillboard != NULL)
	{
		//初期化処理
		pBillboard->Init();
	}

	return pBillboard;
}
//==============================================
//ビルボードの更新処理
//==============================================
void CBillboard::Update(void)
{

}
//==============================================
//ビルボードの描画処理
//==============================================
void CBillboard::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();																			
	
	D3DXMATRIX		  mtxTrans;		 //計算用マトリックス
	D3DXMATRIX		  mtxView;		 //ビューマトリックス取得用

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	
	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに向ける
	D3DXMatrixInverse(&m_mtxworld, NULL, &mtxView);		//逆行列を求める
	m_mtxworld._41 = 0.0f;
	m_mtxworld._42 = 0.0f;
	m_mtxworld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	//頂点バッファのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//アルファブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
//==============================================
//位置設定処理
//==============================================
void CBillboard::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//位置代入
	m_pos = pos;

	m_scale = scale;

	VERTEX_3D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x,+m_scale.y,+m_scale.y);
	pVtx[1].pos = D3DXVECTOR3(+m_scale.x,+m_scale.y,+m_scale.y);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x,-m_scale.y,-m_scale.y);
	pVtx[3].pos = D3DXVECTOR3(+m_scale.x,-m_scale.y,-m_scale.y);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}
//==============================================
//色設定処理
//==============================================
void CBillboard::SetCol(D3DXCOLOR Col, float fRadius)
{
	m_col = Col;

	VERTEX_3D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//色の設定
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}
//==============================================
//テクスチャの割り当て
//==============================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
