//=============================================================================
//
// マウス
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CMouse.h"
#include "DebugUtil.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMouse::CMouse()
    : m_nScroll(0)
{
    // 座標クリア
    m_pos.x = 0;
    m_pos.y = 0;
    // 移動差分クリア
    m_diff.x = 0;
    m_diff.y = 0;

    // マウス変数クリア
    memset(&m_MouseState, 0, sizeof(DIMOUSESTATE2));
    memset(&m_MouseTrigger, 0, sizeof(DIMOUSESTATE2));
    memset(&m_MouseRelease, 0, sizeof(DIMOUSESTATE2));
    memset(&m_MouseRepeat, 0, sizeof(DIMOUSESTATE2));
    memset(&m_aMouseRepeatCount, 0, sizeof(int) * MAX_BUTTON);
}

//=============================================================================
// デストラクタ
//=============================================================================
CMouse::~CMouse()
{
    if(m_pDev) m_pDev->Unacquire();
    SafeRelease(m_pDev);
}

//=============================================================================
// 生成
//=============================================================================
CMouse* CMouse::Create(CInputObject* pObj, HWND hWnd)
{
    CMouse* pMs = new CMouse();

    if(pMs)
    {
        INIT_CHECK(pMs->Init(pObj, hWnd));
        _PrintConsole("マウス\n");
    }

    return pMs;
}

//=============================================================================
// 開放
//=============================================================================
void CMouse::Release()
{
    delete this;
}

//=============================================================================
// 更新
//=============================================================================
void CMouse::Update()
{
    DIMOUSESTATE2 TempState;
    
    // マウスの情報取得
    if(SUCCEEDED(m_pDev->GetDeviceState(sizeof(TempState),
                                                &TempState)))
    {
        // スクリーン座標取得
        GetCursorPos(&m_pos);
        // スクリーン座標からクライアント座標に変換
        ScreenToClient(m_hWnd, &m_pos);

        // 差分を設定
        m_diff.x = TempState.lX;
        m_diff.y = TempState.lY;
        // スクロール量取得
        m_nScroll = TempState.lZ;

        for(int i = 0; i < MAX_BUTTON; i++)
        {
            // トリガー情報の作成
            m_MouseTrigger.rgbButtons[i] = ((m_MouseState.rgbButtons[i] ^ TempState.rgbButtons[i]) & TempState.rgbButtons[i]);

            // リリース情報の作成
            m_MouseRelease.rgbButtons[i] = ((m_MouseState.rgbButtons[i] ^ TempState.rgbButtons[i]) & ~TempState.rgbButtons[i]);
            
            // リピート情報の作成
            // キーを入力しているとき
            if(TempState.rgbButtons[i] & KEY_ON)
            {    
                // カウントがREPEAT_TIME未満のとき
                if(m_aMouseRepeatCount[i] < REPEAT_TIME)
                {
                    // トリガー状態
                    m_MouseRepeat.rgbButtons[i] = m_MouseTrigger.rgbButtons[i];
                }

                // カウントが一定以上のとき
                else
                {
                    // 押下状態
                    m_MouseRepeat.rgbButtons[i] = TempState.rgbButtons[i];
                    // カウンタをREPEAT_TIMEに固定
                    m_aMouseRepeatCount[i] = REPEAT_TIME;
                }

                // カウント増加
                m_aMouseRepeatCount[i]++;
            }

            // 入力していないとき
            else 
            {
                // トリガー状態
                m_MouseRepeat.rgbButtons[i] = m_MouseTrigger.rgbButtons[i];
                // カウントを 0 にする
                m_aMouseRepeatCount[i] = 0;
            }

            // キー入力状態の更新
            m_MouseState.rgbButtons[i] = TempState.rgbButtons[i];
        }
    }
    else
    {
        // アクセス権を再取得
        m_pDev->Acquire();
    }
}

//=============================================================================
// 座標取得
//=============================================================================
const POINT& CMouse::GetPosition() const
{
    return m_pos;
}

//=============================================================================
// 移動量取得
//=============================================================================
const POINT& CMouse::GetMove() const
{
    return m_diff;
}

//=============================================================================
// スクロール量取得
//=============================================================================
LONG CMouse::GetScroll() const
{
    return m_nScroll;
}

//=============================================================================
// プレス状態取得
//=============================================================================
bool CMouse::GetPress(MouseButton btn) const
{
    return m_MouseState.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// トリガー状態取得
//=============================================================================
bool CMouse::GetTrigger(MouseButton btn) const
{
    return m_MouseTrigger.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// リリース状態取得
//=============================================================================
bool CMouse::GetRelease(MouseButton btn) const
{
    return m_MouseRelease.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// リピート状態取得
//=============================================================================
bool CMouse::GetRepeat(MouseButton btn) const
{
    return m_MouseRepeat.rgbButtons[btn] & KEY_ON ? true : false;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CMouse::Init(CInputObject* pObj, HWND hWnd)
{
    HRESULT hr;

    LPDIRECTINPUT8 pDInput = pObj->GetDInput();

    // デバイスの作成
    hr = pDInput->CreateDevice(GUID_SysMouse,
                                &m_pDev,
                                nullptr);
    _AssertExpr(SUCCEEDED(hr), "マウスデバイス生成失敗");

    // データフォーマット設定
    hr = m_pDev->SetDataFormat(&c_dfDIMouse);
    _AssertExpr(SUCCEEDED(hr), "マウスデータフォーマット初期化失敗");

    // 協調モードの設定(他のアプリケーションとのデバイスの共有方法)
    hr = m_pDev->SetCooperativeLevel(hWnd,
                                            (DISCL_FOREGROUND |        // フォアグラウンド
                                             DISCL_NONEXCLUSIVE));    // 非排他制御
    _AssertExpr(SUCCEEDED(hr), "マウス協調モード初期化失敗");

    // マウスへのアクセス権を取得
    m_pDev->Acquire();

    // ウィンドウハンドル設定
    m_hWnd = hWnd;

    return hr;
}

// EOF
