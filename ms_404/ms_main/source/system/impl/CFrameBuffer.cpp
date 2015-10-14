//=============================================================================
//
// フレームバッファ [CFrameBuffer.cpp]
// Author : Ryo Kobayashi
// Data : 2015/5/11
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CFrameBuffer.h"
#include "../IColorBuffer.h"
#include "../IDepthStencilBuffer.h"
#include <common/DebugUtil.h>

CFrameBuffer* CFrameBuffer::Create()
{
    CFrameBuffer* pFB = new CFrameBuffer();
    
    if(pFB)
    {
        //INIT_CHECK(pDSBuffer->Initialize(pHolder, desc));
        _PrintConsole("フレームバッファ");
    }

    return pFB;
}

HRESULT CFrameBuffer::Initialize(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;

    return S_OK;
}

void CFrameBuffer::Release()
{
    m_pDev = nullptr;
    delete this;
}

void CFrameBuffer::Attach()
{
    for(int i = 0; i < MAX_COLORBUFFER; i++)
    {
        if(m_apFB[i]) m_apFB[i]->Attach();
    }

    if(m_pDSB) m_pDSB->Attach();
}

void CFrameBuffer::Detach()
{
    for(int i = 0; i < MAX_COLORBUFFER; i++)
    {
        if(m_apFB[i]) m_apFB[i]->Detach();
    }

    if(m_pDSB) m_pDSB->Detach();
}

void CFrameBuffer::SetDevice(LPDIRECT3DDEVICE9 pDev)
{
    m_pDev = pDev;
}

void CFrameBuffer::SetColorBuffer(u32 uIndex, IColorBuffer* pBuffer)
{
    if(uIndex >= MAX_COLORBUFFER)
    {
        return;
    }
    
    m_apFB[uIndex] = pBuffer;
}

void CFrameBuffer::SetDepthStencilBuffer(IDepthStencilBuffer* pBuffer)
{
    m_pDSB = pBuffer;
}
























CFrameBuffer::CFrameBuffer()
    : m_pDSB(nullptr)
    , m_pDev(nullptr)
{
    for(int i = 0; i < MAX_COLORBUFFER; i++)
    {
        m_apFB[i] = nullptr;
    }
}

// EOF