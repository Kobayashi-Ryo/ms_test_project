//=============================================================================
//
// シーンクラス基底
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CNode.h"
#include "CCamera.h"
#include <vector>
#include <system/IShader.h>

static const s32 DEFAULT_CAMERA_NUM = 8;

static const s8* DEFAULT_VERTEX_SHADER_2D = "vs_default.fx";
static const s8* DEFAULT_PIXEL_SHADER_2D = "ps_default.fx";

static const s8* DEFAULT_VERTEX_SHADER_3D = "vs_3d.fx";
static const s8* DEFAULT_PIXEL_SHADER_3D = "ps_3d.fx";

//*****************************************************************************
// シーンクラス
//*****************************************************************************
class CScene
    : public CNode
{
public:

    // カメラ取得
    const std::vector<CCamera*>& GetCameras() const;
    // カメラ総数取得
    u32 GetNumCameras() const;

    // デフォルトシェーダー取得
    IShader* GetShader2D() const;
    IShader* GetShader3D() const;

    // ライト取得

    virtual bool Init();

    // こいつらをオーバーライドする
    // virtual void Update();
    // virtual void Draw();

protected:

    CScene();
    virtual ~CScene() = 0;

private:

    void InitShader();

private:

    std::vector<CCamera*> m_Cameras;

    IShader* m_pShader2D;
    IShader* m_pShader3D;
};

#endif  // __SCENE_H__

// EOF
