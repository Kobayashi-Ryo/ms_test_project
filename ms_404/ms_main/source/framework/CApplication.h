//=============================================================================
//
// アプリケーション
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __MS_APPLICATION_H__
#define __MS_APPLICATION_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/common.h>

// system interface
#include <system/ISystem.h>

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CSystem;
class CScene;
class CHardwareTimer;

//*****************************************************************************
// アプリケーションクラス
//*****************************************************************************
class CApplication
    : private CUncopyable
{
protected:

    CApplication();

    virtual ~CApplication();

public:

    virtual bool Init() = 0;

    virtual void Release() = 0;

    /**
    * アプリケーションを終了させる
    */
    void Finish();

    /**
    * システムの取得
    * @ret システムインターフェース
    */
    ISystem* GetSystem();

    /**
    * 現在のシーン取得
    * @ret システムインターフェース
    */
    CScene* GetCurrentScene();
    
    /**
    * アプリケーション開始
    * @ret リターンコード
    */
    s32 Run();

    /**
    * シーンを別のシーンで置き換え
    * @param pScene 置き換えたいシーン
    */
    void ReplaceScene(CScene* pScene);

    /**
    * アプリケーションインスタンス取得
    * @ret アプリケーションインスタンス
    */
    static CApplication* GetInstance();
    
private:

    // システムインターフェース
    CSystem* m_pSystem;

    // アプリケーション起動フラグ
    bool m_bIsRunning;

    // 現在のシーン
    CScene* m_pCurrentScene;
    
    // ハードウェアタイマー
    CHardwareTimer* m_pHardwareTimer;

    // アプリケーション
    static CApplication* m_spApp;
};

#endif  // __MS_APPLICATION_H__

// EOF
