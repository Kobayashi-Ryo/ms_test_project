//=============================================================================
//
// テクスチャ
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CTexture.h"
#include "D3DX.h"
#include "DebugUtil.h"

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    // 独自定義とDirectX定数の対応
    static const D3DFORMAT TEX_FORMAT[] =
    {
        D3DFMT_X8R8G8B8,
        D3DFMT_A8R8G8B8
    };
    static const DWORD TEX_USAGE[] =
    {
        D3DUSAGE_RENDERTARGET,
        D3DUSAGE_DEPTHSTENCIL,
        D3DUSAGE_DYNAMIC
    };
    static const D3DPOOL TEX_POOL[] =
    {
        D3DPOOL_DEFAULT,
        D3DPOOL_MANAGED,
        D3DPOOL_SYSTEMMEM
    };
};

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
    : m_pTex(nullptr)
    , m_pSurface(nullptr)
    , m_strName("")
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
    SafeRelease(m_pSurface);
    SafeRelease(m_pTex);
}

//=============================================================================
// 生成
//=============================================================================
CTexture* CTexture::Create(CDeviceHolder* pHolder, cs8* pFileName)
{
    CTexture* pTex = new CTexture();

    if(pTex)
    {
        INIT_CHECK(pTex->Init(pHolder, pFileName));
        _PrintConsole("テクスチャ : %s\n", pFileName);
    }

    return pTex;
}

//=============================================================================
// 生成
//=============================================================================
CTexture* CTexture::Create(CDeviceHolder* pHolder, const TextureDesc& desc)
{
    CTexture* pTex = new CTexture();

    if(pTex)
    {
        INIT_CHECK(pTex->Init(pHolder, desc));
        _PrintConsole("テクスチャ\n");
    }

    return pTex;
}

//=============================================================================
// 開放
//=============================================================================
void CTexture::Release()
{
    CRef::Decrement();
}

//=============================================================================
// 開放
//=============================================================================
void CTexture::CleanUp()
{
    delete this;
}

//=============================================================================
// リソース情報の保存
//=============================================================================
void CTexture::Restore()
{
    SafeRelease(m_pSurface);
    if(m_pTex) m_pTex->GetLevelDesc(0, &m_desc);
    SafeRelease(m_pTex);
}

//=============================================================================
// リソース情報の再読み込み
//=============================================================================
void CTexture::Reload(CDeviceHolder* pHolder)
{
    LPDIRECT3DDEVICE9 pDev = pHolder->GetDevice();

    pDev->CreateTexture(
        m_desc.Width,
        m_desc.Height,
        1,
        m_desc.Usage,
        m_desc.Format,
        m_desc.Pool,
        &m_pTex,
        nullptr);

    m_pTex->GetSurfaceLevel(0, &m_pSurface);
}

//=============================================================================
// テクスチャ取得
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture() const
{
    return m_pTex;
}

//=============================================================================
// サーフェス取得
//=============================================================================
LPDIRECT3DSURFACE9 CTexture::GetSurface() const
{
    return m_pSurface;
}

//=============================================================================
// 横幅取得
//=============================================================================
u32 CTexture::GetWidth() const
{
    return m_desc.Width;
}

//=============================================================================
// 縦幅取得
//=============================================================================
u32 CTexture::GetHeight() const
{
    return m_desc.Height;
}

//=============================================================================
// 名前取得
//=============================================================================
const std::string& CTexture::GetName() const
{
    return m_strName;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTexture::Init(CDeviceHolder* pHolder, cs8* pFileName)
{
    _Assert(pFileName);
    m_strName = pFileName;
    D3DXCreateTextureFromFile(
        pHolder->GetDevice(),
        pFileName,
        &m_pTex);
    _Assert(m_pTex);
    m_pTex->GetLevelDesc(0, &m_desc);

    return S_OK;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTexture::Init(CDeviceHolder* pHolder, const TextureDesc& desc)
{
    pHolder->GetDevice()->CreateTexture(
        desc.Width,
        desc.Height,
        1,
        TEX_USAGE[desc.Usage],
        TEX_FORMAT[desc.Format],
        TEX_POOL[desc.Pool],
        &m_pTex,
        nullptr);

    m_pTex->GetSurfaceLevel(0, &m_pSurface);

    _Assert(m_pTex);
    m_pTex->GetLevelDesc(0, &m_desc);

    return S_OK;
}

// EOF
