//=============================================================================
//
// ゲームシーン
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CSceneGame.h"
#include "AppDelegate.h"

#include "CGameStage.h"

#include <common/DebugUtil.h>

CSceneGame* CSceneGame::CreateScene()
{
    CSceneGame* scene = new CSceneGame();

    bool success = scene->Init();
    _CriticalAssert(success);

    return scene;
}

bool CSceneGame::Init()
{
    // 自分の名前設定
    SetName("SceneGame");

    m_pGameStage = CGameStage::Create("st001");
    AddChild(m_pGameStage);

    return true;
}

void CSceneGame::Update()
{
    CNode::Update();
}

void CSceneGame::Draw()
{
    // HACK 適当2画面
    CApplication* app = CApplication::GetInstance();
    auto sys = app->GetSystem();
    auto holder = sys->GetDeviceHolder();
    auto d3dDev = holder->GetDevice();
    D3DVIEWPORT9 vp;
    d3dDev->GetViewport(&vp);

    // 両画面描画処理
    // startなどの表示

    // uiはそれぞれの画面で描画するようにする
    // 完全にレイアウトを決めるか
    // プレイヤーマネージャを作って、UIを持たせるか

    // 左側
    D3DVIEWPORT9 left = vp;
    left.X = 0;
    left.Y = 0;
    left.Width = (u32)(holder->GetBackBufferWidth() * 0.5f);
    left.Height = holder->GetBackBufferHeight();
    d3dDev->SetViewport(&left);
    d3dDev->Clear(
                0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
                D3DXCOLOR(1.0f, 0.5f, 0.5f,0), 1, 0);
    // 左側描画処理
    // カメラ設定
    // UI設定
    m_pGameStage->Draw();

    // 右側
    D3DVIEWPORT9 right = vp;
    right.X = (u32)(holder->GetBackBufferWidth() * 0.5f);
    right.Y = 0;
    right.Width = (u32)(holder->GetBackBufferWidth() * 0.5f);
    right.Height = holder->GetBackBufferHeight();
    d3dDev->SetViewport(&right);
    d3dDev->Clear(
                0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
                D3DXCOLOR(0.5f, 1.0f, 0.5f,0), 1, 0);

    // 元に戻す
    d3dDev->SetViewport(&vp);
}

// EOF
