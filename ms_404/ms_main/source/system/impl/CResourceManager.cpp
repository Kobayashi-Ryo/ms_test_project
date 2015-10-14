//=============================================================================
//
// リソース管理クラス
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CResourceManager.h"
#include <algorithm>

#include "CDeviceHolder.h"

#include "CLostResource.h"
#include "CFont.h"
#include "CTexture.h"
#include "CVertexDeclaration.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CFrameBuffer.h"
#include "CColorBuffer.h"
#include "CDepthStencilBuffer.h"

#include <common/DebugUtil.h>

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    static cs8* PATH_TEXTURE = "resource/texture/";
};

//=============================================================================
// コンストラクタ
//=============================================================================
CResourceManager::CResourceManager()
    : m_pHolder(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CResourceManager::~CResourceManager()
{
    // ロストリソース開放
    auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
    []
    (CLostResource*)
    ->bool
    {
        return true;
    }
    );
    m_listLostRes.erase(itDel, m_listLostRes.end());
    
    // フォント開放
    for(auto it = m_setFont.begin(); it != m_setFont.end();)
    {
        (*it)->CleanUp();
        m_setFont.erase(it++);
    }

    // テクスチャ開放
    for(auto it = m_setTextures.begin(); it != m_setTextures.end();)
    {
        (*it)->CleanUp();
        m_setTextures.erase(it++);
    }
    for(auto it = m_mapTextures.begin(); it != m_mapTextures.end();)
    {
        it->second->CleanUp();
        m_mapTextures.erase(it++);
    }
    
    // 頂点宣言開放
    for(auto it = m_setVertexDecl.begin(); it != m_setVertexDecl.end();)
    {
        (*it)->Release();
        m_setVertexDecl.erase(it++);
    }

    // 頂点バッファ開放
    for(auto it = m_setVertexBuffer.begin(); it != m_setVertexBuffer.end();)
    {
        (*it)->CleanUp();
        m_setVertexBuffer.erase(it++);
    }

    // インデックスバッファ開放
    for(auto it = m_setIndexBuffer.begin(); it != m_setIndexBuffer.end();)
    {
        (*it)->CleanUp();
        m_setIndexBuffer.erase(it++);
    }
    
    // シェーダ開放
    for(auto it = m_setShader.begin(); it != m_setShader.end();)
    {
        (*it)->Release();
        m_setShader.erase(it++);
    }

    // フレームバッファ開放
    for(auto it = m_setFB.begin(); it != m_setFB.end();)
    {
        (*it)->Release();
        m_setFB.erase(it++);
    }
    // カラーバッファ開放
    for(auto it = m_setCB.begin(); it != m_setCB.end();)
    {
        (*it)->Release();
        m_setCB.erase(it++);
    }
    // 深度バッファ開放
    for(auto it = m_setDS.begin(); it != m_setDS.end();)
    {
        (*it)->Release();
        m_setDS.erase(it++);
    }
}

//=============================================================================
// 初期化
//=============================================================================
CResourceManager* CResourceManager::Create(CDeviceHolder* pHolder)
{
    CResourceManager* pMgr = new CResourceManager();

    if(pMgr)
    {
        INIT_CHECK(pMgr->Init(pHolder));
        _PrintConsole("リソースマネージャー\n");
    }

    return pMgr;
}

//=============================================================================
// 開放
//=============================================================================
void CResourceManager::Release()
{
    delete this;
}

//=============================================================================
// リソース再初期化
//=============================================================================
void CResourceManager::Reset()
{
    if(IsLost()) return;

    for(auto it = m_listLostRes.begin(); it != m_listLostRes.end(); ++it)
    {
        (*it)->Restore();
    }

    HRESULT hr = m_pHolder->Reset();
    if(SUCCEEDED(hr)) { _PrintConsole("デバイス復帰\n"); }
    else { _PrintConsole("デバイス復帰失敗\n"); return; }
    
    for(auto it = m_listLostRes.begin(); it != m_listLostRes.end(); ++it)
    {
        (*it)->Reload(m_pHolder);
    }
}

