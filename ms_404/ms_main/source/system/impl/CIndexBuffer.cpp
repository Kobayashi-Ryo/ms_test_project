//=============================================================================
//
// インデックスバッファ
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CIndexBuffer.h"
#include "CDeviceHolder.h"
#include <common/DebugUtil.h>

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    // 独自定義とDirectX定数の対応
    static const D3DFORMAT IDX_FORMAT[] =
    {
        D3DFMT_INDEX16,
        D3DFMT_INDEX32
    };
    static const DWORD IDX_USAGE[] =
    {
        D3DUSAGE_DYNAMIC,
        D3DUSAGE_WRITEONLY
    };
    static const D3DPOOL IDX_POOL[] =
    {
        D3DPOOL_DEFAULT,
        D3DPOOL_MANAGED,
        D3DPOOL_SYSTEMMEM
    };
};

//=============================================================================
// コンストラクタ
//=============================================================================
CIndexBuffer::CIndexBuffer()
    : m_pIdx(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CIndexBuffer::~CIndexBuffer()
{
    SafeRelease(m_pIdx);
}

//=============================================================================
// インデックスバッファ生成
//=============================================================================
CIndexBuffer* CIndexBuffer::Create(CDeviceHolder* pHolder, const IndexBufferDesc& desc)
{
    CIndexBuffer* pIdx = new CIndexBuffer();

    if(pIdx)
    {
        INIT_CHECK(pIdx->Init(pHolder, desc));
        _PrintConsole("インデックスバッファ\n");
    }

    return pIdx;
}

//=============================================================================
// DirectXインデックスバッファ取得
//=============================================================================
LPDIRECT3DINDEXBUFFER9 CIndexBuffer::GetPointer() const
{
    return m_pIdx;
}

//=============================================================================
// 開放
//=============================================================================
void CIndexBuffer::Release()
{
    CRef::Decrement();
}

//=============================================================================
// インデックスバッファロック
//=============================================================================
HRESULT CIndexBuffer::Lock(void** pBuff)
{
    return m_pIdx->Lock(0, 0, pBuff, 0);
}

//=============================================================================
// インデックスバッファアンロック
//=============================================================================
HRESULT CIndexBuffer::Unlock()
{
    return m_pIdx->Unlock();
}

//=============================================================================
// リソースの強制的な削除
//=============================================================================
void CIndexBuffer::CleanUp()
{
    delete this;
}

//=============================================================================
// リソース情報の保存
//=============================================================================
void CIndexBuffer::Restore()
{
    m_pIdx->GetDesc(&m_desc);
    SafeRelease(m_pIdx);
}

//=============================================================================
// リソース情報の再読み込み
//=============================================================================
void CIndexBuffer::Reload(CDeviceHolder* pHolder)
{
    auto pDev = pHolder->GetDevice();

    pDev->CreateIndexBuffer(
        m_desc.Size,
        m_desc.Usage,
        m_desc.Format,
        m_desc.Pool,
        &m_pIdx,
        nullptr);
    _Assert(m_pIdx);
}

void CIndexBuffer::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}
void CIndexBuffer::Attach()
{
    m_pDev->SetIndices(m_pIdx);
}
void CIndexBuffer::Detach()
{
    m_pDev->SetIndices(nullptr);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CIndexBuffer::Init(CDeviceHolder* pHolder, const IndexBufferDesc& desc)
{
    m_pDev = pHolder->GetDevice();

    m_pDev->CreateIndexBuffer(
        desc.Size,
        IDX_USAGE[desc.Usage],
        IDX_FORMAT[desc.Format],
        IDX_POOL[desc.Pool],
        &m_pIdx,
        nullptr);
    _Assert(m_pIdx);

    m_pIdx->GetDesc(&m_desc);

    return S_OK;
}

// EOF
