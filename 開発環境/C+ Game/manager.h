//==============================================
//
//マネージャー(manager.h)
//Author: fujiwara ryuki
//
//==============================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"d3dx9.h"
#include"object.h"

class CRenderer;
class CInputKeyboard;
class CInputKeyPad;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CFade;

//******************//
//シーンのクラス定義//
//******************//
class CScene
{
public: //アクセス可能

	enum MODE
	{
		MODE_TITLE,
		MODE_GAME,
		MODE_PAUSE,
		MODE_RESULT,
		MODE_MAX
	};

	CScene();					//コンストラクタ
	virtual ~CScene();			//デストラクタ

	virtual HRESULT Init(void);		//初期化処理
	virtual void Uninit(void);		//終了処理
	virtual void Update(void);		//更新処理
	virtual void Draw(void);		//描画処理

	//静的メンバ関数
	static CScene *Create(MODE mode);	//メモリ生成処理
	static CScene::MODE GetMode(void);	//モードの取得

	static CFade *m_pfade;

private: //アクセス(メンバ関数内)

	static MODE m_mode;

	CScene *m_pPause;					//ポーズのポインタ
};

//************************//
//マネージャークラスの定義//
//************************//
class CManager
{
public: //アクセス可能

	CManager();		//コンストラクタ
	~CManager();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		//初期処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(int nCount);											//描画処理

	static void SetMode(CScene::MODE mode);							//モードの設定
	static CRenderer *GetRenderer(void);							//レンダーの取得
	static CInputKeyboard *GetInputKeyboard(void);					//キーボードの取得
	static CInputKeyPad *GetInputKeyPad(void);					//キーパッドの取得
	static CCamera *GetCamera(void);								//カメラの取得
	static CTexture *GetTexture(void);								//テクスチャの取得
	static CSound *GetSound(void);									//サウンドの取得

private: //アクセス(メンバ関数内)

	static CTexture			*m_pTexture;							//テクスチャのポインタ
	static CRenderer		*m_pRenderer;							//レンダーのポインタ
	static CInputKeyboard	*m_pInputKeyboard;						//キーボードのポインタ
	static CInputKeyPad		*m_pInputKeyPad;						//キーパッドのポインタ
	static CSound			*m_pSound;								//サウンドのポインタ
	static CCamera			*m_pCamera;								//カメラのポインタ
	static CLight			*m_pLight;								//ライトのポインタ
	static CScene			*m_pScene;								//シーンのポインタ
};
#endif 
