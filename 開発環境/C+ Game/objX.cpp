//==============================================
//
//�I�u�W�F�N�gX(objX.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"objX.h"
#include"texture.h"

//****************//
//   �}�N����`   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//�ʒuY�̏����l
//==============================================
//�R���X�g���N�^
//==============================================
CObjX::CObjX()
{
	//�����ݒ�
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;

	m_pos = VECTOR_INIT;	//�ʒu
	m_rot = VECTOR_INIT;	//�p�x
	m_move = VECTOR_INIT;	//�傫��
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CObjX::~CObjX()
{

}
//==============================================
//3D�I�u�W�F�N�g�̏���������
//==============================================
HRESULT CObjX::Init(void)
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	CTexture *pTexture = CManager::GetTexture();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATERIAL	*pMat;	//�}�e���A���ւ̃|�C���^

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX({m_Filename},
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	m_nIdxTex = new int[(int)m_dwNumMat];

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���@

			m_nIdxTex[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
	}

	SetType(TYPE_OBJX);

	return S_OK;
}
//==============================================
//3D�I�u�W�F�N�g�̏I������
//==============================================
void CObjX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	//�I�u�W�F�N�g�̉������
	CObject::Release();
}
//==============================================
//3D�I�u�W�F�N�g�̃�������������
//==============================================
CObjX *CObjX::Create(void)
{
	CObjX *pObjX;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pObjX = new CObjX;

	if (pObjX != NULL)
	{
		//����������
		pObjX->Init();
	}

	return pObjX;
}
//==============================================
//3D�I�u�W�F�N�g�̍X�V����
//==============================================
void CObjX::Update(void)
{
}
//==============================================
//3D�I�u�W�F�N�g�̕`�揈��
//==============================================
void CObjX::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	D3DXMATRIX		  mtxRot, mtxTrans, mtxScall;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9	  matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL	  *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	//�g�k�𔽉f
	D3DXMatrixScaling(&mtxScall, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0,pTexture->GetAddress(*m_nIdxTex));

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}