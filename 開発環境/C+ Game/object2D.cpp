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
#include"object2D.h"

//****************//
//   マクロ定義   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f, 0.0f))		//位置Yの初期値
//==============================================
//コンストラクタ
//==============================================
CObject2D::CObject2D()
{
	//初期設定
	m_pTexture = NULL;		//テクスチャのポインタ
	m_pVtxBuffer = NULL;	//バッファのポインタ

	m_pos = POS_INIT;		//位置
	m_move = VECTOR_INIT;	//位置
	m_rot = VECTOR_INIT;	//角度
	m_scale = SCALE_INIT;	//大きさ
}
//==============================================
//デスストラクタ
//==============================================
CObject2D::~CObject2D()
{

}
//==============================================
//2Dオブジェクトの初期化処理
//==============================================
HRESULT CObject2D::Init(void)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_2D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - SCALE_INIT.x, m_pos.y - SCALE_INIT.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + SCALE_INIT.x, m_pos.y - SCALE_INIT.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - SCALE_INIT.x, m_pos.y + SCALE_INIT.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + SCALE_INIT.x, m_pos.y + SCALE_INIT.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
//2Dオブジェクトの終了処理
//==============================================
void CObject2D::Uninit(void)
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
//2Dオブジェクトのメモリ生成処理
//==============================================
CObject2D *CObject2D::Create(void)
{
	CObject2D *pObject2D;	//2Dオブジェクトのインスタンス生成

	//メモリ生成
	pObject2D = new CObject2D;

	if (pObject2D != NULL)
	{
		//初期化処理
		pObject2D->Init();
	}

	return pObject2D;
}
//==============================================
//2Dオブジェクトの更新処理
//==============================================
void CObject2D::Update(void)
{
	
}
//==============================================
//2Dオブジェクトの描画処理
//==============================================
void CObject2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	if (GetType() == TYPE_EFFECT)
	{
		//アルファブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (GetType() == TYPE_EFFECT)
	{
		//アルファブレンディングをデフォルトに設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
//==============================================
//位置設定処理
//==============================================
void CObject2D::SetPos(D3DXVECTOR3 pos , D3DXVECTOR3 scale)
{
	//位置代入
	m_pos = pos; 

	m_scale = scale;

	VERTEX_2D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}
//==============================================
//位置設定処理
//==============================================
void CObject2D::SetGauge(float Gauge)
{
	VERTEX_2D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Gauge, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Gauge, m_pos.y + m_scale.y, 0.0f);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}
//==============================================
//テクスチャ座標設定処理
//==============================================
void CObject2D::SetTex(D3DXVECTOR2	tex,float Anim)
{
	VERTEX_2D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	///テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2((tex.x - (1.0f / Anim)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((tex.x - (1.0f / Anim)), tex.y);
	pVtx[3].tex = D3DXVECTOR2(tex.x, tex.y);
	
	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}
//==============================================
//色設定処理
//==============================================
void CObject2D::SetCol(D3DXCOLOR Col,float fRadius)
{
	VERTEX_2D *pVtx;	//2Dバッファのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
     m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//色の設定
	pVtx[0].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);
	pVtx[1].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);
	pVtx[2].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);
	pVtx[3].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}
//==============================================
//テクスチャの割り当て
//==============================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
