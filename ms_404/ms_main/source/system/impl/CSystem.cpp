//=============================================================================
//
// システムクラス
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CSystem.h"

// window
#include "CWindow.h"
// device holder
#include "CDeviceHolder.h"
// sound manager
#include "CSoundManager.h"
// input manager
#include "CInputManager.h"
// debug
#include "CDebug.h"
// resource manager
#include "CResourceManager.h"

// hardware timer
#include "CHardwareTimer.h"

// thread
#include <process.h>

// util
#include <common/DebugUtil.h>

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
    static const DWORD DIFF_MILLISEC = 16;
};

//*****************************************************************************
// 静的メンバ変数初期化
//*****************************************************************************
std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)> CSystem::m_sWndProcHook = nullptr;

//*****************************************************************************
// 名前空間
//*****************************************************************************
namespace
{
unsigned __stdcall WindowProc(void* pData)
{
    //=============================================================================
    // ウィンドウ処理
    //=============================================================================
    CSystem *pSys = (CSystem*)pData;

    CWindow *pWindow = pSys->GetWindowInst();
    HRESULT hr = pWindow->Initialize();
    if(FAILED(hr))
    {
      _endthreadex(0);
      return 0;
    }

    // ウィンドウ表示
    pWindow->ShowWindow();

    MSG Msg;
    Msg.message = WM_NULL;
    volatile bool bLoop = true;
    while(bLoop)
    {
      // 終了
      if(CWindow::MESSAGE_TERMINATE == pWindow->ProcMessage(Msg))
      {
        pSys->Finish();
        bLoop = false;
        break;
      }
      Sleep(16);
    }

    _endthreadex(0);
    return 0;
}
};

