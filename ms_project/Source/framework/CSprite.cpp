//=============================================================================
//
// スプライトクラス
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CSprite.h"
#include "Resource.h"
#include "DebugUtil.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CSprite::CSprite()
    : m_pVtxBuff(nullptr)
    , m_pTex(nullptr)
    , m_color(1,1,1,1)
    , m_size(0, 0)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSprite::~CSprite()
{
    Resource::Get()->Release(m_pVtxBuff);
    Resource::Get()->Release(m_pTex);
}

//=============================================================================
// 生成
//=============================================================================
CSprite* CSprite::Create(const SpriteDesc& desc)
{
    CSprite* pSpr = new CSprite();

    if(pSpr)
    {
        INIT_CHECK(pSpr->Init(desc));
        _PrintConsole("スプライト\n");
    }

    return pSpr;
}

//=============================================================================
// 生成
//=============================================================================
CSprite* CSprite::Create(const SpriteDesc& desc, cs8* pFileName)
{
    CSprite* pSpr = new CSprite();

    if(pSpr)
    {
        INIT_CHECK(pSpr->Init(desc, pFileName));
        _PrintConsole("スプライト : テクスチャ %s\n", pFileName);
    }

    return pSpr;
}

//=============================================================================
// 更新
//=============================================================================
void CSprite::Update()
{
    if(GetUpdate())
    {
        UpdateBuffer();
    }
}

//=============================================================================
// 描画
//=============================================================================
void CSprite::Draw()
{
}

// 色設定
void CSprite::SetColor(const D3DXCOLOR& color){ SetColor(color.r, color.g, color.b); }
void CSprite::SetColor(cf32 r, cf32 g, cf32 b){ SetUpdate(true); m_color.r = r; m_color.g = g; m_color.b = b; }
// 色取得
const D3DXCOLOR& CSprite::GetColor() const { return m_color; }

// アルファ値設定
void CSprite::SetAlpha(cf32 a){ SetUpdate(true); m_color.a = a; }
// アルファ値取得
f32 CSprite::GetAlpha() const { return m_color.a; }

// テクスチャ設定
void CSprite::SetTexture(cs8* pFileName, bool bUseTexSize)
{
    if(!m_pTex)
    {
        m_pTex = Resource::Get()->GetTexture(pFileName);
        if(m_pTex && bUseTexSize)
        {
            m_size.x = (f32)m_pTex->GetWidth();
            m_size.y = (f32)m_pTex->GetHeight();
        }
        return;
    }

    ITexture* pTex = Resource::Get()->GetTexture(pFileName);
    if(!pTex) return;

    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        Resource::Get()->Release(m_pTex);
    }

    m_pTex = pTex;
    if(bUseTexSize)
    {
        m_size.x = (f32)m_pTex->GetWidth();
        m_size.y = (f32)m_pTex->GetHeight();
    }
}

void CSprite::SetTexture(ITexture* pTex, bool bUseTexSize)
{
    if(m_pTex && m_pTex->GetName().size() > 0)
    {
        Resource::Get()->Release(m_pTex);
    }

    m_pTex = pTex;
    if(m_pTex && bUseTexSize)
    {
        m_size.x = (f32)m_pTex->GetWidth();
        m_size.y = (f32)m_pTex->GetHeight();
    }
}

// 初期化
HRESULT CSprite::Init(const SpriteDesc& desc)
{
    // 頂点バッファ
    VertexBufferDesc vtxDesc;
    vtxDesc.Size = desc.vertexSize * 4;
    vtxDesc.Usage = VTXUSAGE_WRITEONLY;
    vtxDesc.Pool = VTXPOOL_MANAGED;
    m_pVtxBuff = Resource::Get()->GetVertexBuffer(vtxDesc);
    _Assert(m_pVtxBuff);

    // 各パラメータ設定
    SetPosition(desc.pos);
    m_color = desc.color;
    m_size.x = desc.width;
    m_size.y = desc.height;

    // バッファ更新
    UpdateBuffer();

    return S_OK;
}

HRESULT CSprite::Init(const SpriteDesc& desc, cs8* pFileName)
{
    INIT_CHECK(Init(desc));
    SetTexture(pFileName, desc.useTexSize);

    return S_OK;
}

// バッファ更新
void CSprite::UpdateBuffer()
{
    cf32 HALF_WIDTH = m_size.x * 0.5f;
    cf32 HALF_HEIGHT = m_size.x * 0.5f;

    SetUpdate(false);
}

// EOF
