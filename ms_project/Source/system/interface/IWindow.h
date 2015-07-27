//=============================================================================
//
// ウィンドウインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INTERFACE_WINDOW_H__
#define __INTERFACE_WINDOW_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <string>

//*****************************************************************************
// ウィンドウインターフェース
//*****************************************************************************
class IWindow
{
public:

    /**
    * ウィンドウ横幅取得
    * @ret ウィンドウ横幅
    */
    virtual DWORD GetWidth() const = 0;
    
    /**
    * ウィンドウ縦幅取得
    * @ret ウィンドウ縦幅
    */
    virtual DWORD GetHeight() const = 0;
    
    /**
    * ウィンドウハンドル取得
    * @ret ウィンドウハンドル
    */
    virtual HWND GetHandle() const = 0;
    
    /**
    * キャプション設定
    * @param strCaption 設定するキャプション
    */
    virtual void SetCaption(const std::string& strCaption) = 0;

protected:

    /**
    * デストラクタ
    */
    virtual ~IWindow(){}
};

#endif  // __INTERFACE_WINDOW_H__

// EOF
