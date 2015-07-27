//=============================================================================
//
// 入力マネージャー
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CUncopyable.h"
#include "interface/IInputManager.h"

//*****************************************************************************
// 前方参照
//*****************************************************************************
// input object
class CInputObject;
// input
class CKeyboard;
class CMouse;

//*****************************************************************************
// 入力マネージャー
//*****************************************************************************
class CInputManager
    : private CUncopyable
    , public IInputManager
{
private:

    /**
    * コンストラクタ
    */
    CInputManager();

    /**
    * デストラクタ
    */
    ~CInputManager();

public:

    /**
    * 生成
    * @ret マネージャー
    */
    static CInputManager* Create(HWND hWnd);

    /**
    * 開放
    */
    void Release();

    /**
    * 更新
    */
    void Update();

    /**
    * キーボード取得
    * @ret キーボード
    */
    IKeyboard* GetKeyboard() const;

    /**
    * マウス取得
    * @ret マウス
    */
    IMouse* GetMouse() const;

private:

    /**
    * 初期化
    * @ret S_OK:成功 E_FAIL:失敗
    */
    HRESULT Init(HWND hWnd);

private:

    // 入力オブジェクト
    CInputObject* m_pInputObject;

    // キーボード
    CKeyboard* m_pKeyboard;

    // マウス
    CMouse* m_pMouse;
};

#endif  // __INPUT_MANAGER_H__

// EOF
