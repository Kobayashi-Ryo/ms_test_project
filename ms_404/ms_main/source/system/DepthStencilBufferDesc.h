//=============================================================================
//
// 深度ステンシルバッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEPTH_STENCIL_BUFFER_DESC_H__
#define __DEPTH_STENCIL_BUFFER_DESC_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
enum DSFormat
{
    DSFMT_D16,
    DSFMT_D32,
    DSFMT_D24S8
};

struct DepthStencilBufferDesc
{
    // バッファ幅
    unsigned            width;
    unsigned            height;
    // フォーマット
    DSFormat           format;
};

#endif  // __DEPTH_STENCIL_BUFFER_DESC_H__

// EOF