//=============================================================================
// フォントインターフェースの取得
//=============================================================================
IFont* CResourceManager::GetFont(const FontDesc& desc)
{
    CFont* pFont = CFont::Create(m_pHolder, desc);

    if(pFont)
    {
        pFont->Increment();

        m_listLostRes.push_back(pFont);
        m_setFont.insert(pFont);
    }

    return pFont;
}

//=============================================================================
// フォント開放
//=============================================================================
void CResourceManager::Release(IFont* pFont)
{
    auto it = m_setFont.find((CFont*)pFont);
    if(it != m_setFont.end())
    {
        CFont *pDelFont = nullptr;
        pDelFont = (*it);
        if(pDelFont->GetReferenceCount() <= 1)
        {// リファレンスが尽きた
            // リストから削除
            m_setFont.erase(it);
            // ロストリソースから削除
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelFont] (CLostResource* pRes) ->bool
            {
                if(pRes == (CLostResource*)pDelFont)
                {
                    return true;
                }
                return false;
            });
            if(itDel != m_listLostRes.end())
            {
                m_listLostRes.erase(itDel);
            }
        }
        // カウンタデクリメント
        pDelFont->Decrement();
    }
}

//=============================================================================
// テクスチャの取得
//=============================================================================
ITexture* CResourceManager::GetTexture(cs8* pFileName)
{
    auto it = m_mapTextures.find(pFileName);
    if(it != m_mapTextures.end())
    {
        it->second->Increment();
        return it->second;
    }

    std::string strPath(PATH_TEXTURE);
    strPath += pFileName;
    CTexture* pTex = CTexture::Create(m_pHolder, strPath.c_str());

    if(pTex)
    {
        m_mapTextures[pFileName] = pTex;
    }

    pTex->Increment();
    return pTex;
}

//=============================================================================
// テクスチャの取得
//=============================================================================
ITexture* CResourceManager::GetTexture(const TextureDesc& desc)
{
    CTexture* pTex = CTexture::Create(m_pHolder, desc);

    if(pTex)
    {
        pTex->Increment();
        m_listLostRes.push_back(pTex);
        m_setTextures.insert(pTex);
    }

    return pTex;
}

//=============================================================================
// テクスチャ開放
//=============================================================================
void CResourceManager::Release(ITexture* pTex)
{
    if(0 == pTex->GetName().compare(""))
    {
        ReleaseUnnamedTexture(pTex);
    }
    else
    {
        ReleaseNamedTexture(pTex);
    }
}

//=============================================================================
// 頂点宣言の取得
//=============================================================================
IVertexDeclaration* CResourceManager::GetVertexDeclaration(u8 uNumElems, const VertexDeclarationDesc* pDesc)
{
    CVertexDeclaration* pDecl = CVertexDeclaration::Create(m_pHolder, uNumElems, pDesc);

    if(pDecl)
    {
        m_setVertexDecl.insert(pDecl);
    }

    return pDecl;
}

//=============================================================================
// 頂点宣言開放
//=============================================================================
void CResourceManager::Release(IVertexDeclaration* pDecl)
{
    auto itDel = m_setVertexDecl.find((CVertexDeclaration*)pDecl);
    if(itDel != m_setVertexDecl.end())
    {
        (*itDel)->Release();
        m_setVertexDecl.erase(itDel);
    }
}

//=============================================================================
// 頂点バッファの取得
//=============================================================================
IVertexBuffer* CResourceManager::GetVertexBuffer(const VertexBufferDesc& desc)
{
    CVertexBuffer* pVtx = CVertexBuffer::Create(m_pHolder, desc);

    if(pVtx)
    {
        pVtx->Increment();

        // メモリ配置チェック
        if(desc.Pool == VTXPOOL_DEFAULT)
        {
            m_listLostRes.push_back(pVtx);
        }
        m_setVertexBuffer.insert(pVtx);
    }

    return pVtx;
}

