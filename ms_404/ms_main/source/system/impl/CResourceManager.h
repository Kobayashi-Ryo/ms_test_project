//=============================================================================
//
// リソース管理クラス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <common/common.h>

#include <string>
#include <list>
#include <map>
#include <set>
#include <memory>

#include "../IResource.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;
class CLostResource;
class CFont;
class CTexture;
class CVertexDeclaration;
class CVertexBuffer;
class CIndexBuffer;
class CShader;
class CFrameBuffer;
class CColorBuffer;
class CDepthStencilBuffer;

//*****************************************************************************
// リソース管理クラス
//*****************************************************************************
class CResourceManager
    : private CUncopyable
    , public IResource
{
private:

    /**
    * コンストラクタ
    */
    CResourceManager();

    /**
    * デストラクタ
    */
    ~CResourceManager();

public:

    /**
    * 初期化
    * @ret リソースマネージャー
    * @param pHolder デバイスホルダー
    */
    static CResourceManager* Create(CDeviceHolder* pHolder);

    /**
    * 開放
    */
    void Release();

    /**
    * リソース再初期化
    */
    void Reset();

    /**
    * フォントインターフェースの取得
    * @ret フォントインターフェース
    * @param desc フォント情報
    */
    IFont* GetFont(const FontDesc& desc);
    /**
    * フォント開放
    * @param pTex フォントインターフェース
    */
    void Release(IFont* pFont);

    /**
    * テクスチャの取得
    */
    ITexture* GetTexture(cs8* pFileName);
    /**
    * テクスチャの取得
    */
    ITexture* GetTexture(const TextureDesc& desc);
    /**
    * テクスチャ開放
    * @param pTex テクスチャインターフェース
    */
    void Release(ITexture* pTex);

    /**
    * 頂点宣言の取得
    * @ret 頂点宣言インターフェース
    * @param desc 頂点宣言情報
    */
    IVertexDeclaration* GetVertexDeclaration(u8 uNumElems, const VertexDeclarationDesc* pDesc);
    /**
    * 頂点宣言開放
    * @param pTex 頂点宣言インターフェース
    */
    void Release(IVertexDeclaration* pDecl);

    /**
    * 頂点バッファの取得
    * @ret 頂点バッファインターフェース
    * @param desc 頂点バッファ情報
    */
    IVertexBuffer* GetVertexBuffer(const VertexBufferDesc& desc);
    /**
    * テクスチャ開放
    * @param pTex テクスチャインターフェース
    */
    void Release(IVertexBuffer* pVtx);

    /**
    * インデックスバッファの取得
    * @ret インデックスバッファインターフェース
    * @param desc インデックスバッファ情報
    */
    IIndexBuffer* GetIndexBuffer(const IndexBufferDesc& desc);
    /**
    * インデックス開放
    * @param pTex インデックスインターフェース
    */
    void Release(IIndexBuffer* pIdx);
    
    /**
    * シェーダの取得
    * @ret シェーダインターフェース
    * @param pVertexShader 頂点シェーダ
    * @param pPixelShader ピクセルシェーダ
    */
    IShader* GetShader(
        const s8* pVertexShader,
        const s8* pPixelShader);
    /**
    * シェーダ開放
    * @param pSh シェーダインターフェース
    */
    void Release(IShader* pSh);
    
    /**
    * フレームバッファの取得
    * @ret フレームバッファインターフェース
    */
    IFrameBuffer* GetFrameBuffer();
    /**
    * フレームバッファ開放
    * @param pSh フレームバッファインターフェース
    */
    void Release(IFrameBuffer* pFB);

    /**
    * カラーバッファの取得
    * @ret カラーバッファインターフェース
    */
    IColorBuffer* GetColorBuffer(const ColorBufferDesc& desc);
    /**
    * カラーバッファ開放
    * @param pSh カラーバッファインターフェース
    */
    void Release(IColorBuffer* pCB);

    /**
    * 深度バッファの取得
    * @ret 深度バッファインターフェース
    */
    IDepthStencilBuffer* GetDepthStencilBuffer(const DepthStencilBufferDesc& desc);
    /**
    * 深度バッファ開放
    * @param pDS 深度バッファインターフェース
    */
    void Release(IDepthStencilBuffer* pDS);

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT Init(CDeviceHolder* pHolder);

    /**
    * ロスト状態のチェック
    * @ret true:ロスト中 false:復帰
    */
    bool IsLost();
    
    /**
    * 名前付きテクスチャの開放
    * @param pTex テクスチャ
    */
    void ReleaseNamedTexture(ITexture* pTex);

    /**
    * 名前なしテクスチャ開放
    * @param pTex テクスチャ
    */
    void ReleaseUnnamedTexture(ITexture* pTex);

private:

    // デバイスホルダー
    CDeviceHolder* m_pHolder;

    // ロストリソースリスト
    std::list<CLostResource*> m_listLostRes;

    // フォント
    std::set<CFont*> m_setFont;

    // テクスチャリスト
    std::set<CTexture*> m_setTextures;
    std::map<std::string, CTexture*> m_mapTextures;

    // 頂点宣言リスト
    std::set<CVertexDeclaration*> m_setVertexDecl;

    // 頂点バッファリスト
    std::set<CVertexBuffer*> m_setVertexBuffer;

    // インデックスバッファリスト
    std::set<CIndexBuffer*> m_setIndexBuffer;

    // シェーダリスト
    std::set<CShader*> m_setShader;
    
    // フレームバッファリスト
    std::set<CFrameBuffer*> m_setFB;
    // カラーバッファリスト
    std::set<CColorBuffer*> m_setCB;
    // 深度バッファリスト
    std::set<CDepthStencilBuffer*> m_setDS;
};

#endif  // __RESOURCE_MANAGER_H__

// EOF
