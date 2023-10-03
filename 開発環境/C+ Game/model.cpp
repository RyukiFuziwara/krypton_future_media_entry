//==============================================
//
//���f��(Model.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"model.h"
#include"texture.h"

//****************//
//   �}�N����`   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//�ʒuY�̏����l
//==============================================
//�R���X�g���N�^
//==============================================
CModel::CModel()
{
	//�����ݒ�
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;

	m_nIdxTex = NULL;

	m_pos = VECTOR_INIT;	//�ʒu
	m_rot = VECTOR_INIT;	//�p�x
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CModel::~CModel()
{

}
//==============================================
//���f���̏���������
//==============================================
HRESULT CModel::Init(const char *FIlename)
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�e�N�X�`���擾
	CTexture *pTexture = CManager::GetTexture();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATERIAL	*pMat;	//�}�e���A���ւ̃|�C���^

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX({FIlename},
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
		else
		{
			m_nIdxTex[nCntMat] = NULL;
		}
	}

	//�����ݒ�
	m_pos = VECTOR_INIT;
	m_rot = VECTOR_INIT;

	return S_OK;
}
//==============================================
//���f���̏I������
//==============================================
void CModel::Uninit(void)
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

	if (m_pParent != NULL)
	{
		m_pParent = NULL;
	}
}
//==============================================
//���f���̃�������������
//==============================================
CModel *CModel::Create(const char *Filename)
{
	CModel *pModel;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pModel = new CModel;

	if (pModel != NULL)
	{
		//����������
		pModel->Init(Filename);
	}

	return pModel;
}
//==============================================
//���f���̍X�V����
//==============================================
void CModel::Update(void)
{
}
//==============================================
//���f���̕`�揈��
//==============================================
void CModel::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	D3DXMATRIX		  mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9	  matDef;				//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL	  *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParent;

	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�}�g���b�N�X���������킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
  	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_nIdxTex[nCntMat] != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAddress(*m_nIdxTex));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0,NULL);
		}

		//���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//==============================================
//�e���f���ݒ菈��
//==============================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}