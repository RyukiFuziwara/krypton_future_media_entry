//==============================================
//
//オブジェクトX(objX.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _OBJX_H_
#define _OBJX_H_

#include"object.h"

//**************************//
//2Dオブジェクトクラスの定義//
//**************************//
class CObjX : public CObject
{
public:	//アクセス可能

	CObjX();									//コンストラクタ
	virtual~CObjX();							//デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);										//初期処理
	virtual void Uninit(void);										//終了処理
	virtual void Update(void);										//更新処理
	virtual void Draw(void);										//描画処理

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale) { m_pos = pos; m_scale = scale; };	//位置設定処理
	void SetRot(D3DXVECTOR3 rot) {m_rot = rot;};	//位置設定処理
	D3DXVECTOR3 GetPos(void) { return m_pos; }						//位置取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//角度取得処理
	D3DXVECTOR3 GetScale(void) { return m_scale; }					//角度取得処理

	void SetFile(const char *Filename) { m_Filename = Filename; };	//ファイル設定処理

	//静的メンバ関数
	static CObjX *Create(void);										//メモリ生成処理

private: //アクセス(メンバ関数内)

	//メンバ変数
	D3DXMATRIX				m_mtxworld;								//ワールドマトリックス
	D3DXVECTOR3				m_pos;									//位置
	D3DXVECTOR3				m_rot;									//角度
	D3DXVECTOR3				m_move;									//移動量
	D3DXVECTOR3				m_scale;								//大きさ
	LPD3DXMESH				m_pMesh;								//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER			m_pBuffMat;								//マテリアルへのポインタ
	DWORD					m_dwNumMat;								//マテリアルの数
	
	int *m_nIdxTex;

	const char *m_Filename;
};

#endif
