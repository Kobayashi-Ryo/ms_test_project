//=============================================================================
//
// 頂点宣言
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CVertexDeclaration.h"
#include "CDeviceHolder.h"
#include <common/DebugUtil.h>

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    // 独自定義とDirectX定数の対応
    static const BYTE DECL_TYPE[] =
    {
        D3DDECLTYPE_FLOAT1   ,
        D3DDECLTYPE_FLOAT2   ,
        D3DDECLTYPE_FLOAT3   ,
        D3DDECLTYPE_FLOAT4   ,
        D3DDECLTYPE_D3DCOLOR ,

        D3DDECLTYPE_UBYTE4   ,
        D3DDECLTYPE_SHORT2   ,
        D3DDECLTYPE_SHORT4   ,

        D3DDECLTYPE_UBYTE4N  ,
        D3DDECLTYPE_SHORT2N  ,
        D3DDECLTYPE_SHORT4N  ,
        D3DDECLTYPE_USHORT2N ,
        D3DDECLTYPE_USHORT4N ,
        D3DDECLTYPE_UDEC3    ,
        D3DDECLTYPE_DEC3N    ,
        D3DDECLTYPE_FLOAT16_2,
        D3DDECLTYPE_FLOAT16_4,
        D3DDECLTYPE_UNUSED   ,
    };

    static const BYTE DECL_USAGE[] =
    {
        D3DDECLUSAGE_POSITION,
        D3DDECLUSAGE_BLENDWEIGHT,
        D3DDECLUSAGE_BLENDINDICES,
        D3DDECLUSAGE_NORMAL,
        D3DDECLUSAGE_PSIZE,
        D3DDECLUSAGE_TEXCOORD,
        D3DDECLUSAGE_TANGENT,
        D3DDECLUSAGE_BINORMAL,
        D3DDECLUSAGE_TESSFACTOR,
        D3DDECLUSAGE_POSITIONT,
        D3DDECLUSAGE_COLOR,
        D3DDECLUSAGE_FOG,
        D3DDECLUSAGE_DEPTH,
        D3DDECLUSAGE_SAMPLE,
    };

    const D3DVERTEXELEMENT9 DECL_END[] =
    {
        D3DDECL_END()
    };
};

CVertexDeclaration::CVertexDeclaration()
    : m_pDecl(nullptr)
    , m_pDev(nullptr)
{
}

CVertexDeclaration::~CVertexDeclaration()
{
    SafeRelease(m_pDecl);
}

CVertexDeclaration* CVertexDeclaration::Create(CDeviceHolder* pHolder, u8 uNumElems, const VertexDeclarationDesc* pDesc)
{
    CVertexDeclaration* pDecl = new CVertexDeclaration();

    if(pDecl)
    {
        INIT_CHECK(pDecl->Init(pHolder, uNumElems, pDesc));
        _PrintConsole("頂点宣言");
    }

    return pDecl;
}

void CVertexDeclaration::Release()
{
    delete this;
}

LPDIRECT3DVERTEXDECLARATION9 CVertexDeclaration::GetPointer() const
{
    return m_pDecl;
}

void CVertexDeclaration::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

void CVertexDeclaration::Attach()
{
    m_pDev->SetVertexDeclaration(m_pDecl);
}

void CVertexDeclaration::Detach()
{
    m_pDev->SetVertexDeclaration(nullptr);
}

HRESULT CVertexDeclaration::Init(CDeviceHolder* pHolder, u8 uNumDescs, const VertexDeclarationDesc* pDesc)
{
    D3DVERTEXELEMENT9 *pElem = new D3DVERTEXELEMENT9[uNumDescs + 1];

    for(u8 i = 0; i < uNumDescs; i++)
    {
        pElem[i].Stream     = pDesc[i].Stream;
        pElem[i].Offset     = pDesc[i].Offset;
        pElem[i].Type       = DECL_TYPE[pDesc[i].Type];
        pElem[i].Method     = D3DDECLMETHOD_DEFAULT;
        pElem[i].Usage      = DECL_USAGE[pDesc[i].Usage];
        pElem[i].UsageIndex = pDesc[i].UsageIndex;
    }

    pElem[uNumDescs] = DECL_END[0];

    m_pDev = pHolder->GetDevice();

    m_pDev->CreateVertexDeclaration(
        pElem,
        &m_pDecl);
    _Assert(m_pDecl);

    SafeDeleteArray(pElem);

    return S_OK;
}

// EOF
