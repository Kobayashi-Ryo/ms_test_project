//=============================================================================
//
// システムインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INTERFACE_SYSTEM_H__
#define __INTERFACE_SYSTEM_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
// interface
#include "IWindow.h"
#include "IDeviceHolder.h"
#include "ISound.h"
#include "IInputManager.h"
#include "IDebug.h"
#include "IResource.h"

//*****************************************************************************
// システムインターフェース
//*****************************************************************************
class ISystem
{
protected:

    typedef LRESULT WND_PROC_HOOK(HWND, UINT, WPARAM, LPARAM);

public:

    /**
    * ウィンドウ取得
    * @ret ウィンドウインターフェース
    */
    virtual IWindow* GetWindow() const = 0;

    /**
    * デバイスホルダー取得
    * @ret デバイスホルダーインターフェース
    */
    virtual IDeviceHolder* GetDeviceHolder() const = 0;

    /**
    * サウンド取得
    * @ret サウンドインターフェース
    */
    virtual ISound* GetSound() const = 0;

    /**
    * 入力マネージャ取得
    * @ret 入力マネージャインターフェース
    */
    virtual IInputManager* GetInputManager() const = 0;

    /**
    * デバッグ取得
    * @ret デバッグインターフェース
    */
    virtual IDebug* GetDebug() const = 0;

    /**
    * リソース取得
    * @ret リソースインターフェース
    */
    virtual IResource* GetResource() const = 0;

    /**
    * 取得
    * @ret インターフェース
    */

    /**
    * 強制終了
    */
    virtual void Abort() = 0;
    
    /**
    * ウィンドウプロシージャフック設定
    * @param hook フック関数
    */
    virtual void SetWndProcHook(WND_PROC_HOOK hook) = 0;

protected:

    /**
    * デストラクタ
    */
    virtual ~ISystem(){}
};

#endif  // __INTERFACE_SYSTEM_H__

// EOF
