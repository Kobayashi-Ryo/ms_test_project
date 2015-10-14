//=============================================================================
//
// プレイヤー
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CPlayer.h"

#include <common/DebugUtil.h>

CPlayer::CPlayer()
    : m_pDrawer(nullptr)
{
}

CPlayer::~CPlayer()
{
}

CPlayer* CPlayer::Create(s32 nID)
{
    CPlayer* pObj = new CPlayer();

    if(pObj)
    {
        bool suc = pObj->Init(nID);
        _Assert(suc);
        _PrintConsole("プレイヤー\n");
    }

    return pObj;
}

void CPlayer::Update()
{
    m_pDrawer->SetPositionY(GetPosition().y);

    CNode::Update();
}

void CPlayer::Draw()
{
    m_pDrawer->Draw();
}

void CPlayer::Move(const vec3& v)
{
    SetPosition(GetPosition() + v);
}

s32 CPlayer::GetID() const
{
    return m_nID;
}

bool CPlayer::Init(s32 nID)
{
    SetName("player");
    m_nID = nID;

    m_pDrawer = CSphere::Create();
    AddChild(m_pDrawer);

    SetPositionY(1.0f);

    return true;
}

// EOF
