//=============================================================================
//
// ノードクラス
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef __NODE_H__
#define __NODE_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CRef.h"
#include "common.h"
#include <set>
#include "msMath.h"

//*****************************************************************************
// ノードクラス
//*****************************************************************************
class CNode
    : private CRef
{
public:

    // 子ノードを追加
    void AddChild(CNode* pChild);

    // 自分を親から削除して、自分の子供ごと消える
    void RemoveFromParentAndCleanUp();

    // 自分を親から削除する
    void RemoveFromParent();

    // 親取得
    CNode* GetParent() const;

    // 子のリスト取得
    std::set<CNode*> GetChildren() const;

    // 更新
    virtual void Update();
    // 描画
    virtual void Draw();

    // 座標設定
    void SetPosition(const vec3& pos);
    void SetPosition(cf32 x, cf32 y, cf32 z);
    void SetPositionX(cf32 pos);
    void SetPositionY(cf32 pos);
    void SetPositionZ(cf32 pos);
    // 座標取得
    const vec3& GetPosition() const;

    // 回転量設定
    void SetRotation(const vec3& rot);
    void SetRotation(cf32 x, cf32 y, cf32 z);
    void SetRotationX(cf32 rot);
    void SetRotationY(cf32 rot);
    void SetRotationZ(cf32 rot);
    // 回転量取得
    const vec3& GetRotation() const;

    // 拡縮設定
    void SetScaling(const vec3& scl);
    void SetScaling(cf32 x, cf32 y, cf32 z);
    void SetScalingX(cf32 scl);
    void SetScalingY(cf32 scl);
    void SetScalingZ(cf32 scl);
    // 拡縮取得
    const vec3& GetScaling() const;

    // 表示設定
    void SetVisible(const bool bVisible);
    // 表示状態取得
    bool IsVisible() const;

    // 変換行列取得
    const mat4x4& GetTransform() const;

protected:

    // 更新実装
    virtual void UpdateSelf(){}
    // 描画実装
    virtual void DrawSelf(){}

    // 変換行列設定
    void SetupTransform();

    // 親を設定
    void SetParent(CNode* pParent);

    // 子供を削除
    void RemoveChild(CNode* pChild);

    // 更新通知
    void SetUpdate(bool bUpdate);
    // 更新取得
    bool GetUpdate();

    CNode();

    virtual ~CNode() = 0;

private:

    CNode* m_pParent;

    std::set<CNode*> m_Children;

    mat4x4 m_transform;
    vec3 m_pos;
    vec3 m_rot;
    vec3 m_scl;

    bool m_bVisible;

    bool m_bUpdate;
};

#endif  // __NODE_H__

// EOF