//=============================================================================
// コンストラクタ
//=============================================================================
CSystem::CSystem()
    : m_pWindow(nullptr)
    , m_pDeviceHolder(nullptr)
    , m_pSoundManager(nullptr)
    , m_pInputManager(nullptr)
    , m_pDebug(nullptr)
    , m_pResourceManager(nullptr)
    , m_pHardwareTimer(nullptr)
    , m_bIsRunning(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSystem::~CSystem()
{
    SafeRelease(m_pResourceManager);
    SafeRelease(m_pDebug);
    SafeRelease(m_pInputManager);
    SafeRelease(m_pSoundManager);
    SafeRelease(m_pDeviceHolder);
    SafeRelease(m_pWindow);
    SafeRelease(m_pHardwareTimer);
}

//=============================================================================
// システムの実行
//=============================================================================
s32 CSystem::Run(const std::string& arg)
{
    CSystem* pSys = new CSystem();

    HRESULT hr = pSys->Initialize(arg);
    _CriticalAssert(SUCCEEDED(hr));

    s32 result = 0;

    while(pSys->IsRunning())
    {
        result = pSys->Update();
    }

    pSys->Release();

    return result;
}

//=============================================================================
// 描画開始
//=============================================================================
HRESULT CSystem::BeginDraw()
{
    HRESULT suc = m_pDeviceHolder->GetDevice()->BeginScene();
    return suc;
}

//=============================================================================
// デバッグ描画
//=============================================================================
void CSystem::DebugDraw()
{
    m_pDebug->Draw();
}

//=============================================================================
// 描画終了
//=============================================================================
void CSystem::EndDraw()
{
    m_pDeviceHolder->GetDevice()->EndScene();
    m_pDebug->Clear();
}

//=============================================================================
// バックバッファ交換
//=============================================================================
void CSystem::SwapBuffers()
{
    HRESULT hr = m_pDeviceHolder->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
    if(!SUCCEEDED(hr))
    {
        // デバイスロスト
        m_pResourceManager->Reset();
    }
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSystem::Initialize(const std::string& arg)
{
    HRESULT hr = S_OK;

    // ハードウェアタイマー
    m_pHardwareTimer = CHardwareTimer::Create();
    _Assert(m_pHardwareTimer);

    // ウィンドウ
    hr = CreateWindowMS();
    _Assert(SUCCEEDED(hr));

    // デバイス
    hr = CreateDeviceHolder();
    _Assert(SUCCEEDED(hr));
    
    // リソースマネージャー
    hr = CreateResourceManager();
    _Assert(SUCCEEDED(hr));

    // 入力マネージャー
    hr = CreateInputManager();
    _Assert(SUCCEEDED(hr));

    // サウンドマネージャー
    hr = CreateSoundManager();
    _Assert(SUCCEEDED(hr));

    // デバッグ
    hr = CreateDebug();
    _Assert(SUCCEEDED(hr));

    m_bIsRunning = true;
    _PrintConsole("システム\n");

    return hr;
}

//=============================================================================
// 開放
//=============================================================================
void CSystem::Release()
{
    delete this;
}

//=============================================================================
// 更新
//=============================================================================
s32 CSystem::Update()
{
    // 各システム更新
    m_pInputManager->Update();

    /*
    m_pHardwareTimer->Start();

    // 各システム更新
    m_pInputManager->Update();

    // アプリケーション更新
    m_pDebug->Print("デバッグテスト\n");
    auto key = m_pInputManager->GetKeyboard();
    if(key->GetPress(DIK_P))
    {
        m_pDebug->Print("ぴー\n");
    }

    HRESULT suc = m_pDeviceHolder->GetDevice()->BeginScene();
    if(SUCCEEDED(suc))
    {
        // アプリケーション描画
        // HACK 画面クリア
        m_pDeviceHolder->GetDevice()->Clear(
            0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
            D3DXCOLOR(0,0,0,0), 1, 0);

        // システム系描画
        m_pDebug->Draw();

        m_pDeviceHolder->GetDevice()->EndScene();
    }
    else
    {
        m_pDebug->Clear();
    }

    // HACK 画面スワップ
    HRESULT hr = m_pDeviceHolder->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
    if(!SUCCEEDED(hr))
    {
        // デバイスロスト
        m_pResourceManager->Reset();
    }

    m_pHardwareTimer->End();

    // スレッドお休み
    m_pHardwareTimer->Sleep(DIFF_MILLISEC);
    */

    // TODO : 何か適当な値
    return 0;
}

//=============================================================================
// 終了
//=============================================================================
void CSystem::Finish()
{
    m_bIsRunning = false;
}

//=============================================================================
// システム起動中かどうか
//=============================================================================
bool CSystem::IsRunning()
{
    return m_bIsRunning;
}

//=============================================================================
// ウィンドウ取得
//=============================================================================
IWindow* CSystem::GetWindow() const
{
    return m_pWindow;
}

//=============================================================================
// デバイスホルダー取得
//=============================================================================
IDeviceHolder* CSystem::GetDeviceHolder() const
{
    return m_pDeviceHolder;
}

//=============================================================================
// デバイスホルダー取得
//=============================================================================
ISound* CSystem::GetSound() const
{
    return m_pSoundManager;
}

//=============================================================================
// 入力マネージャ取得
//=============================================================================
IInputManager* CSystem::GetInputManager() const
{
    return m_pInputManager;
}

//=============================================================================
// デバッグ取得
//=============================================================================
IDebug* CSystem::GetDebug() const
{
    return m_pDebug;
}

//=============================================================================
// リソース取得
//=============================================================================
IResource* CSystem::GetResource() const
{
    return m_pResourceManager;
}

//=============================================================================
// 強制終了
//=============================================================================
void CSystem::Abort()
{
    Finish();
    _AbortExpr("強制的に中断されました");
}

//=============================================================================
// ウィンドウ生成
//=============================================================================
HRESULT CSystem::CreateWindowMS()
{
    WindowDesc desc;
    // TODO ウィンドウサイズは設定ファイルから
    desc.uWidth = 960;
    desc.uHeight = 540;
    desc.strCaption = "MS 404";
    desc.strClassName = "g_04_fever";
    desc.pWndProc = WndProc;
    desc.pAsyncData = this;
    desc.pAsyncProc = ::WindowProc;
    m_pWindow = CWindow::Create(desc);
    if(IS_NULL(m_pWindow))
    {
        return E_FAIL;
    }

    return S_OK;
}

//=============================================================================
// デバイスホルダー生成
//=============================================================================
HRESULT CSystem::CreateDeviceHolder()
{
    while(!m_pWindow->IsInitialized()){}
    DeviceDesc desc;
    desc.bWindowed = TRUE;
    desc.hWnd = m_pWindow->GetHandle();
    desc.uBackBufferWidth = m_pWindow->GetWidth();
    desc.uBackBufferHeight = m_pWindow->GetHeight();
    m_pDeviceHolder = CDeviceHolder::Create(desc);

    if(IS_NULL(m_pDeviceHolder))
    {
        return E_FAIL;
    }

    return S_OK;
}

//=============================================================================
// サウンドマネージャー生成
//=============================================================================
HRESULT CSystem::CreateSoundManager()
{
    m_pSoundManager = CSoundManager::Create();
    if(IS_NULL(m_pSoundManager))
    {
        return E_FAIL;
    }
    return S_OK;
}

//=============================================================================
// 入力マネージャー生成
//=============================================================================
HRESULT CSystem::CreateInputManager()
{
    while(!m_pWindow->IsInitialized()){}
    m_pInputManager = CInputManager::Create(m_pWindow->GetHandle());
    if(IS_NULL(m_pInputManager))
    {
        return E_FAIL;
    }
    return S_OK;
}

//=============================================================================
// デバッグ生成
//=============================================================================
HRESULT CSystem::CreateDebug()
{
    m_pDebug = CDebug::Create(m_pDeviceHolder, m_pResourceManager);
    if(IS_NULL(m_pDebug))
    {
        return E_FAIL;
    }

    return S_OK;
}

//=============================================================================
// リソースマネージャ生成
//=============================================================================
HRESULT CSystem::CreateResourceManager()
{
    m_pResourceManager = CResourceManager::Create(m_pDeviceHolder);
    if(IS_NULL(m_pResourceManager))
    {
        return E_FAIL;
    }
    return S_OK;
}

//=============================================================================
// フック関数設定
//=============================================================================
void CSystem::SetWndProcHook(WND_PROC_HOOK Hook)
{
    m_sWndProcHook = Hook;
}

//=============================================================================
// ウィンドウ取得
//=============================================================================
CWindow* CSystem::GetWindowInst() const
{
    return m_pWindow;
}

//=============================================================================
// デバイスホルダー取得
//=============================================================================
CDeviceHolder* CSystem::GetDeviceHolderInst() const
{
    return m_pDeviceHolder;
}

//=============================================================================
// ウィンドウプロシージャ
//=============================================================================
LRESULT CALLBACK CSystem::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if(m_sWndProcHook)
  {
    m_sWndProcHook(hWnd, uMsg, wParam, lParam);
  }

  // メッセージによって分岐
  switch(uMsg)
  {
    // ウィンドウ破棄
  case WM_DESTROY:
    // 終了メッセージ送出
    PostQuitMessage(0);
    break;

    // キー入力
  case WM_KEYDOWN:
    // キー入力処理
    KeyInputProc(hWnd, wParam);
    break;

    // ウィンドウサイズ変更時
  case WM_SIZE:
    break;

  default:
    break;
  }

  // 標準処理に投げる
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// キー入力処理
//=============================================================================
void CSystem::KeyInputProc(HWND hWnd, WPARAM wParam)
{
  switch(wParam)
  {
    // エスケープが押されたとき
  case VK_ESCAPE:
    DestroyWindow(hWnd);
    break;
  }
}

// EOF
