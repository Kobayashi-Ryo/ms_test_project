//=============================================================================
//
// ����
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CSphere.h"
#include "CApplication.h"
#include <common/DebugUtil.h>

CSphere::CSphere()
    : m_pVtxBuff(nullptr)
    , m_pDecl(nullptr)
    , m_pIdxBuff(nullptr)
    , m_pTex(nullptr)
    , m_color(1,1,1,1)
    , m_fRadius(1.0f)
    , m_uDiv(8)
    , m_uNumVertex(0)
    , m_uNumPrimitive(0)
    , m_bSphereUpdate(true)
{
}

CSphere::~CSphere()
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    res->Release(m_pVtxBuff);
    res->Release(m_pDecl);
    res->Release(m_pIdxBuff);
    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        res->Release(m_pTex);
    }
}

CSphere* CSphere::Create()
{
    return Create(SphereDesc(), "white.tga");
}

CSphere* CSphere::Create(const SphereDesc& desc, cs8* pFileName)
{
    CSphere* pObj = new CSphere();

    if(pObj)
    {
        bool suc = pObj->Init(desc, pFileName);
        _Assert(suc);
        _PrintConsole("����\n");
    }

    return pObj;
}

// �`��
void CSphere::Draw()
{
    m_pVtxBuff->Attach();
    m_pIdxBuff->Attach();
    m_pDecl->Attach();
    m_pTex->Attach();
    
    auto dev = CApplication::GetInstance()->GetSystem()->GetDeviceHolder()->GetDevice();
    HRESULT hr = dev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_uNumVertex, 0, m_uNumPrimitive);
    _Assert(SUCCEEDED(hr));

    m_pVtxBuff->Detach();
    m_pIdxBuff->Detach();
    m_pDecl->Detach();
    m_pTex->Detach();
}

// �F�ݒ�
void CSphere::SetColor(const D3DXCOLOR& color){ SetColor(color.r, color.g, color.b); }
void CSphere::SetColor(cf32 r, cf32 g, cf32 b){ m_bSphereUpdate = true; m_color.r = r; m_color.g = g; m_color.b = b; }
// �F�擾
const D3DXCOLOR& CSphere::GetColor() const { return m_color; }

// �A���t�@�l�ݒ�
void CSphere::SetAlpha(cf32 a){ m_bSphereUpdate = true; m_color.a = a; }
// �A���t�@�l�擾
f32 CSphere::GetAlpha() const { return m_color.a; }

// �e�N�X�`���ݒ�
void CSphere::SetTexture(cs8* pFileName)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    if(!m_pTex)
    {
        return;
    }

    ITexture* pTex = res->GetTexture(pFileName);
    if(!pTex) return;

    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        res->Release(m_pTex);
    }

    m_pTex = pTex;
}

void CSphere::SetTexture(ITexture* pTex)
{
    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        auto res = CApplication::GetInstance()->GetSystem()->GetResource();
        res->Release(m_pTex);
    }

    m_pTex = pTex;
}

// ���a�ݒ�
void CSphere::SetRadius(cf32 radius)
{
    m_fRadius = radius;
}
// ���a�擾
f32 CSphere::GetRadius() const
{
    return m_fRadius;
}

// ������
bool CSphere::Init(const SphereDesc& desc, cs8* pFileName)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    m_pTex = res->GetTexture(pFileName);
    m_uDiv = desc.div;
    m_color = desc.color;
    m_fRadius = desc.radius;

    SetPosition(desc.center);

    // ���_��
    m_uNumVertex = (m_uDiv + 1) * (m_uDiv + 1);
    // �v���~�e�B�u��
    //m_uNumPrimitive = 2 * m_uDiv * (m_uDiv -1);
    m_uNumPrimitive = (m_uDiv * 2) * m_uDiv + 4 * (m_uDiv - 1);
    
    // ���_�o�b�t�@
    VertexBufferDesc vtxDesc;
    vtxDesc.Size = sizeof(Vertex3D) * m_uNumVertex;
    vtxDesc.Usage = VTXUSAGE_WRITEONLY;
    vtxDesc.Pool = VTXPOOL_MANAGED;
    m_pVtxBuff = res->GetVertexBuffer(vtxDesc);
    _Assert(m_pVtxBuff);
    // �p�����[�^�ݒ�
    m_pVtxBuff->SetStreamIndex(0);
    m_pVtxBuff->SetOffset(0);
    m_pVtxBuff->SetStride(sizeof(Vertex3D));
    
    // �C���f�b�N�X�o�b�t�@
    IndexBufferDesc idxDesc;
    // (col + 1) * 2 * row + (row - 1) * 2 ���܂Ƃ߂�
    idxDesc.Size = sizeof(u16) * 2 * (m_uDiv * (m_uDiv + 2) - 1);
    idxDesc.Usage = IDXUSAGE_WRITEONLY;
    idxDesc.Pool = IDXPOOL_MANAGED;
    idxDesc.Format = IDXFMT_INDEX16;
    m_pIdxBuff = res->GetIndexBuffer(idxDesc);
    _Assert(m_pIdxBuff);

    SetSphere(desc.outside);

    return true;
}

