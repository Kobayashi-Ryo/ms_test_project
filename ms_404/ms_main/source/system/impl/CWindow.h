//=============================================================================
//
// ウィンドウクラス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __WINDOW_H__
#define __WINDOW_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <string>

#include "../IWindow.h"
#include <common/CUncopyable.h>

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CThread;

//*****************************************************************************
// ウィンドウ情報クラス
//*****************************************************************************
struct WindowDesc
{
    DWORD uWidth;
    DWORD uHeight;
    std::string strCaption;
    std::string strClassName;
    WNDPROC pWndProc;
    void* pAsyncData;   // 非同期処理用データ
    void* pAsyncProc;   // 非同期処理用関数
};

//*****************************************************************************
// ウィンドウクラス
//*****************************************************************************
class CWindow
    : private CUncopyable
    , public IWindow
{
private:
    CWindow();

    ~CWindow();

public:

    enum Message
    {
        MESSAGE_OK,         // メッセージが処理された
        MESSAGE_TERMINATE   // 終了メッセージが来た
    };

    // 生成処理
    static CWindow* Create(
        const WindowDesc& desc);

    // 開放
    void Release();

    // メッセージ処理
    Message ProcMessage(MSG& msg);

    // ウィンドウ表示
    void ShowWindow();

    // ウィンドウ横幅取得
    DWORD GetWidth() const;

    // ウィンドウ縦幅取得
    DWORD GetHeight() const;

    // ウィンドウハンドル取得
    HWND GetHandle() const;

    // キャプション設定
    void SetCaption(const std::string& strCaption);

    // カーソルをクリップする
    void ClipCursor(const int x, const int y);
    // カーソルのクリップ解除
    void UnclipCursor();

    // 初期化済み判定
    bool IsInitialized();

    // 初期化
    HRESULT Initialize();

private:

    // 内部生成処理
    HRESULT InnerCreate(const WindowDesc& desc);

private:
    
    // ウィンドウスタイル
    static const int GAME_WINDOW;

    // ウィンドウハンドル
    HWND m_hWnd;

    // ウィンドウ情報
    WindowDesc m_desc;

    // スレッド
    CThread *m_pThread;

    // 初期化済みフラグ
    volatile bool m_bInitialized;
};

#endif  // __WINDOW_H__

// EOF
