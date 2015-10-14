//=============================================================================
//
// アプリケーション
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CApplication.h"
#include "CScene.h"
#include <common/D3DX.h>

#include <system/impl/CSystem.h>
#include <system/impl/CHardwareTimer.h>
#include <system/impl/CDeviceHolder.h>

#include <common/DebugUtil.h>

namespace
{
    const DWORD DIFF_MILLISEC = 16;
};

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CApplication* CApplication::m_spApp = nullptr;

//=============================================================================
// コンストラクタ
//=============================================================================
CApplication::CApplication()
    : m_bIsRunning(true)
    , m_pCurrentScene(nullptr)
    , m_pHardwareTimer(nullptr)
    , m_pSystem(nullptr)
{
    m_pSystem = new CSystem();
    _CriticalAssert(!IS_NULL(m_pSystem));
    HRESULT hr = m_pSystem->Initialize("");
    _CriticalAssert(SUCCEEDED(hr));
    
    // ハードウェアタイマー
    m_pHardwareTimer = CHardwareTimer::Create();
    _Assert(m_pHardwareTimer);

    m_spApp = this;
}

//=============================================================================
// デストラクタ
//=============================================================================
CApplication::~CApplication()
{
    SafeRelease(m_pCurrentScene);
    SafeRelease(m_pSystem);
    SafeRelease(m_pHardwareTimer);
    m_spApp = nullptr;
}

//=============================================================================
// アプリケーションを終了させる
//=============================================================================
void CApplication::Finish()
{
    m_bIsRunning = false;
    m_pSystem->Finish();
}

//=============================================================================
// システムの取得
//=============================================================================
ISystem* CApplication::GetSystem()
{
    return m_pSystem;
}

//=============================================================================
// 現在のシーン取得
//=============================================================================
CScene* CApplication::GetCurrentScene()
{
    return m_pCurrentScene;
}

//=============================================================================
// アプリケーション開始
//=============================================================================
s32 CApplication::Run()
{
    if(!m_spApp->Init())
    {
        return -1;
    }

    while(m_pSystem->IsRunning())
    {
        m_pHardwareTimer->Start();
        
        // システム更新
        m_pSystem->Update();
        // シーン更新
        if(m_pCurrentScene)
        {
            m_pCurrentScene->Update();
        }

        if(SUCCEEDED(m_pSystem->BeginDraw()))
        {
            // アプリケーション描画
            // HACK 画面クリア
            m_pSystem->GetDeviceHolder()->GetDevice()->Clear(
                0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
                D3DXCOLOR(0.3f, 0.3f, 0.3f,0), 1, 0);
            // 描画処理
            if(m_pCurrentScene)
            {
                m_pCurrentScene->Draw();
            }

            m_pSystem->DebugDraw();

            m_pSystem->EndDraw();
        }
        
        // バッファスワップ
        m_pSystem->SwapBuffers();

        m_pHardwareTimer->End();

        // スレッドお休み
        m_pHardwareTimer->Sleep(DIFF_MILLISEC);
    }

    return 0;
}

//=============================================================================
// シーンを別のシーンで置き換え
//=============================================================================
void CApplication::ReplaceScene(CScene* pScene)
{
    if(!pScene) return;
    if(m_pCurrentScene == pScene) return;

    if(m_pCurrentScene)
    {
        // シーンを開放
        SafeRelease(m_pCurrentScene);
    }
    m_pCurrentScene = pScene;
}

//=============================================================================
// アプリケーションインスタンス取得
//=============================================================================
CApplication* CApplication::GetInstance()
{
    return m_spApp;
}

// EOF
