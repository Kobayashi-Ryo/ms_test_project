//=============================================================================
//
// 深度ステンシルバッファ [CDepthStencilBuffer.h]
// Author : Ryo Kobayashi
// Data : 2015/5/3
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CDepthStencilBuffer.h"
#include "CDeviceHolder.h"
#include <common/DebugUtil.h>

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    // 独自定義とDirectX定数の対応
    const D3DFORMAT DS_FORMAT[] =
    {
        D3DFMT_D16,
        D3DFMT_D32,
        D3DFMT_D24S8
    };
}

//=============================================================================
// 生成
//=============================================================================
CDepthStencilBuffer* CDepthStencilBuffer::Create(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc)
{
    CDepthStencilBuffer* pDSBuffer = new CDepthStencilBuffer();
    
    if(pDSBuffer)
    {
        INIT_CHECK(pDSBuffer->Initialize(pHolder, desc));
        _PrintConsole("深度ステンシルバッファ");
    }

    return pDSBuffer;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CDepthStencilBuffer::Initialize(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc)
{
    if(!pHolder) return E_FAIL;
    m_pDev = pHolder->GetDevice();
    
    HRESULT hr;
    // 深度バッファサーフェイス作成
    hr = m_pDev->CreateDepthStencilSurface(
        desc.width,
        desc.height,
        DS_FORMAT[desc.format],        // 深度バッファフォーマット
        D3DMULTISAMPLE_NONE,    // マルチサンプルタイプ
        0,                    // 品質
        TRUE,            // バッファ破棄ON
        &m_pDepthSurface,
        nullptr);
    _Assert(SUCCEEDED(hr));

    m_pDepthSurface->GetDesc(&m_desc);

    return hr;
}

//=============================================================================
// 開放
//=============================================================================
void CDepthStencilBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// 適用
//=============================================================================
void CDepthStencilBuffer::Attach()
{
    if(m_pDev)
    {
        // 深度バッファ取得
        m_pDev->GetDepthStencilSurface(&m_pPrevSurface);
        // 生成したテクスチャ用に作成したZバッファを設定
        m_pDev->SetDepthStencilSurface(m_pDepthSurface);
    }
}

//=============================================================================
// 解除
//=============================================================================
void CDepthStencilBuffer::Detach()
{
    if(m_pDev)
    {
        m_pDev->SetDepthStencilSurface(m_pPrevSurface);
        SafeRelease(m_pPrevSurface);
    }
}

//=============================================================================
// デバイス設定
//=============================================================================
void CDepthStencilBuffer::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

//=============================================================================
// 横幅取得
//=============================================================================
u32 CDepthStencilBuffer::GetWidth() const
{
    return m_desc.Width;
}

//=============================================================================
// 縦幅取得
//=============================================================================
u32 CDepthStencilBuffer::GetHeight() const
{
    return m_desc.Height;
}

//=============================================================================
// リソースの強制的な削除
//=============================================================================
void CDepthStencilBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// リソース情報の保存
//=============================================================================
void CDepthStencilBuffer::Restore()
{
    m_pDepthSurface->GetDesc(&m_desc);
    SafeRelease(m_pDepthSurface);
}

//=============================================================================
// リソース情報の再読み込み
//=============================================================================
void CDepthStencilBuffer::Reload(CDeviceHolder* pHolder)
{
    m_pDev = pHolder->GetDevice();
    HRESULT hr;
    // 深度バッファサーフェイス作成
    hr = m_pDev->CreateDepthStencilSurface(
        m_desc.Width,
        m_desc.Height,
        m_desc.Format,        // 深度バッファフォーマット
        D3DMULTISAMPLE_NONE,    // マルチサンプルタイプ
        0,                    // 品質
        TRUE,            // バッファ破棄ON
        &m_pDepthSurface,
        nullptr);
    _Assert(SUCCEEDED(hr));
}
























CDepthStencilBuffer::CDepthStencilBuffer()
    : m_pDepthSurface(nullptr)
    , m_pPrevSurface(nullptr)
    , m_desc()
    , m_pDev(nullptr)
{
}

CDepthStencilBuffer::~CDepthStencilBuffer()
{
    SafeRelease(m_pDepthSurface);
    SafeRelease(m_pPrevSurface);

    m_pDev = nullptr;
}

// EOF