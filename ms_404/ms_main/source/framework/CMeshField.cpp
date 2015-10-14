//=============================================================================
//
// ���b�V���t�B�[���h
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CMeshField.h"
#include <system/IVertexBuffer.h>
#include <system/IVertexDeclaration.h>
#include <system/IIndexBuffer.h>
#include <system/ITexture.h>
#include "CApplication.h"

#include <common/DebugUtil.h>

CMeshField::CMeshField()
    : m_pVtxBuff(nullptr)
    , m_pDecl(nullptr)
    , m_pIdxBuff(nullptr)
    , m_pTex(nullptr)
    , m_uNumVtxX(2)
    , m_uNumVtxZ(2)
    , m_uNumPrimitive(2)
    , m_fWidth(1.0f)
    , m_fDepth(1.0f)
{
}

CMeshField::~CMeshField()
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

// ����
CMeshField* CMeshField::Create(const MeshFieldDesc& desc)
{
    CMeshField* p = new CMeshField();

    if(!p->Init(desc))
    {
        p->Release();
        return nullptr;
    }

    return p;
}

// �`��
void CMeshField::Draw()
{
    m_pVtxBuff->Attach();
    m_pIdxBuff->Attach();
    m_pDecl->Attach();
    m_pTex->Attach(); // �����T���v���[�N���X�ɂ���������������
    
    auto dev = CApplication::GetInstance()->GetSystem()->GetDeviceHolder()->GetDevice();
    HRESULT hr = dev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_uNumVtxX * m_uNumVtxZ, 0, m_uNumPrimitive);
    _Assert(SUCCEEDED(hr));

    m_pVtxBuff->Detach();
    m_pIdxBuff->Detach();
    m_pDecl->Detach();
    m_pTex->Detach();
}

// X�������_��
u32 CMeshField::GetNumVertexX() const
{
    return m_uNumVtxX;
}

// Z�������_��
u32 CMeshField::GetNumVertexZ() const
{
    return m_uNumVtxZ;
}

// ���_�o�b�t�@����
void CMeshField::ControlVertex(std::function<void(Vertex3D*, u32, u32)> func)
{
    Vertex3D* pVtx = nullptr;

    m_pVtxBuff->Lock((void**)&pVtx);

    func(pVtx, m_uNumVtxX, m_uNumVtxZ);

    m_pVtxBuff->Unlock();
}

// �����擾
f32 CMeshField::GetWidth() const
{
    return m_fWidth;
}

// ���s�擾
f32 CMeshField::GetDepth() const
{
    return m_fDepth;
}

// ������
bool CMeshField::Init(const MeshFieldDesc& desc)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();

    m_pTex = res->GetTexture(desc.textureName);

    // ���_���ݒ�
    m_uNumVtxX = desc.numXGrid + 1;
    m_uNumVtxZ = desc.numZGrid + 1;
    // �v���~�e�B�u���ݒ�
    m_uNumPrimitive = (desc.numXGrid * 2) * desc.numZGrid + 4 * (desc.numZGrid - 1);

    // ���_�o�b�t�@
    VertexBufferDesc vtxDesc;
    vtxDesc.Size = sizeof(Vertex3D) * m_uNumVtxX * m_uNumVtxZ;
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
    idxDesc.Size = sizeof(u16) * 2 * (desc.numZGrid * (desc.numXGrid + 2) - 1);
    idxDesc.Usage = IDXUSAGE_WRITEONLY;
    idxDesc.Pool = IDXPOOL_MANAGED;
    idxDesc.Format = IDXFMT_INDEX16; // 16�ł����C������
    m_pIdxBuff = res->GetIndexBuffer(idxDesc);
    _Assert(m_pIdxBuff);

    // ���_�A�N�Z�X�p�|�C���^
    Vertex3D *pVtx = nullptr;
    // ���_���b�N
    m_pVtxBuff->Lock((void**)&pVtx);
    // ���_������
    //f32 fTexDiffX = 1.0f / desc.widthGrid;
    //f32 fTexDiffZ = 1.0f / desc.depthGrid;
    for(s32 z = 0; z <= desc.numZGrid; z++)
    {
        for(s32 x = 0; x <= desc.numXGrid; x++)
        {
            s32 nIndex = z * (desc.numXGrid + 1) + x;
            // ���_���W�Z�o
            pVtx[nIndex].pos.x = (f32)( x * desc.widthGrid - desc.numXGrid * desc.widthGrid * 0.5f);
            pVtx[nIndex].pos.y = 0.0f;
            pVtx[nIndex].pos.z = (f32)(-z * desc.depthGrid + desc.numZGrid * desc.depthGrid * 0.5f);

            pVtx[nIndex].normal.x = pVtx[nIndex].normal.z = 0.0f;
            pVtx[nIndex].normal.y = 1.0f;

            // �e�N�X�`�����W�Z�o(�K������)
            pVtx[nIndex].texcoord = vec2((f32)x, (f32)z);
        }
    }
    m_pVtxBuff->Unlock();

    
    // �C���f�b�N�X�A�N�Z�X�p�|�C���^
    u16 *pIdx = nullptr;
    // �C���f�b�N�X�o�b�t�@���b�N
    m_pIdxBuff->Lock((void**)&pIdx);

#ifdef _DEBUG    // �f�o�b�O�E�H�b�`�p
    u16 *pIdxDbg = pIdx;
#endif
    
    for(u16 z = 0; z < desc.numZGrid; z++)
    {
        for(u16 x = 0; x < desc.numXGrid + 1; x++)
        {
            pIdx[x * 2    ] = (z + 1) * (desc.numXGrid + 1) + x;
            pIdx[x * 2 + 1] =  z      * (desc.numXGrid + 1) + x;
        }

        if(z < (desc.numZGrid - 1))
        {
            // �k�ރ|���S���p�̃C���f�b�N�X��ݒ�
            pIdx[(desc.numXGrid + 1) * 2    ] =  z *      (desc.numXGrid + 1) + desc.numXGrid;
            pIdx[(desc.numXGrid + 1) * 2 + 1] = (z + 2) * (desc.numXGrid + 1);
        }

        pIdx += ((desc.numXGrid + 1) * 2 + 2);
    }
    m_pIdxBuff->Unlock();

    // ���_�錾
    VertexDeclarationDesc decl[] =
    {
        {0, 0, VDDECLTYPE_FLOAT3, VDDECLUSAGE_POSITION, 0},
        {0, 12, VDDECLTYPE_FLOAT3, VDDECLUSAGE_NORMAL, 0},
        {0, 24, VDDECLTYPE_FLOAT2, VDDECLUSAGE_TEXCOORD, 0},
    };
    u8 declSize = sizeof(decl) / sizeof(decl[0]);
    m_pDecl = res->GetVertexDeclaration(declSize, decl);

    return true;
}

// EOF