//=============================================================================
// 頂点バッファ開放
//=============================================================================
void CResourceManager::Release(IVertexBuffer* pVtx)
{
    auto it = m_setVertexBuffer.find((CVertexBuffer*)pVtx);
    if(it != m_setVertexBuffer.end())
    {
        CVertexBuffer *pDelVtx = nullptr;
        pDelVtx = (*it);
        if(pDelVtx->GetReferenceCount() <= 1)
        {// リファレンスが尽きた
            // リストから削除
            m_setVertexBuffer.erase(it);
            // ロストリソースから削除
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelVtx] (CLostResource* pRes) ->bool
            {
                if(pRes == (CLostResource*)pDelVtx)
                {
                    return true;
                }
                return false;
            });
            if(itDel != m_listLostRes.end())
            {
                m_listLostRes.erase(itDel);
            }
        }
        // カウンタデクリメント
        pDelVtx->Decrement();
    }
}

//=============================================================================
// インデックスバッファの取得
//=============================================================================
IIndexBuffer* CResourceManager::GetIndexBuffer(const IndexBufferDesc& desc)
{
    CIndexBuffer* pIdx = CIndexBuffer::Create(m_pHolder, desc);

    if(pIdx)
    {
        pIdx->Increment();

        // メモリ配置チェック
        if(desc.Pool == IDXPOOL_DEFAULT)
        {
            m_listLostRes.push_back(pIdx);
        }
        m_setIndexBuffer.insert(pIdx);
    }

    return pIdx;
}

//=============================================================================
// インデックス開放
//=============================================================================
void CResourceManager::Release(IIndexBuffer* pIdx)
{
    auto it = m_setIndexBuffer.find((CIndexBuffer*)pIdx);
    if(it != m_setIndexBuffer.end())
    {
        CIndexBuffer *pDelIdx = nullptr;
        pDelIdx = (*it);
        if(pDelIdx->GetReferenceCount() <= 1)
        {// リファレンスが尽きた
            // リストから削除
            m_setIndexBuffer.erase(it);
            // ロストリソースから削除
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelIdx] (CLostResource* pRes) ->bool
            {
                if(pRes == (CLostResource*)pDelIdx)
                {
                    return true;
                }
                return false;
            });
            if(itDel != m_listLostRes.end())
            {
                m_listLostRes.erase(itDel);
            }
        }
        // カウンタデクリメント
        pDelIdx->Decrement();
    }
}

//=============================================================================
// シェーダの取得
//=============================================================================
IShader* CResourceManager::GetShader(
    const s8* pVertexShader,
    const s8* pPixelShader)
{
    CShader* pSh = CShader::Create(m_pHolder, pVertexShader, pPixelShader);

    if(pSh)
    {
        m_setShader.insert(pSh);
    }

    return pSh;
}

//=============================================================================
// シェーダ開放
//=============================================================================
void CResourceManager::Release(IShader* pSh)
{
    auto itDel = m_setShader.find((CShader*)pSh);
    if(itDel != m_setShader.end())
    {
        (*itDel)->Release();
        m_setShader.erase(itDel);
    }
}

//=============================================================================
// フレームバッファの取得
//=============================================================================
IFrameBuffer* CResourceManager::GetFrameBuffer()
{
    CFrameBuffer* pFB = CFrameBuffer::Create();

    if(pFB)
    {
        m_setFB.insert(pFB);
    }

    return pFB;
}

//=============================================================================
// フレームバッファ開放
//=============================================================================
void CResourceManager::Release(IFrameBuffer* pFB)
{
    auto itDel = m_setFB.find((CFrameBuffer*)pFB);
    if(itDel != m_setFB.end())
    {
        (*itDel)->Release();
        m_setFB.erase(itDel);
    }
}

