//=============================================================================
//
// デバイスインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INTERFACE_DEVICE_H__
#define __INTERFACE_DEVICE_H__

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <common/common.h>
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

//*****************************************************************************
// クラス
//*****************************************************************************
class IDevice
{
public:

    /**
    * 画面クリア変数予約
    */
    virtual void ClearColor(cf32 r, cf32 b, cf32 b) = 0;
    virtual void ClearDepth(cf32 d) = 0;
    virtual void ClearStencil(cu32 s) = 0;
    /**
    * 画面をクリア
    */
    virtual void Clear() = 0;

    /**
    * 頂点バッファ設定
    */
    virtual void SetVertexBuffer(cu32 index, IVertexBuffer* pBuff) = 0;
    /**
    * インデックスバッファ設定
    */
    virtual void SetIndexBuffer(IIndexBuffer* pBuff) = 0;
    /**
    * シェーダー設定
    */

    /**
    * ビューポート設定
    */
    virtual void SetViewport(s32 left, s32 top, s32 right, s32 bottom);

    /**
    * 描画
    */
    /**
    * インデックス付描画
    */
};

#endif  // __INTERFACE_DEVICE_H__

// EOF
