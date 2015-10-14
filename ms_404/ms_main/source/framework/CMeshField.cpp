//=============================================================================
//
// メッシュフィールド
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
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

// 生成
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

// 描画
void CMeshField::Draw()
{
    m_pVtxBuff->Attach();
    m_pIdxBuff->Attach();
    m_pDecl->Attach();
    m_pTex->Attach(); // ここサンプラークラスにした方がいいかも
    
    auto dev = CApplication::GetInstance()->GetSystem()->GetDeviceHolder()->GetDevice();
    HRESULT hr = dev->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_uNumVtxX * m_uNumVtxZ, 0, m_uNumPrimitive);
    _Assert(SUCCEEDED(hr));

    m_pVtxBuff->Detach();
    m_pIdxBuff->Detach();
    m_pDecl->Detach();
    m_pTex->Detach();
}

// X方向頂点数
u32 CMeshField::GetNumVertexX() const
{
    return m_uNumVtxX;
}

// Z方向頂点数
u32 CMeshField::GetNumVertexZ() const
{
    return m_uNumVtxZ;
}

// 頂点バッファ操作
void CMeshField::ControlVertex(std::function<void(Vertex3D*, u32, u32)> func)
{
    Vertex3D* pVtx = nullptr;

    m_pVtxBuff->Lock((void**)&pVtx);

    func(pVtx, m_uNumVtxX, m_uNumVtxZ);

    m_pVtxBuff->Unlock();
}

// 横幅取得
f32 CMeshField::GetWidth() const
{
    return m_fWidth;
}

// 奥行取得
f32 CMeshField::GetDepth() const
{
    return m_fDepth;
}

// 初期化
bool CMeshField::Init(const MeshFieldDesc& desc)
{
    auto res = CApplication::GetInstance()->GetSystem()->GetResource();

    m_pTex = res->GetTexture(desc.textureName);

    // 頂点数設定
    m_uNumVtxX = desc.numXGrid + 1;
    m_uNumVtxZ = desc.numZGrid + 1;
    // プリミティブ数設定
    m_uNumPrimitive = (desc.numXGrid * 2) * desc.numZGrid + 4 * (desc.numZGrid - 1);

    // 頂点バッファ
    VertexBufferDesc vtxDesc;
    vtxDesc.Size = sizeof(Vertex3D) * m_uNumVtxX * m_uNumVtxZ;
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
    idxDesc.Size = sizeof(u16) * 2 * (desc.numZGrid * (desc.numXGrid + 2) - 1);
    idxDesc.Usage = IDXUSAGE_WRITEONLY;
    idxDesc.Pool = IDXPOOL_MANAGED;
    idxDesc.Format = IDXFMT_INDEX16; // 16でいい気がする
    m_pIdxBuff = res->GetIndexBuffer(idxDesc);
    _Assert(m_pIdxBuff);

    // 頂点アクセス用ポインタ
    Vertex3D *pVtx = nullptr;
    // 頂点ロック
    m_pVtxBuff->Lock((void**)&pVtx);
    // 頂点初期化
    //f32 fTexDiffX = 1.0f / desc.widthGrid;
    //f32 fTexDiffZ = 1.0f / desc.depthGrid;
    for(s32 z = 0; z <= desc.numZGrid; z++)
    {
        for(s32 x = 0; x <= desc.numXGrid; x++)
        {
            s32 nIndex = z * (desc.numXGrid + 1) + x;
            // 頂点座標算出
            pVtx[nIndex].pos.x = (f32)( x * desc.widthGrid - desc.numXGrid * desc.widthGrid * 0.5f);
            pVtx[nIndex].pos.y = 0.0f;
            pVtx[nIndex].pos.z = (f32)(-z * desc.depthGrid + desc.numZGrid * desc.depthGrid * 0.5f);

            pVtx[nIndex].normal.x = pVtx[nIndex].normal.z = 0.0f;
            pVtx[nIndex].normal.y = 1.0f;

            // テクスチャ座標算出(適当すぎ)
            pVtx[nIndex].texcoord = vec2((f32)x, (f32)z);
        }
    }
    m_pVtxBuff->Unlock();

    
    // インデックスアクセス用ポインタ
    u16 *pIdx = nullptr;
    // インデックスバッファロック
    m_pIdxBuff->Lock((void**)&pIdx);

#ifdef _DEBUG    // デバッグウォッチ用
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
            // 縮退ポリゴン用のインデックスを設定
            pIdx[(desc.numXGrid + 1) * 2    ] =  z *      (desc.numXGrid + 1) + desc.numXGrid;
            pIdx[(desc.numXGrid + 1) * 2 + 1] = (z + 2) * (desc.numXGrid + 1);
        }

        pIdx += ((desc.numXGrid + 1) * 2 + 2);
    }
    m_pIdxBuff->Unlock();

    // 頂点宣言
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
