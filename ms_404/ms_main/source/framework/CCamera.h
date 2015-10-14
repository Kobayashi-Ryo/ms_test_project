//=============================================================================
//
// カメラ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <common/msMath.h>

//*****************************************************************************
// カメラクラス
//*****************************************************************************
class CCamera
{
public:

    CCamera();
    ~CCamera();

    void SetupMatrix();

    void SetPos(const vec3& pos);
    void SetPos(const float x, const float y, const float z);
    const vec3& GetPos();

    void SetLookAt(const vec3& look);
    void SetLookAt(const float x, const float y, const float z);
    const vec3& GetLookAt();

    void SetFoV(const float fov);
    float GetFoV();
    void SetAspect(const float aspect);
    float GetAspect();
    void SetNear(const float fNear);
    float GetNear();
    void SetFar(const float fFar);
    float GetFar();

    const mat4x4& GetView();
    const mat4x4& GetInvView();
    const mat4x4& GetProj();
    const mat4x4& GetViewProj();

    // 姿勢行列取得
    const mat4x4& GetAttitudeMatrix() const;

private:

    void SetAttitudeMatrix();

private:

    vec3 m_pos;
    vec3 m_look;
    vec3 m_up;

    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;

    mat4x4 m_View;
    mat4x4 m_InvView;
    mat4x4 m_Proj;
    mat4x4 m_VP;
    mat4x4 m_Atti;

    viewport m_viewport;
};

#endif  // __CAMERA_H__

// EOF