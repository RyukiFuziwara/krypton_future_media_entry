//==============================================
//
//モデル(model.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//**************************//
//2Dオブジェクトクラスの定義//
//**************************//
class CModel
{
public:	//アクセス可能

	CModel();						//コンストラクタ
	~CModel();						//デストラクタ

	//メンバ関数
	HRESULT Init(const char *Filename);	//初期処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Draw(void);					//描画処理

	//静的メンバ関数
	static CModel *Create(const char *Filename);	//メモリ生成処理
	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; };

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos + m_offset; };				//位置設定処理
	void SetOffSet(D3DXVECTOR3 offset) { m_offset = offset; };				//オフセット設定処理
	void AddPos(D3DXVECTOR3 add) { m_pos += add; }							//位置加算設定
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };							//角度設定処理
	void SetDirection(float direction) { m_direction = direction; }			//方向設定処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	
	float GetDirection(void) { return m_direction; }

private: //アクセス(メンバ関数内)

	
	LPD3DXMESH		m_pMesh;		//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER	m_pBuffMat;		//マテリアルへのポインタ
	DWORD			m_dwNumMat;		//マテリアルの数
	D3DXVECTOR3		m_pos;			//位置
	D3DXVECTOR3		m_offset;		//オフセット
	D3DXVECTOR3		m_rot;			//角度
	D3DXMATRIX		m_mtxWorld;		//ワールドマトリックス
	CModel			*m_pParent;		//親モデルのポインタ
	int				*m_nIdxTex;		//テクスチャの数
	float			m_direction;	//体の方向
};

#endif
