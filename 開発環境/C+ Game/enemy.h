//==============================================
//
//敵3D(enemy.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _enemy_H_
#define _enemy_H_

#include"object.h"
#include"model.h"
#include"motion.h"
#include"life.h"

#define ENEMY_MODEL_PARTS (3)	//プレイヤーのパーツ数
//************************//
//	  敵のクラスの定義	  //
//************************//
class CEnemy : public CObject
{
public:	//アクセス可能

	CEnemy();									//コンストラクタ
	~CEnemy();									//デストラクタ

	typedef enum
	{
		BOSS_FORM_ONE = 0,
		BOSS_FORM_TWO,
		BOSS_FORM_THREE,
		BOSS_FORM_MAX,

	}BOSS_FORM;

	//メンバ関数
	HRESULT Init(void);								//初期処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理

	virtual void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale) { m_pos = pos;}			//位置設定処理
	virtual D3DXVECTOR3 GetPos(void) { return m_pos; }								//位置取得処理
	virtual D3DXVECTOR3 GetScale(void) { return m_scale; }							//大きさ取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }										//角度取得処理
	static int GetFormType(void) { return m_Form; }

	//静的メンバ関数
	static CEnemy *Create(void);												//メモリ生成処理

	//当たり判定
	static bool CEnemy::Collision(
		D3DXVECTOR3 *pPos,
		D3DXVECTOR3 *pMove,
		D3DXVECTOR3 scale,
		float fWidth,
		float fHeight);


private: //アクセス(メンバ関数内)

	void Attack(void);								//更新処理
	void Defeat(void);								//撃破処理

	static CLife	*m_pLife;
	static int		m_Form;							//ボスの形態

	int				m_nLifeTemp;
	D3DXVECTOR3		m_pos;							//位置
	D3DXVECTOR3		m_rot;							//角度
	D3DXVECTOR3		m_scale;						//大きさ
	D3DXMATRIX		m_mtxWorld;						//ワールドマトリックス
	CModel			*m_apModel[ENEMY_MODEL_PARTS];	//モデルへのポインタ
	int				m_nNumModel;					//モデルの総数
	CMotion			*pMotion;
	
	int				m_nAttackCount;					//攻撃カウント
	int				m_UltStack;						//必殺スタック
	int				m_nNum;							//体力
	float			m_movey;						//重力加算用

	bool			m_bDefeat;
};
#endif
