//=============================================================================
//
// カラーバッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __COLOR_BUFFER_INTERFACE_H__
#define __COLOR_BUFFER_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "ColorBufferDesc.h"
#include "ITexture.h"

//*****************************************************************************
// クラス
//*****************************************************************************
class IColorBuffer
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
    * レンダーターゲットに設定するときの番号を設定
    */
    virtual void SetRenderTargetIndex(cu32 uIndex) = 0;
    
    /**
    * バッファ横幅取得
    */
    virtual u32 GetWidth() const = 0;
    
    /**
    * バッファ縦幅取得
    */
    virtual u32 GetHeight() const = 0;
    
    /**
    * テクスチャ取得
    */
    virtual ITexture* GetTexture() const = 0;
};

#endif  // __COLOR_BUFFER_INTERFACE_H__

// EOF
