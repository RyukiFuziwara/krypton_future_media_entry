//==============================================
//
//���C�g(light.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"light.h"
#include"manager.h"
#include"renderer.h"

//==============================================
//�R���X�g���N�^
//==============================================
CLight::CLight()
{			
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CLight::~CLight()
{

}
//==============================================
//���C�g�̏���������
//==============================================
HRESULT CLight::Init(void)
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3	vecDir;	//�ݒ�p�����x�N�g��

	//���C�g�̏����N���A����
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	m_Light.Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	m_Light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	D3DXVec3Normalize(&vecDir, &vecDir);
	m_Light.Direction = vecDir;
	
	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_Light);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	return S_OK;
}
//==============================================
//���C�g�̏I������
//==============================================
void CLight::Uninit(void)
{
	
}
//==============================================
//���C�g�̍X�V����
//==============================================
void CLight::Update(void)
{

}