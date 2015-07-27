//=============================================================================
//
// ノードクラス
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CNode.h"
#include "DebugUtil.h"

//=============================================================================
// 子ノードを追加
//=============================================================================
void CNode::AddChild(CNode* pChild)
{
    _Assert(pChild);
    _Assert(pChild != m_pParent);
    auto it = m_Children.find(pChild);
    if(it == m_Children.end())
    {
        pChild->Increment();
        m_Children.insert(pChild);
    }
}

//=============================================================================
// 自分を親から削除して、自分の子供ごと消える
//=============================================================================
void CNode::RemoveFromParentAndCleanUp()
{
    RemoveFromParent();
    CRef::Decrement();
}

//=============================================================================
// 自分を親から削除する
//=============================================================================
void CNode::RemoveFromParent()
{
    if(m_pParent)
    {
        m_pParent->RemoveChild(this);
    }
}

//=============================================================================
// 親取得
//=============================================================================
CNode* CNode::GetParent() const
{
    return m_pParent;
}

//=============================================================================
// 子のリスト取得
//=============================================================================
std::set<CNode*> CNode::GetChildren() const
{
    return m_Children;
}

//=============================================================================
// 更新
//=============================================================================
void CNode::Update()
{
    UpdateSelf();

    for(auto it = m_Children.begin(); it != m_Children.end() ; ++it)
    {
        (*it)->Update();
    }
}

//=============================================================================
// 描画
//=============================================================================
void CNode::Draw()
{
    DrawSelf();

    for(auto it = m_Children.begin(); it != m_Children.end() ; ++it)
    {
        (*it)->Draw();
    }
}

// 座標設定
void CNode::SetPosition(const vec3& pos){ SetPosition(pos.x, pos.y, pos.z); }
void CNode::SetPosition(cf32 x, cf32 y, cf32 z){ m_pos.x = x; m_pos.y = y; m_pos.z = z; }
void CNode::SetPositionX(cf32 pos){ m_pos.x = pos; }
void CNode::SetPositionY(cf32 pos){ m_pos.y = pos; }
void CNode::SetPositionZ(cf32 pos){ m_pos.z = pos; }
// 座標取得
const vec3& CNode::GetPosition() const { return m_pos; }

// 回転量設定
void CNode::SetRotation(const vec3& rot){ SetRotation(rot.x, rot.y, rot.z); }
void CNode::SetRotation(cf32 x, cf32 y, cf32 z){ m_rot.x = x; m_rot.y = y; m_rot.z = z; }
void CNode::SetRotationX(cf32 rot){ m_rot.x = rot; }
void CNode::SetRotationY(cf32 rot){ m_rot.y = rot; }
void CNode::SetRotationZ(cf32 rot){ m_rot.z = rot; }
// 回転量取得
const vec3& CNode::GetRotation() const { return m_rot; }

// 拡縮設定
void CNode::SetScaling(const vec3& scl){ SetScaling(scl.x, scl.y, scl.z); }
void CNode::SetScaling(cf32 x, cf32 y, cf32 z){ m_scl.x = x; m_scl.y = y; m_scl.z = z; }
void CNode::SetScalingX(cf32 scl){ m_scl.x = scl; }
void CNode::SetScalingY(cf32 scl){ m_scl.y = scl; }
void CNode::SetScalingZ(cf32 scl){ m_scl.z = scl; }
// 拡縮取得
const vec3& CNode::GetScaling() const { return m_scl; }

// 表示設定
void CNode::SetVisible(const bool bVisible) { m_bVisible = bVisible; }
// 表示状態取得
bool CNode::IsVisible() const { return m_bVisible; }

// 変換行列取得
const mat4x4& CNode::GetTransform() const
{
    return m_transform;
}

// 変換行列設定
void CNode::SetupTransform()
{
    D3DXMatrixWorld(&m_transform, m_pos, m_rot, m_scl);
}

// 親を設定
void CNode::SetParent(CNode* pParent)
{
    _Assert(IS_NULL(m_pParent));
    _Assert(!IS_NULL(pParent));
    m_pParent = pParent;
}

// 子供を削除
void CNode::RemoveChild(CNode* pChild)
{
    auto it = m_Children.find(pChild);

    if(it != m_Children.end())
    {
        m_Children.erase(it);
    }
}

// 更新通知
void CNode::SetUpdate(bool bUpdate)
{
    m_bUpdate = bUpdate;
}

// 更新取得
bool CNode::GetUpdate()
{
    return m_bUpdate;
}

CNode::CNode()
    : m_pParent(nullptr)
    , m_pos(0, 0, 0)
    , m_rot(0, 0, 0)
    , m_scl(1, 1, 1)
    , m_bVisible(true)
    , m_bUpdate(true)
{
    D3DXMatrixIdentity(&m_transform);
}

CNode::~CNode()
{
    for(auto it = m_Children.begin(); it != m_Children.end(); )
    {
        (*it)->Decrement();
        m_Children.erase(it++);
    }
}

// EOF
