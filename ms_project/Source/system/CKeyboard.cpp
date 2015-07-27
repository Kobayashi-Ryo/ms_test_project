//=============================================================================
//
// キーボード
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CKeyboard.h"
#include "DebugUtil.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CKeyboard::CKeyboard()
{
    memset(&m_aKeyState         , 0, sizeof(m_aKeyState));
    memset(&m_aKeyTrigger       , 0, sizeof(m_aKeyTrigger));
    memset(&m_aKeyRelease       , 0, sizeof(m_aKeyRelease));
    memset(&m_aKeyRepeat        , 0, sizeof(m_aKeyRepeat));
    memset(&m_aKeyRepeatCount   , 0, sizeof(m_aKeyRepeatCount));
}

//=============================================================================
// デストラクタ
//=============================================================================
CKeyboard::~CKeyboard()
{
    if(m_pDev) m_pDev->Unacquire();
    SafeRelease(m_pDev);
}

//=============================================================================
// 生成
//=============================================================================
CKeyboard* CKeyboard::Create(CInputObject* pObj, HWND hWnd)
{
    CKeyboard* pKey = new CKeyboard();

    if(pKey)
    {
        INIT_CHECK(pKey->Init(pObj, hWnd));
        _PrintConsole("キーボード\n");
    }

    return pKey;
}

//=============================================================================
// 開放
//=============================================================================
void CKeyboard::Release()
{
    delete this;
}

//=============================================================================
// 更新
//=============================================================================
void CKeyboard::Update()
{
    BYTE aKeyState[MAX_KEY];    // キー入力のワーク

    // キーボードの情報取得
    if(SUCCEEDED(m_pDev->GetDeviceState(sizeof(aKeyState),
                                                &aKeyState[0])))
    {
        // 入力情報の作成
        // ループ処理
        for(int nKeyCnt = 0; nKeyCnt < MAX_KEY; nKeyCnt++)
        {
            // トリガー情報の作成
            m_aKeyTrigger[nKeyCnt] = ((m_aKeyState[nKeyCnt] ^ aKeyState[nKeyCnt]) & aKeyState[nKeyCnt]);

            // リリース情報の作成
            m_aKeyRelease[nKeyCnt] = ((m_aKeyState[nKeyCnt] ^ aKeyState[nKeyCnt]) & ~aKeyState[nKeyCnt]);

            // リピート情報の作成
            // キーを入力しているとき
            if(aKeyState[nKeyCnt] & KEY_ON)
            {    
                // カウントがREPEAT_TIME未満のとき
                if(m_aKeyRepeatCount[nKeyCnt] < REPEAT_TIME)
                {
                    // トリガー状態
                    m_aKeyRepeat[nKeyCnt] = m_aKeyTrigger[nKeyCnt];
                }

                // カウントが一定以上のとき
                else
                {
                    // 押下状態
                    m_aKeyRepeat[nKeyCnt] = aKeyState[nKeyCnt];
                    // カウンタをREPEAT_TIMEに固定
                    m_aKeyRepeatCount[nKeyCnt] = REPEAT_TIME;
                }

                // カウント増加
                m_aKeyRepeatCount[nKeyCnt]++;
            }

            // 入力していないとき
            else 
            {
                // トリガー状態
                m_aKeyRepeat[nKeyCnt] = m_aKeyTrigger[nKeyCnt];
                // カウントを 0 にする
                m_aKeyRepeatCount[nKeyCnt] = 0;
            }

            // キー入力状態の更新
            m_aKeyState[nKeyCnt] = aKeyState[nKeyCnt];
        }
    }
    else
    {
        // アクセス権を再取得
        m_pDev->Acquire();
    }
}

//=============================================================================
// プレス状態取得
//=============================================================================
bool CKeyboard::GetPress(u8 key) const
{
    return m_aKeyState[key] & KEY_ON ? true : false;
}

//=============================================================================
// トリガー状態取得
//=============================================================================
bool CKeyboard::GetTrigger(u8 key) const
{
    return m_aKeyTrigger[key] & KEY_ON ? true : false;
}

//=============================================================================
// リリース状態取得
//=============================================================================
bool CKeyboard::GetRelease(u8 key) const
{
    return m_aKeyRelease[key] & KEY_ON ? true : false;
}

//=============================================================================
// リピート状態取得
//=============================================================================
bool CKeyboard::GetRepeat(u8 key) const
{
    return m_aKeyRepeat[key] & KEY_ON ? true : false;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CKeyboard::Init(CInputObject* pObj, HWND hWnd)
{
    HRESULT hr;

    LPDIRECTINPUT8 pDInput = pObj->GetDInput();

    // デバイスの作成
    hr = pDInput->CreateDevice(GUID_SysKeyboard,
                                &m_pDev,
                                nullptr);
    _AssertExpr(SUCCEEDED(hr), "キーボードデバイス生成失敗");

    // データフォーマット設定
    hr = m_pDev->SetDataFormat(&c_dfDIKeyboard);
    _AssertExpr(SUCCEEDED(hr), "キーボードデータフォーマット初期化失敗");

    // 協調モードの設定(他のアプリケーションとのデバイスの共有方法)
    hr = m_pDev->SetCooperativeLevel(hWnd,
                                            (DISCL_FOREGROUND |        // フォアグラウンド
                                             DISCL_NONEXCLUSIVE));    // 非排他制御
    _AssertExpr(SUCCEEDED(hr), "キーボード協調モード初期化失敗");

    // キーボードへのアクセス権を取得
    m_pDev->Acquire();

    return hr;
}

// EOF
