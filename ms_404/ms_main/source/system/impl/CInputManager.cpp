//=============================================================================
//
// 入力マネージャーインターフェース
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CInputManager.h"

// input object
#include "CInputObject.h"
// input
#include "CKeyboard.h"
#include "CMouse.h"

// debug
#include <common/DebugUtil.h>

//=============================================================================
// コンストラクタ
//=============================================================================
CInputManager::CInputManager()
    : m_pInputObject(nullptr)
    , m_pKeyboard(nullptr)
    , m_pMouse(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CInputManager::~CInputManager()
{
    SafeRelease(m_pMouse);
    SafeRelease(m_pKeyboard);
    SafeRelease(m_pInputObject);
}

//=============================================================================
// 生成
//=============================================================================
CInputManager* CInputManager::Create(HWND hWnd)
{
    CInputManager* pMgr = new CInputManager();

    if(pMgr)
    {
        INIT_CHECK(pMgr->Init(hWnd));
        _PrintConsole("入力マネージャー\n");
    }

    return pMgr;
}

//=============================================================================
// 開放
//=============================================================================
void CInputManager::Release()
{
    delete this;
}

//=============================================================================
// 更新
//=============================================================================
void CInputManager::Update()
{
    m_pKeyboard->Update();
    m_pMouse->Update();
}

//=============================================================================
// キーボード取得
//=============================================================================
IKeyboard* CInputManager::GetKeyboard() const
{
    return m_pKeyboard;
}

//=============================================================================
// マウス取得
//=============================================================================
IMouse* CInputManager::GetMouse() const
{
    return m_pMouse;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CInputManager::Init(HWND hWnd)
{
    // 入力オブジェクト
    m_pInputObject = CInputObject::Create();
    if(IS_NULL(m_pInputObject))
    {
        return E_FAIL;
    }

    // キーボード
    m_pKeyboard = CKeyboard::Create(m_pInputObject, hWnd);
    if(IS_NULL(m_pKeyboard))
    {
        return E_FAIL;
    }
    
    // マウス
    m_pMouse = CMouse::Create(m_pInputObject, hWnd);
    if(IS_NULL(m_pMouse))
    {
        return E_FAIL;
    }

    return S_OK;
}

// EOF
