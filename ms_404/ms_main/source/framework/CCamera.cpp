//=============================================================================
//
// カメラ
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CCamera.h"

CCamera::CCamera()
    : m_pos(0,0,0)
    , m_look(0,0,0)
    , m_up(0,1,0)
    , m_fov(D3DX_PI / 4.0f)
    , m_aspect(16.0f / 9.0f)
    , m_near(1.0f)
    , m_far(100.0f)
{
    m_viewport.X = 0;
    m_viewport.Y = 0;
    m_viewport.Width = 400;
    m_viewport.Height = 300;
    m_viewport.MinZ = 0.0f;
    m_viewport.MaxZ = 1.0f;
}
CCamera::~CCamera(){}

void CCamera::SetupMatrix()
{
    D3DXMatrixLookAtLH(
        &m_View,
        &m_pos,
        &m_look,
        &m_up);
    D3DXMatrixInverse(&m_InvView, nullptr, &m_View);

    D3DXMatrixPerspectiveFovLH(
        &m_Proj,
        m_fov,
        m_aspect,
        m_near,
        m_far);

    D3DXMatrixMultiply(&m_VP, &m_View, &m_Proj);

    SetAttitudeMatrix();
}

void CCamera::SetPos(const vec3& pos){ SetPos(pos.x, pos.y, pos.z); }
void CCamera::SetPos(const float x, const float y, const float z){ m_pos.x=x; m_pos.y=y; m_pos.z=z; }
const vec3& CCamera::GetPos(){ return m_pos; }

void CCamera::SetLookAt(const vec3& look){ SetLookAt(look.x, look.y, look.z); }
void CCamera::SetLookAt(const float x, const float y, const float z){ m_look.x=x; m_look.y=y; m_look.z=z; }
const vec3& CCamera::GetLookAt(){ return m_look; }

void CCamera::SetFoV(const float fov){ m_fov = fov; }
float CCamera::GetFoV(){ return m_fov; }
void CCamera::SetAspect(const float aspect){ m_aspect = aspect; }
float CCamera::GetAspect(){ return m_aspect; }
void CCamera::SetNear(const float fNear){ m_near = fNear; }
float CCamera::GetNear(){ return m_near; }
void CCamera::SetFar(const float fFar){ m_far = fFar; }
float CCamera::GetFar(){ return m_far; }

const mat4x4& CCamera::GetView(){ return m_View; }
const mat4x4& CCamera::GetInvView(){ return m_InvView; }
const mat4x4& CCamera::GetProj(){ return m_Proj; }
const mat4x4& CCamera::GetViewProj(){ return m_VP; }

// 姿勢行列取得
const mat4x4& CCamera::GetAttitudeMatrix() const
{
    return m_Atti;
}

void CCamera::SetAttitudeMatrix()
{
    D3DXMatrixIdentity(&m_Atti);

    m_Atti._11 = m_View._11;
    m_Atti._22 = m_View._22;
    m_Atti._33 = m_View._33;
    
    m_Atti._12 = m_View._21;
    m_Atti._13 = m_View._31;
    
    m_Atti._23 = m_View._32;
}

// EOF