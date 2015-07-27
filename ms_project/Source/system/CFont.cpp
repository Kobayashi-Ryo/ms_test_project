//=============================================================================
//
// フォント
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CFont.h"
#include "CDeviceHolder.h"
#include "DebugUtil.h"

CFont::CFont()
    : m_pFont(nullptr)
{
}

CFont::~CFont()
{
    SafeRelease(m_pFont);
}

CFont* CFont::Create(CDeviceHolder* pHolder, const FontDesc& desc)
{
    CFont* pFont = new CFont();

    if(pFont)
    {
        INIT_CHECK(pFont->Init(pHolder, desc));
        _PrintConsole("フォント");
    }

    return pFont;
}

void CFont::Draw(RECT& rect, cs8* pString)
{
    // デバッグ描画
    HR(m_pFont->DrawText(0, pString, -1, &rect, DT_NOCLIP, D3DCOLOR_RGBA(255, 255, 255, 255)));
}

void CFont::Release()
{
    CRef::Decrement();
}

void CFont::CleanUp()
{
    delete this;
}

void CFont::Restore()
{
    if(m_pFont) m_pFont->GetDesc(&m_desc);
    SafeRelease(m_pFont);
}

void CFont::Reload(CDeviceHolder* pHolder)
{
    // Font作成
    INIT_CHECK(D3DXCreateFontIndirect(pHolder->GetDevice(), &m_desc, &m_pFont));
}

HRESULT CFont::Init(CDeviceHolder* pHolder, const FontDesc& desc)
{
    // デバイス
    LPDIRECT3DDEVICE9 pDev = pHolder->GetDevice();

    // Font情報初期化
    m_desc.Height          = desc.Height;      // 文字の高さ
    m_desc.Width           = desc.Width;       // 文字の横幅
    m_desc.Weight          = 0;                // フォントのウェイト
    m_desc.MipLevels       = 1;                // ミップマップレベル
    m_desc.Italic          = desc.Italic;      // イタリック文字
    m_desc.CharSet         = DEFAULT_CHARSET;    // 文字セット
    m_desc.OutputPrecision = OUT_DEFAULT_PRECIS;// 出力精度
    m_desc.Quality         = DEFAULT_QUALITY;    // 出力品質
    m_desc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;// フォントのピッチとファミリ
    strcpy_s(m_desc.FaceName, sizeof(m_desc.FaceName), "Times New Roman");// フォントのタイプフェース名

    // Font作成
    INIT_CHECK(D3DXCreateFontIndirect(pDev, &m_desc, &m_pFont));
    
    // 初期化成功
    return S_OK;
}

// EOF
