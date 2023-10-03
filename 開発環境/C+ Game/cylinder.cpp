//==============================================
//
//�I�u�W�F�N�g2D(object.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"cylinder.h"

//****************//
//   �}�N����`   //
//****************//
#define VECTOR_INIT				(D3DXVECTOR3(0.0f,0.0f,0.0f))	//�ʒuY�̏����l
#define MESH_SPLIT				(6)							//������
#define MESH_WIDTH				(2000.0f)						//�w�i�̍L��
#define MESH_HEIGHT				(2000.0f)						//�w�i�̍���
#define MESH_TEX_RESOLUTION		(2.0f)							//�w�i�̉𑜓x
//==============================================
//�R���X�g���N�^
//==============================================
CCylinder::CCylinder()
{
	//�����ݒ�
	m_pTexture = NULL;		//�e�N�X�`���̃|�C���^
	m_pVtxBuffer = NULL;	//�o�b�t�@�̃|�C���^
	m_pIdxBuffer = NULL;

	m_pos = VECTOR_INIT;		//�ʒu
	m_rot = VECTOR_INIT;		//�p�x
	m_scale = SCALE_INIT * 10;	//�傫��
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CCylinder::~CCylinder()
{

}
//==============================================
//�V�����_�[�̏���������
//==============================================
HRESULT CCylinder::Init(void)
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall.jpg",
		&m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESH_SPLIT * 2 + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (int nCntMeshCylinder = 0; nCntMeshCylinder < MESH_SPLIT + 1; nCntMeshCylinder++)
	{
		pVtx[nCntMeshCylinder].pos = D3DXVECTOR3(
		sinf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) *MESH_WIDTH,
			MESH_HEIGHT,
			cosf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) * MESH_WIDTH);

		pVtx[MESH_SPLIT + nCntMeshCylinder + 1].pos = D3DXVECTOR3(
			sinf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) *MESH_WIDTH,
			0.0f,
			cosf(D3DX_PI * (1.0f - (2.0f / MESH_SPLIT * nCntMeshCylinder))) * MESH_WIDTH);

		if (nCntMeshCylinder == MESH_SPLIT)
		{
			pVtx[nCntMeshCylinder].pos = D3DXVECTOR3(
				sinf(D3DX_PI * 1.0f) *MESH_WIDTH,
				MESH_HEIGHT,
				cosf(D3DX_PI * 1.0f) * MESH_WIDTH);

			pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].pos = D3DXVECTOR3(
				sinf(D3DX_PI * 1.0f) *MESH_WIDTH,
				0.0f,
				cosf(D3DX_PI * 1.0f) * MESH_WIDTH);
		}

		//�@���x�N�g���̐ݒ�
		pVtx[nCntMeshCylinder].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntMeshCylinder].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCntMeshCylinder].tex = D3DXVECTOR2(nCntMeshCylinder * (MESH_TEX_RESOLUTION / MESH_SPLIT), 0.0f);
		pVtx[MESH_SPLIT + 1 + nCntMeshCylinder].tex = D3DXVECTOR2(nCntMeshCylinder * (MESH_TEX_RESOLUTION / MESH_SPLIT), 1.0f);
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffer->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (MESH_SPLIT * 2 + 2), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuffer, NULL);

	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	for (int nCntMeshCylinder = 0; nCntMeshCylinder < MESH_SPLIT * 2 + 2; nCntMeshCylinder++)
	{
		if (nCntMeshCylinder % EVENPARITY == NOPARITY)
		{
			pIdx[nCntMeshCylinder] = nCntMeshCylinder / EVENPARITY;
		}
		if (nCntMeshCylinder % EVENPARITY == ODDPARITY)
		{
			pIdx[nCntMeshCylinder] = (nCntMeshCylinder / EVENPARITY) + ODDPARITY + MESH_SPLIT;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuffer->Unlock();

	SetType(TYPE_WALL);

	return S_OK;
}
//==============================================
//�V�����_�[�̏I������
//==============================================
void CCylinder::Uninit(void)
{
	if (m_pVtxBuffer != NULL)
	{//�o�b�t�@�̔j��
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}

	//�I�u�W�F�N�g�̉������
	CObject::Release();
}
//==============================================
//�V�����_�[�̃�������������
//==============================================
CCylinder *CCylinder::Create(void)
{
	CCylinder *pCylinder;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pCylinder = new CCylinder;

	if (pCylinder != NULL)
	{
		//����������
		pCylinder->Init();
	}

	return pCylinder;
}
//==============================================
//�V�����_�[�̍X�V����
//==============================================
void CCylinder::Update(void)
{

}
//==============================================
//�V�����_�[�̕`�揈��
//==============================================
void CCylinder::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffer);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);

	//�|���S���`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MESH_SPLIT * 2 + 2), 0, (MESH_SPLIT * 2 + 2));
}
//==============================================
//�e�N�X�`���̊��蓖��
//==============================================
void CCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//==============================================
//�ʒu�ݒ菈��
//==============================================
void CCylinder::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ʒu���
	m_pos = pos;
}