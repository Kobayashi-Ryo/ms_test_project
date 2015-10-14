//=============================================================================
//
// ウィンドウクラス [CWindow.h]
//
// Date : 2015/1/31
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CWindow.h"
#include "CThread.h"
#include <common/DebugUtil.h>

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
// ウィンドウスタイル
const int CWindow::GAME_WINDOW = (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX));

//=============================================================================
// コンストラクタ
//=============================================================================
CWindow::CWindow()
    : m_hWnd(0)
    , m_desc()
    , m_pThread(nullptr)
    , m_bInitialized(false)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CWindow::~CWindow()
{
    // スレッドの開放
    m_pThread->release();
    // ウィンドウクラス登録解除
    UnregisterClass(m_desc.strClassName.c_str(), GetModuleHandle(NULL));
}

//=============================================================================
// 生成処理
//=============================================================================
CWindow* CWindow::Create(const WindowDesc& desc)
{
    CWindow* pWnd = new CWindow();

    if(pWnd)
    {
        pWnd->InnerCreate(desc);
        _CriticalAssertExpr(pWnd, "ウィンドウの生成に失敗");
        _PrintConsole("ウィンドウ\n");
    }

    return pWnd;
}

//=============================================================================
// 開放
//=============================================================================
void CWindow::Release()
{
    delete this;
}

//=============================================================================
// メッセージ処理
//=============================================================================
CWindow::Message CWindow::ProcMessage(MSG& msg)
{
    // メッセージがある場合処理
    Message message = MESSAGE_OK;
    BOOL bIsMessageExist = PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
    if(TRUE == bIsMessageExist)
    {
      // 終了メッセージが送られた場合
      if(msg.message == WM_QUIT)
      {
        message = MESSAGE_TERMINATE;
      }
      // 送られていない場合
      else
      {
        // メッセージの翻訳と送出
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    return message;
}

//=============================================================================
// ウィンドウ表示
//=============================================================================
void CWindow::ShowWindow()
{
    // ウィンドウ表示
    ::ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
}

//=============================================================================
// ウィンドウ横幅取得
//=============================================================================
DWORD CWindow::GetWidth() const
{
    return m_desc.uWidth;
}

//=============================================================================
// ウィンドウ縦幅取得
//=============================================================================
DWORD CWindow::GetHeight() const
{
    return m_desc.uHeight;
}

//=============================================================================
// ウィンドウハンドル取得
//=============================================================================
HWND CWindow::GetHandle() const
{
    return m_hWnd;
}

//=============================================================================
// キャプション設定
//=============================================================================
void CWindow::SetCaption(const std::string& strCaption)
{
    m_desc.strCaption = strCaption;
    // ウィンドウのキャプションを設定
    SetWindowText(m_hWnd, m_desc.strCaption.c_str());
}

//=============================================================================
// カーソルをクリップする
//=============================================================================
void CWindow::ClipCursor(const int x, const int y)
{
    POINT p = {x, y};
    ClientToScreen(m_hWnd, &p);
    RECT clip = {p.x - 1, p.y - 1,
            p.x + 1, p.y + 1};
    ::ClipCursor(&clip);
}

//=============================================================================
// カーソルのクリップを解除する
//=============================================================================
void CWindow::UnclipCursor()
{
    ::ClipCursor(NULL);
}

//=============================================================================
// 初期化済み判定
//=============================================================================
bool CWindow::IsInitialized()
{
    return m_bInitialized;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CWindow::Initialize()
{
    HRESULT hr = S_OK;

    HINSTANCE hInstance = GetModuleHandle(NULL);

    RECT rc;
    // ウィンドウ矩形範囲設定
    rc.top = 0;
    rc.left = 0;
    rc.right = m_desc.uWidth;
    rc.bottom = m_desc.uHeight;

    // ウィンドウクラス初期化
    WNDCLASSEX wcex =
    {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        m_desc.pWndProc,  // ウィンドウプロシージャ関数
        0,
        0,
        hInstance,
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        m_desc.strClassName.c_str(),
        NULL
    };

    // ウィンドウクラス登録
    if(FAILED(RegisterClassEx(&wcex)))
    {
        MessageBox(NULL, "ウィンドウクラス登録失敗", "エラー", MB_OK);
        return E_FAIL;
    }

    // ウィンドウ幅合わせ
    AdjustWindowRect(
      &rc,    // ウィンドウ幅
      GAME_WINDOW, // ウィンドウスタイル
      FALSE);    // メニューの有無

    // ウィンドウ座標設定
    // タスクバーを除いたディスプレイ幅取得
    int nDisplayWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    int nDisplayHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    // ウィンドウ作成
    int nWindowWidth = rc.right - rc.left;  // ウィンドウ横幅
    int nWindowHeight = rc.bottom - rc.top;  // ウィンドウ縦幅
    int nWindowPosX = (nDisplayWidth >> 1) - (nWindowWidth >> 1);  // ウィンドウ左上X座標
    int nWindowPosY = (nDisplayHeight >> 1) - (nWindowHeight >> 1);  // ウィンドウ左上Y座標

    // ウィンドウの作成
    m_hWnd = CreateWindowEx(0,
        m_desc.strClassName.c_str(),
        m_desc.strCaption.c_str(),
        // 可変枠、最大化ボタンを取り除く
        GAME_WINDOW,
        nWindowPosX,
        nWindowPosY,
        nWindowWidth,
        nWindowHeight,
        NULL,
        NULL,
        hInstance,
        NULL);

    // 作成失敗表示
    if(!m_hWnd)
    {
        MessageBox(NULL, "ウィンドウ作成失敗", "エラー", MB_OK);
        return E_FAIL;
    }

    m_bInitialized = true;

    return hr;
}

//=============================================================================
// 内部生成処理
//=============================================================================
HRESULT CWindow::InnerCreate(const WindowDesc& desc)
{
    m_desc = desc;

    // スレッド生成
    HRESULT hr = E_FAIL;
    CThread::create(&m_pThread);
    hr = m_pThread->start(m_desc.pAsyncData, m_desc.pAsyncProc, true) ? S_OK : E_FAIL;

    return hr;
}

// EOF
