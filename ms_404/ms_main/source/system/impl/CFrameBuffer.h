//=============================================================================
//
// フレームバッファ [CFrameBuffer.h]
// Author : Ryo Kobayashi
// Data : 2015/5/3
//
//=============================================================================
#pragma once
#ifndef __FRAME_BUFFER_H__
#define __FRAME_BUFFER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../IFrameBuffer.h"

class CFrameBuffer
    : public IFrameBuffer
{
public:

    static const int MAX_COLORBUFFER = 4;

    static CFrameBuffer* Create();

    HRESULT Initialize(LPDIRECT3DDEVICE9 pDev);

    void Release();

    void Attach();
    void Detach();

    void SetDevice(LPDIRECT3DDEVICE9 pDev);
    void SetColorBuffer(u32 uIndex, IColorBuffer* pBuffer);
    void SetDepthStencilBuffer(IDepthStencilBuffer* pBuffer);

protected:

    CFrameBuffer();

private:

    IColorBuffer*        m_apFB[MAX_COLORBUFFER];
    IDepthStencilBuffer* m_pDSB;

    LPDIRECT3DDEVICE9    m_pDev;
};

#endif  // __FRAME_BUFFER_H__

// EOF