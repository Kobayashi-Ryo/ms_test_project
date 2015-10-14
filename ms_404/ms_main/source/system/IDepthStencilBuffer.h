//=============================================================================
//
// 深度ステンシルバッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEPTH_STENCIL_INTERFACE_H__
#define __DEPTH_STENCIL_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/common.h>
#include "DepthStencilBufferDesc.h"

//*****************************************************************************
// クラス
//*****************************************************************************
class IDepthStencilBuffer
{
public:

    virtual void Attach() = 0;
    virtual void Detach() = 0;

    virtual u32 GetWidth() const = 0;
    virtual u32 GetHeight() const = 0;
};

#endif  // __DEPTH_STENCIL_INTERFACE_H__

// EOF
