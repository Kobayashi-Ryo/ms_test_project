//=============================================================================
//
// 頂点バッファ
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CVertexBuffer.h"
#include "CDeviceHolder.h"
#include <common/DebugUtil.h>

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    // 独自定義とDirectX定数の対応
    static const DWORD VTX_USAGE[] =
    {
        D3DUSAGE_DYNAMIC,
        D3DUSAGE_SOFTWAREPROCESSING,
        D3DUSAGE_WRITEONLY
    };
    static const D3DPOOL VTX_POOL[] =
    {
        D3DPOOL_DEFAULT,
        D3DPOOL_MANAGED,
        D3DPOOL_SYSTEMMEM
    };
};

//=============================================================================
// コンストラクタ
//=============================================================================
CVertexBuffer::CVertexBuffer()
    : m_pVtx(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CVertexBuffer::~CVertexBuffer()
{
    SafeRelease(m_pVtx);
}

//=============================================================================
// 頂点バッファ生成
//=============================================================================
CVertexBuffer* CVertexBuffer::Create(CDeviceHolder* pHolder, const VertexBufferDesc& desc)
{
    CVertexBuffer* pVtx = new CVertexBuffer();

    if(pVtx)
    {
        INIT_CHECK(pVtx->Init(pHolder, desc));
        _PrintConsole("頂点バッファ\n");
    }

    return pVtx;
}

//=============================================================================
// DirectX頂点バッファ取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CVertexBuffer::GetPointer() const
{
    return m_pVtx;
}

//=============================================================================
// 開放
//=============================================================================
void CVertexBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// 頂点バッファロック
//=============================================================================
HRESULT CVertexBuffer::Lock(void** pBuff)
{
    return m_pVtx->Lock(0, 0, pBuff, 0);
}

//=============================================================================
// 頂点バッファアンロック
//=============================================================================
HRESULT CVertexBuffer::Unlock()
{
    return m_pVtx->Unlock();
}

//=============================================================================
// リソースの強制的な削除
//=============================================================================
void CVertexBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// リソース情報の保存
//=============================================================================
void CVertexBuffer::Restore()
{
    m_pVtx->GetDesc(&m_desc);
    SafeRelease(m_pVtx);
}

//=============================================================================
// リソース情報の再読み込み
//=============================================================================
void CVertexBuffer::Reload(CDeviceHolder* pHolder)
{
    auto pDev = pHolder->GetDevice();

    pDev->CreateVertexBuffer(
        m_desc.Size,
        m_desc.Usage,
        0,
        m_desc.Pool,
        &m_pVtx,
        nullptr);
    _Assert(m_pVtx);
}

//=============================================================================
// ストリーム番号設定
//=============================================================================
void CVertexBuffer::SetStreamIndex(u32 index)
{
    m_index = index;
}

//=============================================================================
// バッファオフセット設定
//=============================================================================
void CVertexBuffer::SetOffset(u32 offset)
{
    m_offset = offset;
}

//=============================================================================
// ストリームに流す頂点サイズ設定
//=============================================================================
void CVertexBuffer::SetStride(u32 stride)
{
    m_stride = stride;
}

void CVertexBuffer::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

void CVertexBuffer::Attach()
{
    m_pDev->SetStreamSource(m_index, m_pVtx, m_offset, m_stride);
}

void CVertexBuffer::Detach()
{
    m_pDev->SetStreamSource(m_index, nullptr, 0, 0);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CVertexBuffer::Init(CDeviceHolder* pHolder, const VertexBufferDesc& desc)
{
    m_pDev = pHolder->GetDevice();

    m_pDev->CreateVertexBuffer(
        desc.Size,
        VTX_USAGE[desc.Usage],
        0,
        VTX_POOL[desc.Pool],
        &m_pVtx,
        nullptr);
    _Assert(m_pVtx);

    m_pVtx->GetDesc(&m_desc);

    m_index = 0;
    m_offset = 0;
    m_stride = 0;
    
    return S_OK;
}

// EOF
