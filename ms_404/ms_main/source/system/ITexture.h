//=============================================================================
//
// テクスチャインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __TEXTURE_INTERFACE_H__
#define __TEXTURE_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/DirectX.h>
#include <string>
#include "TextureDesc.h"

//*****************************************************************************
// テクスチャインターフェース
//*****************************************************************************
class ITexture
{
public:
    
    /**
    * 適用
    */
    virtual void Attach() = 0;
    /**
    * 解除
    */
    virtual void Detach() = 0;

    /**
    * テクスチャステージインデックス設定
    * @param index インデックス
    */
    virtual void SetIndex(u32 index) = 0;

    /**
    * テクスチャ取得
    * @ret DirectXテクスチャインターフェース
    */
    virtual LPDIRECT3DTEXTURE9 GetTexture() const = 0;

    /**
    * サーフェス取得
    * @ret DirectXサーフェスインターフェース
    */
    virtual LPDIRECT3DSURFACE9 GetSurface() const = 0;

    /**
    * 横幅取得
    * @ret 横幅
    */
    virtual u32 GetWidth() const = 0;

    /**
    * 縦幅取得
    * @ret 縦幅
    */
    virtual u32 GetHeight() const = 0;

    /**
    * 名前取得
    * @ret 名前
    */
    virtual const std::string& GetName() const = 0;

protected:

    virtual ~ITexture(){}
};

#endif  // __TEXTURE_INTERFACE_H__

// EOF
