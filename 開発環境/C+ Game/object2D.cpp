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
#include"object2D.h"

//****************//
//   �}�N����`   //
//****************//
#define VECTOR_INIT			(D3DXVECTOR3(0.0f,0.0f, 0.0f))		//�ʒuY�̏����l
//==============================================
//�R���X�g���N�^
//==============================================
CObject2D::CObject2D()
{
	//�����ݒ�
	m_pTexture = NULL;		//�e�N�X�`���̃|�C���^
	m_pVtxBuffer = NULL;	//�o�b�t�@�̃|�C���^

	m_pos = POS_INIT;		//�ʒu
	m_move = VECTOR_INIT;	//�ʒu
	m_rot = VECTOR_INIT;	//�p�x
	m_scale = SCALE_INIT;	//�傫��
}
//==============================================
//�f�X�X�g���N�^
//==============================================
CObject2D::~CObject2D()
{

}
//==============================================
//2D�I�u�W�F�N�g�̏���������
//==============================================
HRESULT CObject2D::Init(void)
{
	//�����_�[�̏��擾
	CRenderer *pRenderer = CManager::GetRenderer();

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_2D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - SCALE_INIT.x, m_pos.y - SCALE_INIT.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + SCALE_INIT.x, m_pos.y - SCALE_INIT.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - SCALE_INIT.x, m_pos.y + SCALE_INIT.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + SCALE_INIT.x, m_pos.y + SCALE_INIT.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
//2D�I�u�W�F�N�g�̏I������
//==============================================
void CObject2D::Uninit(void)
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
//2D�I�u�W�F�N�g�̃�������������
//==============================================
CObject2D *CObject2D::Create(void)
{
	CObject2D *pObject2D;	//2D�I�u�W�F�N�g�̃C���X�^���X����

	//����������
	pObject2D = new CObject2D;

	if (pObject2D != NULL)
	{
		//����������
		pObject2D->Init();
	}

	return pObject2D;
}
//==============================================
//2D�I�u�W�F�N�g�̍X�V����
//==============================================
void CObject2D::Update(void)
{
	
}
//==============================================
//2D�I�u�W�F�N�g�̕`�揈��
//==============================================
void CObject2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	if (GetType() == TYPE_EFFECT)
	{
		//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (GetType() == TYPE_EFFECT)
	{
		//�A���t�@�u�����f�B���O���f�t�H���g�ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
//==============================================
//�ʒu�ݒ菈��
//==============================================
void CObject2D::SetPos(D3DXVECTOR3 pos , D3DXVECTOR3 scale)
{
	//�ʒu���
	m_pos = pos; 

	m_scale = scale;

	VERTEX_2D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_scale.x, m_pos.y + m_scale.y, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}
//==============================================
//�ʒu�ݒ菈��
//==============================================
void CObject2D::SetGauge(float Gauge)
{
	VERTEX_2D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Gauge, m_pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_scale.x, m_pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Gauge, m_pos.y + m_scale.y, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}
//==============================================
//�e�N�X�`�����W�ݒ菈��
//==============================================
void CObject2D::SetTex(D3DXVECTOR2	tex,float Anim)
{
	VERTEX_2D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	///�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((tex.x - (1.0f / Anim)), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((tex.x - (1.0f / Anim)), tex.y);
	pVtx[3].tex = D3DXVECTOR2(tex.x, tex.y);
	
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}
//==============================================
//�F�ݒ菈��
//==============================================
void CObject2D::SetCol(D3DXCOLOR Col,float fRadius)
{
	VERTEX_2D *pVtx;	//2D�o�b�t�@�̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
     m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);
	pVtx[1].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);
	pVtx[2].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);
	pVtx[3].col = D3DXCOLOR(Col.r, Col.g, Col.b, Col.a + fRadius);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuffer->Unlock();
}
//==============================================
//�e�N�X�`���̊��蓖��
//==============================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
