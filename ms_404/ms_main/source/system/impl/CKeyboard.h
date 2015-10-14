//=============================================================================
//
// キーボード
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CInputObject.h"
#include "../IKeyboard.h"
#include <common/common.h>

//*****************************************************************************
// キーボード
//*****************************************************************************
class CKeyboard
    : private CUncopyable
    , public IKeyboard
{
private:

    /**
    * コンストラクタ
    */
    CKeyboard();

    /**
    * デストラクタ
    */
    ~CKeyboard();

public:

    /**
    * 生成
    * @ret マネージャー
    * @param pObj 入力オブジェクト
    * @param hWnd ウィンドウハンドル
    */
    static CKeyboard* Create(CInputObject* pObj, HWND hWnd);

    /**
    * 開放
    */
    void Release();

    /**
    * 更新
    */
    void Update();

    /**
    * プレス状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetPress(u8 key) const;

    /**
    * トリガー状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetTrigger(u8 key) const;

    /**
    * リリース状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetRelease(u8 key) const;

    /**
    * リピート状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetRepeat(u8 key) const;

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    * @param pObj 入力オブジェクト
    * @param hWnd ウィンドウハンドル
    */
    HRESULT Init(CInputObject* pObj, HWND hWnd);

private:

    LPDIRECTINPUTDEVICE8 m_pDev;    // デバイスへのポインタ

    static const s32 MAX_KEY = 256;    // キー最大数
    static const s32 REPEAT_TIME = 20; // リピートタイム(カウンタ)
    static const s32 KEY_ON = 128;    // キー入力フラグ

    BYTE m_aKeyState[MAX_KEY];      // キーボードの状態を格納するワーク
    BYTE m_aKeyTrigger[MAX_KEY];    // トリガー入力情報
    BYTE m_aKeyRelease[MAX_KEY];    // キーリリース情報
    BYTE m_aKeyRepeat[MAX_KEY];     // リピート情報
    s32 m_aKeyRepeatCount[MAX_KEY]; // キーを押している時間のカウント
};

#endif  // __KEYBOARD_H__

// EOF
