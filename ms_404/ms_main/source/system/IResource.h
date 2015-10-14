//=============================================================================
//
// リソースインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __RESOURCE_INTERFACE_H__
#define __RESOURCE_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/common.h>

// font
#include "IFont.h"

// texture
#include "ITexture.h"

// surface

// declaration
#include "IVertexDeclaration.h"

// vertex
#include "IVertexBuffer.h"

// index
#include "IIndexBuffer.h"

// shader
#include "IShader.h"

// render buffer
#include "IFrameBuffer.h"
#include "IColorBuffer.h"
#include "IDepthStencilBuffer.h"

//*****************************************************************************
// リソースインターフェース
//*****************************************************************************
class IResource
{
public:

    // フォント
    /**
    * フォントインターフェースの取得
    * @ret フォントインターフェース
    * @param desc フォント情報
    */
    virtual IFont* GetFont(const FontDesc& desc) = 0;
    /**
    * フォント開放
    * @param pTex フォントインターフェース
    */
    virtual void Release(IFont* pFont) = 0;

    // テクスチャ
    /**
    * テクスチャの取得
    * @ret テクスチャインターフェース
    * @param pFileName テクスチャファイル名
    */
    virtual ITexture* GetTexture(cs8* pFileName) = 0;
    /**
    * テクスチャの取得
    * @ret テクスチャインターフェース
    * @param desc テクスチャ情報
    */
    virtual ITexture* GetTexture(const TextureDesc& desc) = 0;
    /**
    * テクスチャ開放
    * @param pTex テクスチャインターフェース
    */
    virtual void Release(ITexture* pTex) = 0;

    // 頂点宣言
    /**
    * 頂点宣言の取得
    * @ret 頂点宣言インターフェース
    * @param desc 頂点宣言情報
    */
    virtual IVertexDeclaration* GetVertexDeclaration(u8 uNumDescs, const VertexDeclarationDesc* pDesc) = 0;
    /**
    * 頂点宣言開放
    * @param pDecl 頂点宣言インターフェース
    */
    virtual void Release(IVertexDeclaration* pDecl) = 0;

    // 頂点バッファ
    /**
    * 頂点バッファの取得
    * @ret 頂点バッファインターフェース
    * @param desc 頂点バッファ情報
    */
    virtual IVertexBuffer* GetVertexBuffer(const VertexBufferDesc& desc) = 0;
    /**
    * 頂点バッファ開放
    * @param pVtx 頂点バッファインターフェース
    */
    virtual void Release(IVertexBuffer* pVtx) = 0;

    // インデックスバッファ
    /**
    * インデックスバッファの取得
    * @ret インデックスバッファインターフェース
    * @param desc インデックスバッファ情報
    */
    virtual IIndexBuffer* GetIndexBuffer(const IndexBufferDesc& desc) = 0;
    /**
    * インデックス開放
    * @param pIdx インデックスインターフェース
    */
    virtual void Release(IIndexBuffer* pIdx) = 0;

    // シェーダ
    /**
    * シェーダの取得
    * @ret シェーダインターフェース
    * @param pVertexShader 頂点シェーダ
    * @param pPixelShader ピクセルシェーダ
    */
    virtual IShader* GetShader(
        const s8* pVertexShader,
        const s8* pPixelShader) = 0;
    /**
    * シェーダ開放
    * @param pSh シェーダインターフェース
    */
    virtual void Release(IShader* pSh) = 0;

    // フレームバッファ
    /**
    * フレームバッファの取得
    * @ret フレームバッファインターフェース
    */
    virtual IFrameBuffer* GetFrameBuffer() = 0;
    /**
    * フレームバッファ開放
    * @param pSh フレームバッファインターフェース
    */
    virtual void Release(IFrameBuffer* pFB) = 0;

    // カラーバッファ
    /**
    * カラーバッファの取得
    * @ret カラーバッファインターフェース
    */
    virtual IColorBuffer* GetColorBuffer(const ColorBufferDesc& desc) = 0;
    /**
    * カラーバッファ開放
    * @param pSh カラーバッファインターフェース
    */
    virtual void Release(IColorBuffer* pCB) = 0;

    // 深度バッファ
    /**
    * 深度バッファの取得
    * @ret 深度バッファインターフェース
    */
    virtual IDepthStencilBuffer* GetDepthStencilBuffer(const DepthStencilBufferDesc& desc) = 0;
    /**
    * 深度バッファ開放
    * @param pDS 深度バッファインターフェース
    */
    virtual void Release(IDepthStencilBuffer* pDS) = 0;

protected:

    virtual ~IResource(){}
};

#endif  // __RESOURCE_INTERFACE_H__

// EOF
