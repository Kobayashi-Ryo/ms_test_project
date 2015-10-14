//=============================================================================
//
// 球体
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
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
        _PrintConsole("球体\n");
    }

    return pObj;
}

// 描画
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

// 色設定
void CSphere::SetColor(const D3DXCOLOR& color){ SetColor(color.r, color.g, color.b); }
void CSphere::SetColor(cf32 r, cf32 g, cf32 b){ m_bSphereUpdate = true; m_color.r = r; m_color.g = g; m_color.b = b; }
// 色取得
const D3DXCOLOR& CSphere::GetColor() const { return m_color; }

// アルファ値設定
void CSphere::SetAlpha(cf32 a){ m_bSphereUpdate = true; m_color.a = a; }
// アルファ値取得
f32 CSphere::GetAlpha() const { return m_color.a; }

// テクスチャ設定
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

// 半径設定
void CSphere::SetRadius(cf32 radius)
{
    m_fRadius = radius;
}
// 半径取得
f32 CSphere::GetRadius() const
{
    return m_fRadius;
}

// 初期化
bool CSphere::Init(const SphereDesc& desc, cs8* pFileName)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();
    m_pTex = res->GetTexture(pFileName);
    m_uDiv = desc.div;
    m_color = desc.color;
    m_fRadius = desc.radius;

    SetPosition(desc.center);

    // 頂点数
    m_uNumVertex = (m_uDiv + 1) * (m_uDiv + 1);
    // プリミティブ数
    //m_uNumPrimitive = 2 * m_uDiv * (m_uDiv -1);
    m_uNumPrimitive = (m_uDiv * 2) * m_uDiv + 4 * (m_uDiv - 1);
    
    // 頂点バッファ
    VertexBufferDesc vtxDesc;
    vtxDesc.Size = sizeof(Vertex3D) * m_uNumVertex;
    vtxDesc.Usage = VTXUSAGE_WRITEONLY;
    vtxDesc.Pool = VTXPOOL_MANAGED;
    m_pVtxBuff = res->GetVertexBuffer(vtxDesc);
    _Assert(m_pVtxBuff);
    // パラメータ設定
    m_pVtxBuff->SetStreamIndex(0);
    m_pVtxBuff->SetOffset(0);
    m_pVtxBuff->SetStride(sizeof(Vertex3D));
    
    // インデックスバッファ
    IndexBufferDesc idxDesc;
    // (col + 1) * 2 * row + (row - 1) * 2 をまとめた
    idxDesc.Size = sizeof(u16) * 2 * (m_uDiv * (m_uDiv + 2) - 1);
    idxDesc.Usage = IDXUSAGE_WRITEONLY;
    idxDesc.Pool = IDXPOOL_MANAGED;
    idxDesc.Format = IDXFMT_INDEX16;
    m_pIdxBuff = res->GetIndexBuffer(idxDesc);
    _Assert(m_pIdxBuff);

    SetSphere(desc.outside);

    return true;
}

// バッファ更新
void CSphere::SetSphere(bool bOutside)
{
    f32 fOutsideMultipler;
    if(bOutside)
    {
        // 外側
        fOutsideMultipler = 1.0f;
    }
    else
    {
        // 内側
        fOutsideMultipler = -1.0f;
    }
    
    f32 fRatio = 1.0f;
    // 円周上に頂点を打つ場所の円周上の間隔
    f32 fThetaFragment = (2.0f * D3DX_PI) / m_uDiv;
    // 円の高さの間隔
    f32 fHeightRadianFragment = D3DX_PI / m_uDiv;
    // テクスチャの横幅の間隔
    f32 fTexWidthFragment = 1.0f / m_uDiv;
    // テクスチャの縦幅の間隔
    f32 fTexHeightFragment = 1.0f / m_uDiv;
    // 法線
    vec3 tempNormal;

    // 頂点アクセス用ポインタ
    Vertex3D *pVtx = NULL;
    // 頂点ロック
    m_pVtxBuff->Lock((void**)&pVtx);
    for(int y = 0; y <= m_uDiv; y++)
    {
        // 円の高さ
        f32 fCircleHeight = m_fRadius * fRatio * cosf(fHeightRadianFragment * y);
        for(int x = 0; x <= m_uDiv; x++)
        {
            // インデックス
            int nIndex = y * (m_uDiv + 1) + x;
            // 円の半径
            f32 fCircleRadius = m_fRadius * sinf(fHeightRadianFragment * y);
            // 頂点座標
            pVtx[nIndex].pos.x = fCircleRadius * sinf(fOutsideMultipler * -fThetaFragment * x);
            pVtx[nIndex].pos.y = fCircleHeight;
            pVtx[nIndex].pos.z = fCircleRadius * cosf(fOutsideMultipler * -fThetaFragment * x);

            // 法線設定
            D3DXVec3Normalize(&tempNormal, &pVtx[nIndex].pos);
            // 任意の方向を向かせる
            pVtx[nIndex].normal = tempNormal;
            pVtx[nIndex].normal *= fOutsideMultipler;

            // テクスチャ座標
            pVtx[nIndex].texcoord = D3DXVECTOR2((f32)x * fTexWidthFragment, (f32)y * fTexHeightFragment);
        }
    }
    // アンロック
    m_pVtxBuff->Unlock();
    
    // インデックスアクセス用ポインタ
    u16 *pIdx = NULL;
    // インデックスバッファロック
    m_pIdxBuff->Lock((void**)&pIdx);

#ifdef _DEBUG    // デバッグウォッチ用
    u16 *pIdxDbg = pIdx;
#endif
    
    // インデックス設定
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
        // アドレスのインクリメント
        pIdx += (m_uDiv * 2 + 4);
    }

    // アンロック
    m_pIdxBuff->Unlock();
    
    // 頂点宣言
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
