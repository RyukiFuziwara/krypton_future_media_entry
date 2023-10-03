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
#include"object3D.h"

//****************//
//   �}�N����`   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))	//�ʒuY�̏����l
#define MESH_SPLIT			(32)							//������
#define CENTER_AND_ONELAP	(2)								//���S�_�ƂP���ŏd�Ȃ�_
#define MESH_ALL_VERTEX		(MESH_SPLIT + 1)				//���ӂ̕����n�_�ƒ��S
#define MESH_ALL_INDEX		(MESH_SPLIT + 2)				//���ӂ̕����n�_�ƒ��S�E�P���ŏd�Ȃ�_
#define MESH_WIDTH			(2000.0f)						//�n�ʂ̉���
#define MESH_HEIGHT			(2000.0f)						//�n�ʂ̏c��
#define MESH_RADIUS			(MESH_HEIGHT)			//���a

//�ÓI�����o�ϐ��錾
D3DXVECTOR3 CObject3D::m_pos = {};
float CObject3D::m_fRadius = 0.0f;

//==============================================
//�R���X�g���N�^
//==============================================
CObject3D::CObject3D()
{
	//�����ݒ�
	m_pTexture = NULL;		//�e�N�X�`���̃|�C���^
	m_pVtxBuffer = NULL;	//�o�b�t�@�̃|�C���^
	m_pIdxBuffer = NULL;

	m_pos = VECTOR_INIT;		//�ʒu
	m_rot = VECTOR_INIT;		//�p�x
	m_scale = SCALE_INIT * 10;	//�傫��

	m_fRadius = MESH_RADIUS;
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CObject3D::~CObject3D()
{

}
//==============================================
//3D�I�u�W�F�N�g�̏���������
//==============================================
HRESULT CObject3D::Init(void)
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Tile.jpg",
		&m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESH_ALL_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_�ԍ�
	int nNumVtx = 0;

	float Rot = D3DX_PI;	//�p�x

	pVtx[nNumVtx].pos = VECTOR_INIT;						//���S���W���
	pVtx[nNumVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�@��
	pVtx[nNumVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	pVtx[nNumVtx].tex = D3DXVECTOR2(0.5f, 0.5f);			//�e�N�X�`�����W

	nNumVtx++;

	//���ӂ̒��_���̐ݒ�
	for (int nCntVtx = 0; nCntVtx < MESH_SPLIT; nCntVtx++, nNumVtx++)
	{
		pVtx[nNumVtx].pos = D3DXVECTOR3(
			sinf(Rot) * MESH_WIDTH,			//X�̈ʒu
			0.0f,							//Y�̈ʒu
			cosf(Rot) * MESH_HEIGHT);		//Z�̈ʒu

		pVtx[nNumVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nNumVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		float aTexU = 0.5f - 0.5f * sinf(Rot);	//�e�N�X�`����
		float aTexV = 0.5f - 0.5f * cosf(Rot);	//�e�N�X�`������

		pVtx[nNumVtx].tex = D3DXVECTOR2(aTexU, aTexV);

		//�p�x���@�S�̂̊p�x���������Ŋ������������A����
		Rot -= (D3DX_PI * 2.0f) / MESH_SPLIT;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESH_ALL_INDEX,
		D3DUSAGE_WRITEONLY, 
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffer,
		NULL);

	//�C���f�b�N�X���ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pIdxBuffer->Lock(0, 0, (void**)&pIdx, 0);

	for (int nNumIdx = 0; nNumIdx < MESH_ALL_INDEX; nNumIdx++)
	{
		//���̌v�Z���ł́A�@���傤��1������Ƃ��ɓ�����1�ɂȂ�@�@����ȊO�ł́A�J�E���^�[���������@�̗]�肪�ԍ��Ƃ��Đݒ肳���
		pIdx[nNumIdx] = (nNumIdx / (MESH_ALL_INDEX - 1)) + (nNumIdx % (MESH_ALL_INDEX - 1));
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuffer->Unlock();

	SetType(TYPE_STAGE);

	return S_OK;
}
//==============================================
//3D�I�u�W�F�N�g�̏I������
//==============================================
void CObject3D::Uninit(void)
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
//3D�I�u�W�F�N�g�̃�������������
//==============================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObject3D;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pObject3D = new CObject3D;

	if (pObject3D != NULL)
	{
		//����������
		pObject3D->Init();
	}

	return pObject3D;
}
//==============================================
//3D�I�u�W�F�N�g�̍X�V����
//==============================================
void CObject3D::Update(void)
{
}
//==============================================
//3D�I�u�W�F�N�g�̕`�揈��
//==============================================
void CObject3D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	//���ʃJ�����O��ON
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

	//�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN,0,0, MESH_ALL_VERTEX,0, MESH_SPLIT);

	//���ʂ̃J�����O���[�h�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//==============================================
//3D�I�u�W�F�N�g�̓����蔻�菈��
//==============================================
bool CObject3D::CollisionStage(D3DXVECTOR3 pos)
{
	bool bColli = false;

	//���݁E�O��̈ʒu�ƃt�B�[���h�̒��S�ʒu�̍����i�[
	D3DXVECTOR2 PosDiff;

	PosDiff.x = powf(m_pos.x - pos.x, 2.0f);	//���݂̂w���W�̍��̂Q��
	PosDiff.y = powf(m_pos.z - pos.z, 2.0f);	//���݂̂y���W�̍��̂Q��	�ϐ���  "�x" �����ǁA�y���W�̍������܂� 

	float fLength = sqrtf(PosDiff.x + PosDiff.y);	//���݂̂w�E�y�̒������擾

	if (fLength >= m_fRadius)
	{//���S�ʒu����̋������t�B�[���h�̔��a�ȏゾ����

		bColli = true;
	}

	return bColli;
}
//==============================================
//�e�N�X�`���̊��蓖��
//==============================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
//==============================================
//�ʒu�ݒ菈��
//==============================================
void CObject3D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ʒu���
	m_pos = pos;
}