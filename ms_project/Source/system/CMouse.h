//=============================================================================
//
// マウス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CInputObject.h"
#include "interface/IMouse.h"
#include "common.h"

//*****************************************************************************
// マウス
//*****************************************************************************
class CMouse
    : private CUncopyable
    , public IMouse
{
private:

    /**
    * コンストラクタ
    */
    CMouse();

    /**
    * デストラクタ
    */
    ~CMouse();

public:

    /**
    * 生成
    * @ret マネージャー
    * @param pObj 入力オブジェクト
    * @param hWnd ウィンドウハンドル
    */
    static CMouse* Create(CInputObject* pObj, HWND hWnd);

    /**
    * 開放
    */
    void Release();

    /**
    * 更新
    */
    void Update();

    /**
    * 座標取得
    * @ret 座標
    */
    const POINT& GetPosition() const;

    /**
    * 移動量取得
    * @ret 移動量
    */
    const POINT& GetMove() const;

    /**
    * スクロール量取得
    * @ret スクロール量
    */
    LONG GetScroll() const;

    /**
    * プレス状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetPress(MouseButton btn) const;

    /**
    * トリガー状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetTrigger(MouseButton btn) const;

    /**
    * リリース状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetRelease(MouseButton btn) const;

    /**
    * リピート状態取得
    * @ret 状態判定
    * @param key 該当キー
    */
    bool GetRepeat(MouseButton btn) const;

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

    static const s32 KEY_ON = 128;    // 入力している
    static const s32 MAX_BUTTON = 8;// マウスのボタン数
    static const s32 REPEAT_TIME = 20; // リピートタイム(fps)
    
    // ウィンドウハンドル
    HWND                 m_hWnd;

    // マウス状態変数
    DIMOUSESTATE2        m_MouseState;
    DIMOUSESTATE2        m_MouseTrigger;
    DIMOUSESTATE2        m_MouseRelease;
    DIMOUSESTATE2        m_MouseRepeat;

    // リピート
    s32                  m_aMouseRepeatCount[MAX_BUTTON];

    // マウス座標
    POINT                m_pos;
    // 前回と今回の差分
    POINT                m_diff;

    // スクロール量
    LONG                 m_nScroll;
};

#endif  // __MOUSE_H__

// EOF
