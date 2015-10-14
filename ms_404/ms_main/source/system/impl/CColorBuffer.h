//=============================================================================
//
// カラーバッファ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __COLOR_BUFFER_H__
#define __COLOR_BUFFER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../IColorBuffer.h"
#include "CLostResource.h"
#include <common/DirectX.h>
#include <common/CUncopyable.h>

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CDeviceHolder;
class CTexture;

class CColorBuffer
    : public IColorBuffer
    , public CLostResource
{
public:

    static CColorBuffer* Create(CDeviceHolder* pHolder, const ColorBufferDesc& desc);

    HRESULT Initialize(CDeviceHolder* pHolder, const ColorBufferDesc& desc);

    void Release();
    
    void Attach();
    void Detach();
    
    void SetDevice(LPDIRECT3DDEVICE9 pDev);
    void SetRenderTargetIndex(cu32 uIndex);

    u32 GetWidth() const;
    u32 GetHeight() const;

    ITexture* GetTexture() const;

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

    CColorBuffer();
    ~CColorBuffer();

private:

    void Uninitialize();

private:
    
    // テクスチャサーフェス
    LPDIRECT3DSURFACE9  m_pSurface;
    // レンダリングターゲットテクスチャ
    CTexture*  m_pTexture;

    // 前回設定されていたサーフェス
    LPDIRECT3DSURFACE9  m_pPrevSurface;

    // フレームバッファ情報
    ColorBufferDesc     m_desc;

    // デバイス
    LPDIRECT3DDEVICE9   m_pDev;
};

#endif  // __COLOR_BUFFER_H__

// EOF
