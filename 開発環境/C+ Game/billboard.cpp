//==============================================
//
//�r���{�[�h(billboard.cpp)
//Author: fujiwara ryuki
//
//==============================================
#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"Billboard.h"
#include"pause.h"

//****************//
//   �}�N����`   //
//****************//
#define BILLBOARD_WIDTH		(10)
#define BILLBOARD_HEIGHT	(10)
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f,0.0f))		//�ʒuY�̏����l

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CBillboard::m_pTexture = NULL;
//==============================================
//�R���X�g���N�^
//==============================================
CBillboard::CBillboard()
{
	//�����ݒ�
	m_pTexture = NULL;		//�e�N�X�`���̃|�C���^
	m_pVtxBuffer = NULL;	//�o�b�t�@�̃|�C���^

	m_pos = VECTOR_INIT;		//�ʒu
	m_scale = SCALE_INIT;	//�傫��
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CBillboard::~CBillboard()
{

}
//==============================================
//�r���{�[�h�̏���������
//==============================================
HRESULT CBillboard::Init(void)
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_3D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍��W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, +BILLBOARD_HEIGHT, +BILLBOARD_HEIGHT);
	pVtx[1].pos = D3DXVECTOR3(+BILLBOARD_WIDTH, +BILLBOARD_HEIGHT, +BILLBOARD_HEIGHT);
	pVtx[2].pos = D3DXVECTOR3(-BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, -BILLBOARD_HEIGHT);
	pVtx[3].pos = D3DXVECTOR3(+BILLBOARD_WIDTH, -BILLBOARD_HEIGHT, -BILLBOARD_HEIGHT);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();

	return S_OK;
}
//==============================================
//�r���{�[�h�̏I������
//==============================================
void CBillboard::Uninit(void)
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
//�r���{�[�h�̃�������������
//==============================================
CBillboard *CBillboard::Create(void)
{
	CBillboard *pBillboard;	//�r���{�[�h�̃C���X�^���X����

	//����������
	pBillboard = new CBillboard;

	if (pBillboard != NULL)
	{
		//����������
		pBillboard->Init();
	}

	return pBillboard;
}
//==============================================
//�r���{�[�h�̍X�V����
//==============================================
void CBillboard::Update(void)
{

}
//==============================================
//�r���{�[�h�̕`�揈��
//==============================================
void CBillboard::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();																			
	
	D3DXMATRIX		  mtxTrans;		 //�v�Z�p�}�g���b�N�X
	D3DXMATRIX		  mtxView;		 //�r���[�}�g���b�N�X�擾�p

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����Ɍ�����
	D3DXMatrixInverse(&m_mtxworld, NULL, &mtxView);		//�t�s������߂�
	m_mtxworld._41 = 0.0f;
	m_mtxworld._42 = 0.0f;
	m_mtxworld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	//���_�o�b�t�@�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//�A���t�@�u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
//==============================================
//�ʒu�ݒ菈��
//==============================================
void CBillboard::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//�ʒu���
	m_pos = pos;

	m_scale = scale;

	VERTEX_3D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_scale.x,+m_scale.y,+m_scale.y);
	pVtx[1].pos = D3DXVECTOR3(+m_scale.x,+m_scale.y,+m_scale.y);
	pVtx[2].pos = D3DXVECTOR3(-m_scale.x,-m_scale.y,-m_scale.y);
	pVtx[3].pos = D3DXVECTOR3(+m_scale.x,-m_scale.y,-m_scale.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}
//==============================================
//�F�ݒ菈��
//==============================================
void CBillboard::SetCol(D3DXCOLOR Col, float fRadius)
{
	m_col = Col;

	VERTEX_3D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);
	pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);
	pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);
	pVtx[3].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b,fRadius);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}
//==============================================
//�e�N�X�`���̊��蓖��
//==============================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