//=============================================================================
// カラーバッファの取得
//=============================================================================
IColorBuffer* CResourceManager::GetColorBuffer(const ColorBufferDesc& desc)
{
    CColorBuffer* pCB = CColorBuffer::Create(m_pHolder, desc);

    if(pCB)
    {
        m_setCB.insert(pCB);
    }

    return pCB;
}

//=============================================================================
// カラーバッファ開放
//=============================================================================
void CResourceManager::Release(IColorBuffer* pCB)
{
    auto itDel = m_setCB.find((CColorBuffer*)pCB);
    if(itDel != m_setCB.end())
    {
        (*itDel)->Release();
        m_setCB.erase(itDel);
    }
}

//=============================================================================
// 深度バッファの取得
//=============================================================================
IDepthStencilBuffer* CResourceManager::GetDepthStencilBuffer(const DepthStencilBufferDesc& desc)
{
    CDepthStencilBuffer* pDS = CDepthStencilBuffer::Create(m_pHolder, desc);

    if(pDS)
    {
        m_setDS.insert(pDS);
    }

    return pDS;
}

//=============================================================================
// 深度バッファ開放
//=============================================================================
void CResourceManager::Release(IDepthStencilBuffer* pDS)
{
    auto itDel = m_setDS.find((CDepthStencilBuffer*)pDS);
    if(itDel != m_setDS.end())
    {
        (*itDel)->Release();
        m_setDS.erase(itDel);
    }
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CResourceManager::Init(CDeviceHolder* pHolder)
{
    m_pHolder = pHolder;

    return S_OK;
}

//=============================================================================
// ロスト状態のチェック
//=============================================================================
bool CResourceManager::IsLost()
{
    HRESULT hr = m_pHolder->GetDevice()->TestCooperativeLevel();

    if(D3DERR_DEVICELOST == hr)
    {
        _PrintConsole("デバイスロスト\n");
        return true;
    }
    else if(D3DERR_DRIVERINTERNALERROR == hr)
    {
        _CriticalAssertExpr(SUCCEEDED(hr), "ドライバー内にエラー発生");
    }
    else if(D3DERR_DEVICENOTRESET == hr)
    {
        _PrintConsole("デバイス復帰可能\n");
        return false;
    }

    return false;
}

//=============================================================================
// 名前付きテクスチャの開放
//=============================================================================
void CResourceManager::ReleaseNamedTexture(ITexture* pTex)
{
    auto it = m_mapTextures.find(pTex->GetName());
    if(it != m_mapTextures.end())
    {
        CTexture *pDelTex = nullptr;
        pDelTex = it->second;
        if(pDelTex->GetReferenceCount() <= 1)
        {// リファレンスが尽きた
            // リストから削除
            m_mapTextures.erase(it);
        }
        // カウンタデクリメント
        pDelTex->Decrement();
    }
}

//=============================================================================
// 名前なしテクスチャ開放
//=============================================================================
void CResourceManager::ReleaseUnnamedTexture(ITexture* pTex)
{
    auto it = m_setTextures.find((CTexture*)pTex);
    if(it != m_setTextures.end())
    {
        CTexture *pDelTex = nullptr;
        pDelTex = (*it);
        if(pDelTex->GetReferenceCount() <= 1)
        {// リファレンスが尽きた
            // リストから削除
            m_setTextures.erase(it);
            // ロストリソースから削除
            auto itDel = std::remove_if(m_listLostRes.begin(), m_listLostRes.end(),
            [pDelTex]
            (CLostResource* pRes)
            ->bool
            {
                if(pRes == (CLostResource*)pDelTex)
                {
                    return true;
                }
                return false;
            }
            );
            m_listLostRes.erase(itDel);
        }
        // カウンタデクリメント
        pDelTex->Decrement();
    }
}

// EOF
