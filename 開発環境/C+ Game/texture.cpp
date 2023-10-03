//==============================================
//
//テクスチャ管理(texutre.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"texture.h"
#include"manager.h"
#include"renderer.h"

int CTexture::m_nNumAll = 0;
//==============================================
//コンストラクタ
//==============================================
CTexture::CTexture()
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		m_apTexture[nCntTex] = NULL;
		m_nTexname[nCntTex] = "NULL";
	}

	m_nNumAll = -1;
}
//==============================================
//デスストラクタ
//==============================================
CTexture::~CTexture()
{

}
//==============================================
//テクスチャの読込処理
//==============================================
HRESULT CTexture::Load(void)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//0
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Title.png",
		&m_apTexture[TEXTURE_TITLE]);

	//1
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\result000.png",
		&m_apTexture[TEXTURE_RESULT]);

	//2
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking.png",
		&m_apTexture[TEXTURE_RANKING]);

	//14
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\press_enter.png",
		&m_apTexture[TEXTURE_ENTER]);

	//3
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\your_score.png",
		&m_apTexture[TEXTURE_YOURSCORE]);

	//4
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\1st.png",
		&m_apTexture[TEXTURE_FIRST]);

	//5
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\2nd.png",
		&m_apTexture[TEXTURE_SECOND]);

	//6
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\3rd.png",
		&m_apTexture[TEXTURE_THIRD]);

	//7
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&m_apTexture[TEXTURE_NUMBER]);

	//8
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TextBack.jpg",
		&m_apTexture[TEXTURE_FLAME]);

	//9
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&m_apTexture[TEXTURE_EFFECT]);

	//10
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\superman_hero.png",
		&m_apTexture[TEXTURE_PLAYER]);

	//11
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy.png",
		&m_apTexture[TEXTURE_ENEMY]);

	//12
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Tile.jpg",
		&m_apTexture[TEXTURE_BLOCK]);

	//13
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet001.png",
		&m_apTexture[TEXTURE_BULLET]);

	//14
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&m_apTexture[TEXTURE_EXPLOSION]);

	//15
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\control.png",
		&m_apTexture[TEXTURE_CONTROL]);
	
	return S_OK;
}
//==============================================
//テクスチャの破棄処理
//==============================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		//テクスチャ破棄
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
//==============================================
//テクスチャの指定読込処理
//==============================================
int CTexture::Regist(const char *pFilename)
{
	//レンダーの情報取得
	CRenderer *pRenderer = CManager::GetRenderer();
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		if (strcmp(m_nTexname[nCntTex],pFilename) == 0)
		{
			return (nCntTex + TEXTURE_MAX);
		}
	}

	m_nNumAll++;

	if (m_apTexture[(m_nNumAll + TEXTURE_MAX)] == NULL)
	{
		D3DXCreateTextureFromFile(pDevice,
		pFilename,
		&m_apTexture[(m_nNumAll + TEXTURE_MAX)]);

		//文字数分の動的確保
		m_nTexname[m_nNumAll] = new char[(int)(strlen(pFilename))];

		//保存
		strcpy(m_nTexname[m_nNumAll], pFilename);
	}

	return (m_nNumAll + TEXTURE_MAX);
}
//==============================================
//テクスチャの取得処理
//==============================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int ndlx)
{
		return m_apTexture[ndlx];
}
