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
#include "common.h"

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
    * @param pTex 頂点宣言インターフェース
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
    * @param pTex 頂点バッファインターフェース
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
    * @param pTex インデックスインターフェース
    */
    virtual void Release(IIndexBuffer* pIdx) = 0;

protected:

    virtual ~IResource(){}
};

#endif  // __RESOURCE_INTERFACE_H__

// EOF
