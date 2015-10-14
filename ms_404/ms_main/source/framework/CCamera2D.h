//=============================================================================
//
// 2Dカメラ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __CAMERA_2D_H__
#define __CAMERA_2D_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/common.h>
#include <common/msMath.h>

//*****************************************************************************
// 2Dカメラクラス
//*****************************************************************************
class CCamera2D
{
public:

    CCamera2D();
    ~CCamera2D();

    void SetupMatrix();

    void SetPos(const vec2& pos);
    void SetPos(cf32 x, cf32 y);
    const vec2& GetPos();

    void SetZoomRate(cf32 zoom);
    void AddZoomRate(cf32 zoom);
    f32 GetZoomRate();

    void SetVolumeWidth(cf32 width);
    f32 GetVolumeWidth();

    void SetVolumeHeight(cf32 height);
    f32 GetVolumeHeight();
    
    const mat4x4& GetOrtho();

private:
    
    vec2 m_pos;

    f32 m_zoom;

    f32 m_width;
    f32 m_height;

    mat4x4 m_Ortho;
};


#endif    // __CAMERA_2D_H__

// EOF
