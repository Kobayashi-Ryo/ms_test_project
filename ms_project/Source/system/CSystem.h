//=============================================================================
//
// システムクラス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <string>
#include <functional>

// common
#include "common.h"

// interface
#include "interface/ISystem.h"


//*****************************************************************************
// 前方参照
//*****************************************************************************
// window
class CWindow;
// device holder
class CDeviceHolder;
// sound manager
class CSoundManager;
// input manager
class CInputManager;
// debug
class CDebug;
// resource manager
class CResourceManager;

// hardware timer
class CHardwareTimer;

//*****************************************************************************
// システムクラス
//*****************************************************************************
class CSystem
    : private CUncopyable
    , public ISystem
{
private:

    /**
    * コンストラクタ
    */
    CSystem();

    /**
    * デストラクタ
    */
    ~CSystem();
    
public:

    /**
    * システムの実行
    * @ret 実行結果
    * @param arg プログラムに渡された引数
    */
    static s32 Run(const std::string& arg);
    
    /**
    * 初期化
    * @ret 成功:S_OK 失敗:E_FAIL
    * @param プログラムに渡された引数
    */
    HRESULT Initialize(const std::string& arg);

    /**
    * 開放
    */
    void Release();
    
    /**
    * 更新
    */
    s32 Update();
    
    /**
    * 終了
    */
    void Finish();
    
    /**
    * システム起動中かどうか
    * @ret true:起動中 false:終了中
    */
    bool IsRunning();


    /**
    * ウィンドウ取得
    * @ret ウィンドウインターフェース
    */
    IWindow* GetWindow() const;

    /**
    * デバイスホルダー取得
    * @ret デバイスホルダーインターフェース
    */
    IDeviceHolder* GetDeviceHolder() const;

    /**
    * サウンド取得
    * @ret サウンドインターフェース
    */
    ISound* GetSound() const;

    /**
    * 入力マネージャ取得
    * @ret 入力マネージャインターフェース
    */
    IInputManager* GetInputManager() const;

    /**
    * デバッグ取得
    * @ret デバッグインターフェース
    */
    IDebug* GetDebug() const;
    
    /**
    * リソース取得
    * @ret リソースインターフェース
    */
    IResource* GetResource() const;

    /**
    * 強制終了
    */
    void Abort();

    /**
    * フックプロシージャ設定
    * @param hook フック関数
    */
    void SetWndProcHook(WND_PROC_HOOK hook);


    /**
    * ウィンドウ取得
    * @ret ウィンドウインスタンス
    */
    CWindow* GetWindowInst() const;
    
    /**
    * デバイスホルダー取得
    * @ret デバイスホルダーインスタンス
    */
    CDeviceHolder* GetDeviceHolderInst() const;

private:

    /**
    * ウィンドウ生成
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT CreateWindowMS();

    /**
    * デバイスホルダー生成
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT CreateDeviceHolder();

    /**
    * サウンドマネージャー生成
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT CreateSoundManager();

    /**
    * 入力マネージャー生成
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT CreateInputManager();

    /**
    * デバッグ生成
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT CreateDebug();

    /**
    * リソースマネージャ生成
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT CreateResourceManager();

    /**
    * ウィンドウプロシージャ
    * 細かい説明はググって
    */
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /**
    * キー入力
    * そのうち廃止
    */
    static void KeyInputProc(HWND hWnd, WPARAM wParam);

private:

    // ウィンドウ
    CWindow* m_pWindow;

    // デバイス
    CDeviceHolder* m_pDeviceHolder;

    // サウンド
    CSoundManager* m_pSoundManager;

    // 入力
    CInputManager* m_pInputManager;

    // デバッグ
    CDebug* m_pDebug;

    // リソースマネージャー
    CResourceManager* m_pResourceManager;

    // ハードウェアタイマー
    CHardwareTimer* m_pHardwareTimer;

    // システム起動中フラグ
    bool m_bIsRunning;


    // アプリケーション


    // プロシージャフック
    static std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> m_sWndProcHook;
};

#endif  // __SYSTEM_H__

// EOF
