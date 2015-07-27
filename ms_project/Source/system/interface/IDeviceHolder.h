//=============================================================================
//
// デバイスインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEVICE_HOLDER_INTERFACE_H__
#define __DEVICE_HOLDER_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "DirectX.h"

//*****************************************************************************
// デバイスインターフェース
//*****************************************************************************
class IDeviceHolder
{
public:

    /**
    * DirectX9デバイス取得
    * @ret Direct9デバイス
    */
    virtual LPDIRECT3DDEVICE9 GetDevice() const = 0;

    /**
    * バックバッファ横幅取得
    * @ret バックバッファ横幅
    */
    virtual DWORD GetBackBufferWidth() const = 0;

    /**
    * バックバッファ縦幅取得
    * @ret バックバッファ縦幅
    */
    virtual DWORD GetBackBufferHeight() const = 0;

protected:

    virtual ~IDeviceHolder(){}
};

#endif  // __DEVICE_HOLDER_INTERFACE_H__

// EOF