// �o�b�t�@�X�V
void CSphere::SetSphere(bool bOutside)
{
    f32 fOutsideMultipler;
    if(bOutside)
    {
        // �O��
        fOutsideMultipler = 1.0f;
    }
    else
    {
        // ����
        fOutsideMultipler = -1.0f;
    }
    
    f32 fRatio = 1.0f;
    // �~����ɒ��_��łꏊ�̉~����̊Ԋu
    f32 fThetaFragment = (2.0f * D3DX_PI) / m_uDiv;
    // �~�̍����̊Ԋu
    f32 fHeightRadianFragment = D3DX_PI / m_uDiv;
    // �e�N�X�`���̉����̊Ԋu
    f32 fTexWidthFragment = 1.0f / m_uDiv;
    // �e�N�X�`���̏c���̊Ԋu
    f32 fTexHeightFragment = 1.0f / m_uDiv;
    // �@��
    vec3 tempNormal;

    // ���_�A�N�Z�X�p�|�C���^
    Vertex3D *pVtx = NULL;
    // ���_���b�N
    m_pVtxBuff->Lock((void**)&pVtx);
    for(int y = 0; y <= m_uDiv; y++)
    {
        // �~�̍���
        f32 fCircleHeight = m_fRadius * fRatio * cosf(fHeightRadianFragment * y);
        for(int x = 0; x <= m_uDiv; x++)
        {
            // �C���f�b�N�X
            int nIndex = y * (m_uDiv + 1) + x;
            // �~�̔��a
            f32 fCircleRadius = m_fRadius * sinf(fHeightRadianFragment * y);
            // ���_���W
            pVtx[nIndex].pos.x = fCircleRadius * sinf(fOutsideMultipler * -fThetaFragment * x);
            pVtx[nIndex].pos.y = fCircleHeight;
            pVtx[nIndex].pos.z = fCircleRadius * cosf(fOutsideMultipler * -fThetaFragment * x);

            // �@���ݒ�
            D3DXVec3Normalize(&tempNormal, &pVtx[nIndex].pos);
            // �C�ӂ̕�������������
            pVtx[nIndex].normal = tempNormal;
            pVtx[nIndex].normal *= fOutsideMultipler;

            // �e�N�X�`�����W
            pVtx[nIndex].texcoord = D3DXVECTOR2((f32)x * fTexWidthFragment, (f32)y * fTexHeightFragment);
        }
    }
    // �A�����b�N
    m_pVtxBuff->Unlock();
    
    // �C���f�b�N�X�A�N�Z�X�p�|�C���^
    u16 *pIdx = NULL;
    // �C���f�b�N�X�o�b�t�@���b�N
    m_pIdxBuff->Lock((void**)&pIdx);

#ifdef _DEBUG    // �f�o�b�O�E�H�b�`�p
    u16 *pIdxDbg = pIdx;
#endif
    
    // �C���f�b�N�X�ݒ�
    for(u16 y = 0; y < m_uDiv; y++)
    {
        pIdx[0] = (y + 1) * (m_uDiv + 1);
        for(u16 x = 0; x < m_uDiv; x++)
        {
            pIdx[x * 2 + 1]    = y * (m_uDiv + 1) + x;
            pIdx[x * 2 + 2]    = (y + 1) * (m_uDiv + 1) + (x + 1);
        }
        pIdx[m_uDiv * 2 + 1] = y * (m_uDiv + 1) + m_uDiv;

        if(y != (m_uDiv - 1))
        {
            pIdx[m_uDiv * 2 + 2] = y * (m_uDiv + 1) + m_uDiv;
            pIdx[m_uDiv * 2 + 3] = (y + 2) * (m_uDiv + 1);
        }
        // �A�h���X�̃C���N�������g
        pIdx += (m_uDiv * 2 + 4);
    }

    // �A�����b�N
    m_pIdxBuff->Unlock();
    
    // ���_�錾
    VertexDeclarationDesc decl[] =
    {
        {0, 0, VDDECLTYPE_FLOAT3, VDDECLUSAGE_POSITION, 0},
        {0, 12, VDDECLTYPE_FLOAT3, VDDECLUSAGE_NORMAL, 0},
        {0, 24, VDDECLTYPE_FLOAT2, VDDECLUSAGE_TEXCOORD, 0},
    };
    u8 declSize = sizeof(decl) / sizeof(decl[0]);
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    m_pDecl = res->GetVertexDeclaration(declSize, decl);
}

// EOF
