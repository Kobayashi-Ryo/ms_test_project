//=============================================================================
//
// 2Dカメラ
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CCamera2D.h"

CCamera2D::CCamera2D()
    : m_pos(0,0)
    , m_zoom(1)
    , m_width(256)
    , m_height(256)
{
}

namespace
{
    void SetOrthoMatrix(mat4x4 *pOut, f32 fLeft, f32 fTop, f32 fRight, f32 fBottom, f32 fNear, f32 fFar);
}

CCamera2D::~CCamera2D(){}

void CCamera2D::SetupMatrix()
{
    f32 fWidthOverHeight = m_width / m_height;
    SetOrthoMatrix(
        &m_Ortho,
        m_pos.x            + m_zoom * fWidthOverHeight,
        m_pos.y            + m_zoom,
        m_pos.x + m_width  - m_zoom * fWidthOverHeight,
        m_pos.y + m_height - m_zoom,
        0.0f,
        1.0f);
}
    
void CCamera2D::SetPos(const vec2& pos){SetPos(pos.x,pos.y);}
void CCamera2D::SetPos(cf32 x, cf32 y){m_pos.x=x;m_pos.y=y;}
const vec2& CCamera2D::GetPos(){return m_pos;}

void CCamera2D::SetZoomRate(cf32 zoom){m_zoom=zoom;}
void CCamera2D::AddZoomRate(cf32 zoom){m_zoom+=zoom;}
f32 CCamera2D::GetZoomRate(){return m_zoom;}

void CCamera2D::SetVolumeWidth(cf32 width){m_width=width;}
f32 CCamera2D::GetVolumeWidth(){return m_width;}

void CCamera2D::SetVolumeHeight(cf32 height){m_height=height;}
f32 CCamera2D::GetVolumeHeight(){return m_height;}

const mat4x4& CCamera2D::GetOrtho(){return m_Ortho;}


namespace
{
//=============================================================================
// 平行投影行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/15
//=============================================================================
void SetOrthoMatrix(mat4x4 *pOut, f32 fLeft, f32 fTop, f32 fRight, f32 fBottom, f32 fNear, f32 fFar)
{
	f32 OneOverRightMinusLeft = 1.0f / (fRight - fLeft);
	f32 OneOverTopMinusBottom = 1.0f / (fTop - fBottom);
	f32 OneOverFarMinusNear	= 1.0f / (fFar - fNear);

	pOut->_11 = 2.0f  * OneOverRightMinusLeft;
	pOut->_22 = 2.0f  * OneOverTopMinusBottom;
	pOut->_33 = -1.0f * OneOverFarMinusNear;

	pOut->_41 = -((fRight + fLeft) * OneOverRightMinusLeft);
	pOut->_42 = -((fTop + fBottom) * OneOverTopMinusBottom);
	pOut->_43 = fNear * OneOverFarMinusNear;

	pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_34 = 0.0f;

	pOut->_44 = 1.0f;
}
}

// EOF
