//=============================================================================
//
// キーボードインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __KEYBOARD_INTERFACE_H__
#define __KEYBOARD_INTERFACE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <Windows.h>
#include <common/common.h>

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
class IKeyboard
{
public:

    /**
    * プレス状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetPress(u8 key) const = 0;

    /**
    * トリガー状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetTrigger(u8 key) const = 0;

    /**
    * リリース状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetRelease(u8 key) const = 0;

    /**
    * リピート状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    virtual bool GetRepeat(u8 key) const = 0;

protected:

    virtual ~IKeyboard(){}
};


#endif  // __KEYBOARD_INTERFACE_H__

// EOF
