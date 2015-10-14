//=============================================================================
//
// カラーバッファ [CColorBuffer.cpp]
// Author : Ryo Kobayashi
// Data : 2015/5/3
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CColorBuffer.h"
#include "CTexture.h"
#include <common/DebugUtil.h>

//=============================================================================
// 生成
//=============================================================================
CColorBuffer* CColorBuffer::Create(CDeviceHolder* pHolder, const ColorBufferDesc& desc)
{
    CColorBuffer* pColorBuffer = new CColorBuffer();
    
    if(pColorBuffer)
    {
        INIT_CHECK(pColorBuffer->Initialize(pHolder, desc));
        _PrintConsole("カラーバッファ");
    }

    return pColorBuffer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CColorBuffer::Initialize(CDeviceHolder* pHolder, const ColorBufferDesc& desc)
{
    m_desc = desc;

    Uninitialize();
    
    if(!pHolder) return E_FAIL;
    m_pDev = pHolder->GetDevice();;

    // 空テクスチャ生成
    TextureDesc t_desc;
    t_desc.Width = m_desc.width;
    t_desc.Height = m_desc.height;
    t_desc.Usage = TEXUSAGE_RENDERTARGET;
    t_desc.Format = m_desc.format;
    m_pTexture = CTexture::Create(pHolder, t_desc);

    // テクスチャへのサーフェスを取得
    m_pTexture->GetTexture()->GetSurfaceLevel(0, &m_pSurface);

    return S_OK;
}

//=============================================================================
// 開放
//=============================================================================
void CColorBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// 適用
//=============================================================================
void CColorBuffer::Attach()
{
    m_pDev->GetRenderTarget(m_desc.index, &m_pPrevSurface);
    m_pDev->SetRenderTarget(m_desc.index, m_pSurface);
}

//=============================================================================
// 解除
//=============================================================================
void CColorBuffer::Detach()
{
    _Assert(m_pPrevSurface);

    m_pDev->SetRenderTarget(m_desc.index, m_pPrevSurface);
    SafeRelease(m_pPrevSurface);
}

//=============================================================================
// デバイス設定
//=============================================================================
void CColorBuffer::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

//=============================================================================
// レンダーターゲットインデックス設定
//=============================================================================
void CColorBuffer::SetRenderTargetIndex(cu32 uIndex)
{
    m_desc.index = uIndex;
}

//=============================================================================
// 横幅取得
//=============================================================================
u32 CColorBuffer::GetWidth() const
{
    return m_desc.width;
}

//=============================================================================
// 縦幅取得
//=============================================================================
u32 CColorBuffer::GetHeight() const
{
    return m_desc.height;
}

//=============================================================================
// テクスチャ取得
//=============================================================================
ITexture* CColorBuffer::GetTexture() const
{
    return m_pTexture;
}

//=============================================================================
// リソースの強制的な削除
//=============================================================================
void CColorBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// リソース情報の保存
//=============================================================================
void CColorBuffer::Restore()
{
    m_pTexture->Restore();
}

//=============================================================================
// リソース情報の再読み込み
//=============================================================================
void CColorBuffer::Reload(CDeviceHolder* pHolder)
{
    m_pTexture->Reload(pHolder);
    m_pTexture->GetTexture()->GetSurfaceLevel(0, &m_pSurface);
}

//=============================================================================
// 開放
//=============================================================================
void CColorBuffer::Uninitialize()
{
    SafeRelease(m_pSurface);
    SafeRelease(m_pTexture);

    // 開放忘れの時のため
    SafeRelease(m_pPrevSurface);

    m_pDev = nullptr;
}
























CColorBuffer::CColorBuffer()
    : m_pSurface(nullptr)
    , m_pTexture(nullptr)
    , m_pPrevSurface(nullptr)
    , m_desc()
    , m_pDev(nullptr)
{
}

CColorBuffer::~CColorBuffer()
{
    Uninitialize();
}

// EOF