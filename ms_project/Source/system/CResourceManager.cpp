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
#include <memory>

#include "CDeviceHolder.h"

#include "CLostResource.h"
#include "CFont.h"
#include "CTexture.h"
#include "CVertexDeclaration.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

#include "DebugUtil.h"

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    static cs8* PATH_TEXTURE = "Resource/Texture/";
};

//=============================================================================
// コンストラクタ
//=============================================================================
CResourceManager::CResourceManager()
    : m_pHolder(nullptr)
{
    int* i = new int;
    *i = 5;
    std::tr1::shared_ptr<int> d(i);
    std::tr1::shared_ptr<int> x = std::move(d);
    int a = d.use_count();
    int b = sizeof(std::tr1::shared_ptr<CTexture>);

    std::list< std::tr1::shared_ptr<int> > splist;
    splist.push_back(x);
    for(auto it = splist.begin(); it != splist.end(); ++it)
    {
        if((*it) == x)
        {
            (*(*it).get()) = 10;
        }
    }
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
