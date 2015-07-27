//=============================================================================
//
// アプリケーション
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MS_APP_H__
#define __MS_APP_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "common.h"

// system interface
#include "ISystem.h"

//*****************************************************************************
// アプリケーションクラス
//*****************************************************************************
class CApp
    : private CUncopyable
{
private:

    CApp(ISystem* pSystem);

    virtual ~CApp(){};

public:

    virtual void Release() = 0;

    virtual void Update() = 0;

    virtual void Draw() = 0;

    /**
    * アプリケーションを終了させる
    */
    void Finish();
    
    /**
    * システムの取得
    * @ret システムインターフェース
    */
    ISystem* GetSystem();

private:

    // システムインターフェース
    ISystem* m_pSystem;

    // アプリケーション起動フラグ
    bool m_bIsRunning;
};

#endif  // __MS_APP_H__

// EOF
