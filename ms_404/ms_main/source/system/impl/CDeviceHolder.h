//=============================================================================
//
// デバイスを保持するクラス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __DEVICE_HOLDER_H__
#define __DEVICE_HOLDER_H__

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <common/DirectX.h>
#include <common/CUncopyable.h>

// interface
#include "../IDeviceHolder.h"

//*****************************************************************************
// デバイス情報クラス
//*****************************************************************************
struct DeviceDesc
{
    DWORD uBackBufferWidth;
    DWORD uBackBufferHeight;
    BOOL bWindowed;
    HWND hWnd;
};

//*****************************************************************************
// デバイスを保持するクラス
//*****************************************************************************
class CDeviceHolder
    : private CUncopyable
    , public IDeviceHolder
{
private:

    /**
    * コンストラクタ
    */
    CDeviceHolder();

    /**
    * デストラクタ
    */
    ~CDeviceHolder();

public:

    /**
    * 生成処理
    * @ret インスタンス
    * @param desc デバイス情報
    */
    static CDeviceHolder* Create(const DeviceDesc& desc);

    /**
    * 開放処理
    */
    void Release();

    /**
    * DirectX9デバイス取得
    * @ret Direct9デバイス
    */
    LPDIRECT3DDEVICE9 GetDevice() const;

    /**
    * バックバッファ横幅取得
    * @ret バックバッファ横幅
    */
    DWORD GetBackBufferWidth() const;

    /**
    * バックバッファ縦幅取得
    * @ret バックバッファ縦幅
    */
    DWORD GetBackBufferHeight() const;

    /**
    * デバイス情報取得
    * @ret デバイス情報
    */
    const D3DPRESENT_PARAMETERS& GetPresentParameters() const;

    /**
    * デバイスリセット
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT Reset();

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param desc デバイス情報
    */
    HRESULT Init(const DeviceDesc& desc);

private:

    // デバイス
    LPDIRECT3DDEVICE9 m_pDev;

    // バックバッファサイズ
    DWORD m_uBackBufferWidth;
    DWORD m_uBackBufferHeight;

    // デバイスパラメータ
    D3DPRESENT_PARAMETERS m_PresentParam;
};

#endif  // __DEVICE_HOLDER_H__

// EOF
