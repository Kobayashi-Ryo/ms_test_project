//=============================================================================
//
// ゲームステージ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __GAME_STAGE_H__
#define __GAME_STAGE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "framework.h"
#include <common/common.h>

//*****************************************************************************
// OBJECT ID
//*****************************************************************************
enum ObjectID
{
    OBJECT_PLAYER1,
    OBJECT_PLAYER2
};

//*****************************************************************************
// クラス
//*****************************************************************************
class CGameStage
    : public CNode
{
public:

    CGameStage();
    ~CGameStage();

    // 生成
    static CGameStage* Create(cs8* pFileName);
    // 初期化
    bool Init(cs8* pFileName);

    // 更新
    virtual void Update();
    // 描画
    virtual void Draw();

    // デバッグ描画

    // カメラ設定
    void SetCamera(CCamera* pCamera);

    // プレイヤースコア取得

private:

    // プレイヤー更新
    void UpdatePlayer();

    // オブジェクトソート

    // 当たり判定

private:

    // プレイヤー
    // プレイヤー移動ルート

    // ステージオブジェクト

    // フィールド
    CMeshField* m_pField;

    // カメラ
    CCamera* m_pCamera;
};

#endif  // __GAME_STAGE_H__

// EOF
