//==============================================
//
//敵の攻撃(enemyattack.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _ENEMYATTACK_H_
#define _ENEMYATTACK_H_

#include"object.h"
#include"model.h"
#include"motion.h"

//************************//
//	敵の攻撃クラスの定義　//
//************************//
class CEnemyattack : public CObject
{
public:	//アクセス可能

	CEnemyattack();									//コンストラクタ
	~CEnemyattack();								//デストラクタ

	//メンバ関数
	HRESULT Init(void);								//初期処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale) { m_pos = pos; m_scale = scale; }		//位置設定処理
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					//角度設定処理

	D3DXVECTOR3 GetPos(void) { return m_pos; }						//位置取得処理
	D3DXVECTOR3 GetScale(void) { return m_scale; }					//大きさ取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//角度取得処理

	//静的メンバ関数
	static CEnemyattack *Create(void);				//メモリ生成処理

private: //アクセス(メンバ関数内)

	D3DXVECTOR3		m_pos;							//位置
	D3DXVECTOR3		m_move;							//位置
	D3DXVECTOR3		m_rot;							//角度
	D3DXVECTOR3		m_scale;						//大きさ
	D3DXMATRIX		m_mtxWorld;						//ワールドマトリックス
	CModel			*m_apModel;						//モデルへのポインタ
	int				m_nNumModel;					//モデルの総数
	CMotion			*pMotion;
	bool			m_bRotInit;						//最初だけ角度を取得する用
	int				m_nLife;						//体力
};

#endif
