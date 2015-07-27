//=============================================================================
//
// マウスインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MOUSE_INTERFACE_H__
#define __MOUSE_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include "common.h"

//*****************************************************************************
// マウスボタン定義
//*****************************************************************************
enum MouseButton
{
    BTN_LEFT = 0,
    BTN_RIGHT,
    BTN_CENTER
};

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
class IMouse
{
public:

    /**
    * 座標取得
    * @ret 座標
    */
    virtual const POINT& GetPosition() const = 0;

    /**
    * 移動量取得
    * @ret 移動量
    */
    virtual const POINT& GetMove() const = 0;
    
    /**
    * スクロール量取得
    * @ret スクロール量
    */
    virtual LONG GetScroll(void) const = 0;
    
    /**
    * プレス状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetPress(MouseButton btn) const = 0;

    /**
    * トリガー状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetTrigger(MouseButton btn) const = 0;

    /**
    * リリース状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetRelease(MouseButton btn) const = 0;

    /**
    * リピート状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetRepeat(MouseButton btn) const = 0;

protected:

    virtual ~IMouse(){}
};


#endif  // __MOUSE_INTERFACE_H__

// EOF
