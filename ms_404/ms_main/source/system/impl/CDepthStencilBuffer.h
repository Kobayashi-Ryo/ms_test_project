//=============================================================================
//
// 深度ステンシルバッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEPTH_STENCIL_BUFFER_H__
#define __DEPTH_STENCIL_BUFFER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../IDepthStencilBuffer.h"
#include <common/DirectX.h>
#include "CLostResource.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;

class CDepthStencilBuffer
    : public IDepthStencilBuffer
    , public CLostResource
{
public:
    
    static CDepthStencilBuffer* Create(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc);

    HRESULT Initialize(CDeviceHolder* pHolder, const DepthStencilBufferDesc& desc);

    void Release();
    
    void Attach();
    void Detach();
    
    void SetDevice(LPDIRECT3DDEVICE9 pDev);

    u32 GetWidth() const;
    u32 GetHeight() const;
    
    /**
    * リソースの強制的な削除
    */
    void CleanUp();

    /**
    * リソース情報の保存
    */
    void Restore();

    /**
    * リソース情報の再読み込み
    */
    void Reload(CDeviceHolder* pHolder);

protected:

    CDepthStencilBuffer();
    ~CDepthStencilBuffer();

private:

    // 深度バッファサーフェス
    LPDIRECT3DSURFACE9      m_pDepthSurface;

    // 前回の深度バッファ
    LPDIRECT3DSURFACE9      m_pPrevSurface;

    // 深度バッファ情報
    D3DSURFACE_DESC  m_desc;

    // デバイス
    LPDIRECT3DDEVICE9       m_pDev;
};

#endif  // __DEPTH_STENCIL_BUFFER_H__

// EOF
