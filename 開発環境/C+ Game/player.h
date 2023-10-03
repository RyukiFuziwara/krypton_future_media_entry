//==============================================
//
//オブジェクトX(player.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _player_H_
#define _player_H_

#include"object.h"
#include"model.h"
#include"motion.h"
#include"ActionGauge.h"

#define PLAYER_MODEL_PARTS (10)	//プレイヤーのパーツ数
//************************//
//プレイヤーのクラスの定義//
//************************//
class CPlayer : public CObject
{
public:	//アクセス可能

	CPlayer();									//コンストラクタ
	~CPlayer();									//デストラクタ

	typedef enum
	{
		CONTROL_P1 = 0,
		CONTROL_P2,
		CONTROL_ALL
	}CONTROL;

	//メンバ関数
	HRESULT Init(void);											//初期処理
	void Uninit(void);											//終了処理
	void Update(void);											//更新処理
	void Draw(void);											//描画処理

	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)				//位置設定処理
	{ m_pos = pos; m_posTemp = pos;}

	D3DXVECTOR3 GetPos(void) { return m_pos; }					//位置取得処理
	D3DXVECTOR3 GetScale(void) { return m_scale; }				//大きさ取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }					//角度取得処理

	//静的メンバ関数
	static CPlayer *Create(void);							//メモリ生成処理

	static void SetChange(bool change) { m_change = change;}		//切替設定処理
	static bool GetChange(void) { return m_change; }				//切替取得処理
	static CONTROL GetCon(void) { return m_con; }					//制御取得処理
	static void SetAction(bool bAction) { m_bAction = bAction; }	//行動してるかの設定処理
	static bool GetAction(void) { return m_bAction; }				//行動してるかの取得処理
	static int GetOperation(void) { return m_nOpeCnt; }				//操作してるかの取得処理
	static bool GetDamage(void) { return m_bDamage; }				//攻撃受けてるかの取得処理
	static void SetDamage(bool bDamage) { m_bDamage = bDamage; }	//攻撃受けてるかの設定処理

	static bool Collision(D3DXVECTOR3 *pPos,						//当たり判定
		D3DXVECTOR3 scale,
		float fWidth,
		float fHeight);

private: //アクセス(メンバ関数内)

	void Action(void);								//行動処理

	static CONTROL	m_con;
	static CONTROL	m_conTemp;
	static bool		m_change;
	static bool		m_bAction;
	static bool		m_bDamage;
	static int		m_nOpeCnt;

	D3DXVECTOR3		m_pos;							//位置
	D3DXVECTOR3		m_posTemp;						//位置
	D3DXVECTOR3		m_rot;							//角度
	D3DXVECTOR3		m_move;							//移動量
	D3DXVECTOR3		m_scale;						//大きさ
	D3DXMATRIX		m_mtxWorld;						//ワールドマトリックス
	CModel			*m_apModel[PLAYER_MODEL_PARTS];	//モデルへのポインタ
	CMotion			*pMotion;
	MOTIONTYPE		MotionType;
	int				m_nNumModel;					//モデルの総数
	int				m_nCntEfe;					//モデルの総数
	bool			m_bJump;
	bool			m_bmove;
};

#endif
