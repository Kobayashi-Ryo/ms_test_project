//=============================================================================
//
// アプリケーションの独自設定
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "AppDelegate.h"
#include "CSceneGame.h"

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::Init()
{
    // 初期化
    auto scene = CSceneGame::CreateScene();
    ReplaceScene(scene);

    return true;
}

void AppDelegate::Release()
{
    delete this;
}

// EOF
