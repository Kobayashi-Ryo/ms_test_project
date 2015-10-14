//=============================================================================
//
// フレームバッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __FRAME_BUFFER_INTERFACE_H__
#define __FRAME_BUFFER_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "IColorBuffer.h"
#include "IDepthStencilBuffer.h"

//*****************************************************************************
// クラス
//*****************************************************************************
class IFrameBuffer
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
    * カラーバッファ設定
    */
    void SetColorBuffer(unsigned uIndex, IColorBuffer* pBuffer);
    
    /**
    * 深度バッファ設定
    */
    void SetDepthStencilBuffer(IDepthStencilBuffer* pBuffer);
};

#endif  // __FRAME_BUFFER_INTERFACE_H__

// EOF
